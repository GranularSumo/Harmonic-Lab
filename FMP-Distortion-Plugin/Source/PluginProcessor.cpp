/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FMPDistortionPluginAudioProcessor::FMPDistortionPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
        treestate(*this, nullptr, "PARAMETERS", createParameterLayout()),
        oversamplingProcessor(2, 4, juce::dsp::Oversampling<float>::FilterType::filterHalfBandPolyphaseIIR)
#endif
{
    using namespace parameterInfo;
    treestate.addParameterListener(inputGainId, this);
    treestate.addParameterListener(saturationId, this);
    treestate.addParameterListener(oversamplingId, this);
    treestate.addParameterListener(dryWetId, this);
}

FMPDistortionPluginAudioProcessor::~FMPDistortionPluginAudioProcessor()
{
    using namespace parameterInfo;
    treestate.removeParameterListener(inputGainId, this);
    treestate.removeParameterListener(saturationId, this);
    treestate.removeParameterListener(oversamplingId, this);
    treestate.removeParameterListener(dryWetId, this);

    
}

//==============================================================================
// valueTreeState functions

juce::AudioProcessorValueTreeState::ParameterLayout FMPDistortionPluginAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    using namespace parameterInfo;
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(inputGainId, inputGainName, -24.0f, 24.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterBool>(saturationId, sautrationName, false));
    parameters.push_back(std::make_unique<juce::AudioParameterBool>(oversamplingId, oversamplingName, false));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(dryWetId, dryWetName, 0.0f, 1.0f, 1.0f));


    return { parameters.begin(), parameters.end() };
}

void FMPDistortionPluginAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    using namespace parameterInfo;

    if (parameterID == inputGainId)
    {
        gainProcessor.setGainDecibels(newValue);
    }

    if (parameterID == saturationId)
    {
        dspProcessor.setProcessState();
    }

    if (parameterID == oversamplingId)
    {
        isOversampled = newValue;
    }

    if (parameterID == dryWetId)
    {
        dryWet.setWetMixProportion(newValue);
    }
}

//==============================================================================
const juce::String FMPDistortionPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FMPDistortionPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FMPDistortionPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FMPDistortionPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FMPDistortionPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FMPDistortionPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FMPDistortionPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FMPDistortionPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FMPDistortionPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void FMPDistortionPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FMPDistortionPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();

    dryWet.prepare(spec);
    dryWet.setWetMixProportion(treestate.getRawParameterValue(parameterInfo::dryWetId)->load());

    gainProcessor.prepare(spec);
    gainProcessor.setGainDecibels(treestate.getRawParameterValue(parameterInfo::inputGainId)->load());
    gainProcessor.setRampDurationSeconds(0.02f);

    oversamplingProcessor.initProcessing(samplesPerBlock);

    isOversampled = treestate.getRawParameterValue(parameterInfo::oversamplingId)->load();

}

void FMPDistortionPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FMPDistortionPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FMPDistortionPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    juce::dsp::AudioBlock<float> block(buffer);

    dryWet.pushDrySamples(block);

    if (isOversampled) 
    {
        auto oversampledBlock = oversamplingProcessor.processSamplesUp(block);


        gainProcessor.process(juce::dsp::ProcessContextReplacing<float>(oversampledBlock));
        dspProcessor.process(oversampledBlock);
        DBG("test");

        oversamplingProcessor.processSamplesDown(block);
    }
    else
    {
        gainProcessor.process(juce::dsp::ProcessContextReplacing<float>(block));
        dspProcessor.process(block);
    }

    dryWet.mixWetSamples(block);
}

//==============================================================================
bool FMPDistortionPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FMPDistortionPluginAudioProcessor::createEditor()
{
    //return new FMPDistortionPluginAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void FMPDistortionPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FMPDistortionPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FMPDistortionPluginAudioProcessor();
}
