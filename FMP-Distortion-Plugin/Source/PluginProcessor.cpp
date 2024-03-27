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
    treestate.addParameterListener(outputGainId, this);
    treestate.addParameterListener(oversamplingId, this);
    treestate.addParameterListener(dryWetId, this);
    treestate.addParameterListener(distortionTypeId, this);
    treestate.addParameterListener(driveId, this);
    treestate.addParameterListener(preFilterId, this);
    treestate.addParameterListener(preFilterTypeId, this);
    treestate.addParameterListener(preFilterCutoffId, this);
    treestate.addParameterListener(preFilterResId, this);
    treestate.addParameterListener(postFilterId, this);
    treestate.addParameterListener(postFilterTypeId, this);
    treestate.addParameterListener(postFilterCutoffId, this);
    treestate.addParameterListener(postFilterResId, this);
    treestate.addParameterListener(themeId, this);
}

FMPDistortionPluginAudioProcessor::~FMPDistortionPluginAudioProcessor()
{
    using namespace parameterInfo;
    treestate.removeParameterListener(inputGainId, this);
    treestate.removeParameterListener(outputGainId, this);
    treestate.removeParameterListener(oversamplingId, this);
    treestate.removeParameterListener(dryWetId, this);
    treestate.removeParameterListener(distortionTypeId, this);
    treestate.removeParameterListener(driveId, this);
    treestate.removeParameterListener(preFilterId, this);
    treestate.removeParameterListener(preFilterTypeId, this);
    treestate.removeParameterListener(preFilterCutoffId, this);
    treestate.removeParameterListener(preFilterResId, this);
    treestate.removeParameterListener(postFilterId, this);
    treestate.removeParameterListener(postFilterTypeId, this);
    treestate.removeParameterListener(postFilterCutoffId, this);
    treestate.removeParameterListener(postFilterResId, this);
    treestate.removeParameterListener(themeId, this);
    
}

//==============================================================================
// valueTreeState functions

juce::AudioProcessorValueTreeState::ParameterLayout FMPDistortionPluginAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    using namespace parameterInfo;
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(inputGainId, inputGainName, -24.0f, 24.0f, 0.0f));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(outputGainId, outputGainName, -24.0f, 24.0f, 0.0f));

    parameters.push_back(std::make_unique<juce::AudioParameterBool>(oversamplingId, oversamplingName, false));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(dryWetId, dryWetName, 0.0f, 1.0f, 1.0f));

    parameters.push_back(std::make_unique<juce::AudioParameterChoice>(distortionTypeId, distortionTypeName, distortionTypes, 0));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(driveId, driveName, 1.0f, 24.0f, 4.0f));

    parameters.push_back(std::make_unique<juce::AudioParameterBool>(preFilterId, preFilterName, false));
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>(preFilterTypeId, preFilterTypeName, preFilterTypes, 0));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(preFilterCutoffId, preFilterCutoffName, juce::NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.2f), 22000.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(preFilterResId, preFilterResName, 1.0f / std::sqrt(2), (1.0f / std::sqrt(2)) * 20.0f, 1.0f / std::sqrt(2) + 3));

    parameters.push_back(std::make_unique<juce::AudioParameterBool>(postFilterId, postFilterName, false));
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>(postFilterTypeId, postFilterTypeName, postFilterTypes, 0));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(postFilterCutoffId, postFilterCutoffName, juce::NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.2f), 22000.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(postFilterResId, postFilterResName, 1.0f / std::sqrt(2), (1.0f / std::sqrt(2)) * 20.0f, 1.0f / std::sqrt(2) + 3));

    parameters.push_back(std::make_unique<juce::AudioParameterBool>(uiModeId, uiModeName, true));
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>(themeId, themeName, themeList, 0));


    return { parameters.begin(), parameters.end() };
}

void FMPDistortionPluginAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    using namespace parameterInfo;

    if (parameterID == inputGainId)
    {
        gainProcessor.setGainDecibels(newValue);
    }

    if (parameterID == outputGainId)
    {
        outputGainProcessor.setGainDecibels(newValue);
    }

    if (parameterID == oversamplingId)
    {
        isOversampled = newValue;
        if (isOversampled)
        {
            auto oversamplingFactor = oversamplingProcessor.getOversamplingFactor();
            spec.sampleRate = currentSampleRate * oversamplingFactor;
            spec.maximumBlockSize = currentSamplePerBlock * oversamplingFactor;
            spec.numChannels = getTotalNumInputChannels();
            preFilter.prepare(spec);

            dspProcessor.updateDcBlockerCoefficient(spec.sampleRate);
        }
        else
        {
            spec.sampleRate = currentSampleRate;
            spec.maximumBlockSize = currentSamplePerBlock;
            spec.numChannels = getTotalNumInputChannels();
            preFilter.prepare(spec);

            dspProcessor.updateDcBlockerCoefficient(spec.sampleRate);
        }
    }

    if (parameterID == dryWetId)
    {
        dryWet.setWetMixProportion(newValue);
    }

    if (parameterID == distortionTypeId)
    {
        int index = static_cast<int>(newValue);
        auto algorithm = parameterInfo::indexToAlgorithm(index);
        dspProcessor.resetDelaySamples();
        dspProcessor.resetCounters();
        dspProcessor.setDistortionType(algorithm);
    }

    if (parameterID == driveId)
    {
        dspProcessor.getSmoothedDrive().setTargetValue(newValue);
    }

    if (parameterID == preFilterId)
    {
        preFilterIsOn = newValue;
    }

    if (parameterID == postFilterId)
    {
        postFilterIsOn = newValue;
    }

    if (parameterID == preFilterTypeId)
    {
        if (newValue == 0)
        {
            preFilter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
        }
        else if (newValue == 1)
        {
            preFilter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
        }
        else
        {
            preFilter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
        }
    }

    if (parameterID == preFilterCutoffId)
    {
        preFilter.setCutoffFrequency(newValue);
    }

    if (parameterID == preFilterResId)
    {
        preFilter.setResonance(newValue);
    }

    if (parameterID == postFilterTypeId)
    {
        if (newValue == 0)
        {
            postFilter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
        }
        else if (newValue == 1)
        {
            postFilter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
        }
        else
        {
            postFilter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
        }
    }

    if (parameterID == postFilterCutoffId)
    {
        postFilter.setCutoffFrequency(newValue);
    }

    if (parameterID == postFilterResId)
    {
        postFilter.setResonance(newValue);
    }


    if (parameterID == themeId)
    {
        currentThemeId = static_cast<int>(newValue);
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
    currentSampleRate = sampleRate;
    currentSamplePerBlock = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();

    dryWet.prepare(spec);
    dryWet.setWetMixProportion(treestate.getRawParameterValue(parameterInfo::dryWetId)->load());

    gainProcessor.prepare(spec);
    gainProcessor.setGainDecibels(treestate.getRawParameterValue(parameterInfo::inputGainId)->load());
    gainProcessor.setRampDurationSeconds(0.02f);

    outputGainProcessor.prepare(spec);
    outputGainProcessor.setGainDecibels(treestate.getRawParameterValue(parameterInfo::outputGainId)->load());
    outputGainProcessor.setRampDurationSeconds(0.02f);

    oversamplingProcessor.initProcessing(samplesPerBlock);

    isOversampled = treestate.getRawParameterValue(parameterInfo::oversamplingId)->load();

    dspProcessor.setSampleRate(sampleRate);
    dspProcessor.updateDcBlockerCoefficient(sampleRate);

    dspProcessor.getSmoothedDrive().reset(sampleRate, 0.25);
    dspProcessor.getSmoothedDrive().setCurrentAndTargetValue(treestate.getRawParameterValue(parameterInfo::driveId)->load());


    preFilter.prepare(spec);
    preFilter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
    preFilter.setCutoffFrequency(treestate.getRawParameterValue(parameterInfo::preFilterCutoffId)->load());
    postFilter.prepare(spec);
    postFilter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
    postFilter.setCutoffFrequency(treestate.getRawParameterValue(parameterInfo::postFilterCutoffId)->load());


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

        if (preFilterIsOn)
        {
            preFilter.process(juce::dsp::ProcessContextReplacing<float>(oversampledBlock));
        }
        gainProcessor.process(juce::dsp::ProcessContextReplacing<float>(oversampledBlock));
        dspProcessor.process(oversampledBlock);
        if (postFilterIsOn)
        {
            postFilter.process(juce::dsp::ProcessContextReplacing<float>(oversampledBlock));
        }
        //DBG("test");

        oversamplingProcessor.processSamplesDown(block);
    }
    else
    {
        if (preFilterIsOn)
        {
            preFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
        }
        gainProcessor.process(juce::dsp::ProcessContextReplacing<float>(block));
        dspProcessor.process(block);
        if (postFilterIsOn)
        {
            postFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
        }
    }

    dryWet.mixWetSamples(block);
    outputGainProcessor.process(juce::dsp::ProcessContextReplacing<float>(block));
}

//==============================================================================
bool FMPDistortionPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FMPDistortionPluginAudioProcessor::createEditor()
{

    return new FMPDistortionPluginAudioProcessorEditor(*this);
    //return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void FMPDistortionPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.




    auto state = treestate.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());

    xml->setAttribute("ThemeID", currentThemeId);
    copyXmlToBinary(*xml, destData);
}

void FMPDistortionPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(treestate.state.getType()))
        {
            treestate.replaceState(juce::ValueTree::fromXml(*xmlState));
            if (xmlState->hasAttribute("ThemeID"))
            {
                currentThemeId = xmlState->getIntAttribute("ThemeID");
            }
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FMPDistortionPluginAudioProcessor();
}
