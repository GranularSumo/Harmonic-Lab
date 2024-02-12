/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Parameters.h"
#include "Dsp.h"

//==============================================================================
/**
*/
class FMPDistortionPluginAudioProcessor  : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    FMPDistortionPluginAudioProcessor();
    ~FMPDistortionPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState treestate;

private:


    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged(const juce::String& parameterID, float newValue) override;

    juce::dsp::Gain<float> gainProcessor;
    Dsp dspProcessor;
    juce::dsp::Oversampling<float> oversamplingProcessor;
    juce::dsp::DryWetMixer<float> dryWet;
    juce::dsp::StateVariableTPTFilter<float> preFilter;
    juce::dsp::StateVariableTPTFilter<float> postFilter;
    

    bool isOversampled{ false };
    bool preFilterIsOn{ false };
    bool postFilterIsOn{ false };

    juce::dsp::ProcessSpec spec;
    double currentSampleRate = 0.0;
    int currentSamplePerBlock = 0;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FMPDistortionPluginAudioProcessor)
};
