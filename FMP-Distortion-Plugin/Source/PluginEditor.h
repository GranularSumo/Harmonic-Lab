/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Logo.h"
#include "TextLoader.h"

//==============================================================================
/**
*/
class FMPDistortionPluginAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::ComboBox::Listener
{
public:
    FMPDistortionPluginAudioProcessorEditor (FMPDistortionPluginAudioProcessor&);
    ~FMPDistortionPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void comboBoxChanged(juce::ComboBox* comboBox) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FMPDistortionPluginAudioProcessor& audioProcessor;

    const float pluginWidth = 900.0f;
    const float pluginHeight = 675.0f;


    juce::Slider distortionSlider;
    juce::ComboBox algorithmSelector;
    juce::Label infoBoxTitle;
    juce::TextEditor infoBox;
    juce::TextButton uiSelectorButton;

    Logo logo;
    TextLoader textLoader;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> distortionAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> selectorAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FMPDistortionPluginAudioProcessorEditor)
};
