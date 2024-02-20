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
#include "BasicModeUI.h"
#include "AdvancedModeUI.h"
#include "Settings.h"


//==============================================================================
/**
*/
class FMPDistortionPluginAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    FMPDistortionPluginAudioProcessorEditor(FMPDistortionPluginAudioProcessor&);
    ~FMPDistortionPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FMPDistortionPluginAudioProcessor& audioProcessor;

    const float pluginWidth = 900.0f;
    const float pluginHeight = 675.0f;

    juce::TextButton uiSelectorButton;
    juce::TextButton settingsButton;

    Logo logo;

    BasicModeUI basicModeUI = BasicModeUI(audioProcessor, pluginHeight, pluginWidth);
    AdvancedModeUI advancedModeUI = AdvancedModeUI(audioProcessor, pluginHeight, pluginWidth);
    Settings settingsMenu = Settings(pluginHeight, pluginWidth);

    juce::Colour backgroundColour = juce::Colour::fromString("#ff253353");
    juce::Colour ShadowColour = juce::Colour::fromString("#ff222A3E");
    juce::Colour lineHighlightColour = juce::Colour::fromString("#ff47526D");

    
    juce::Colour sliderBackgroundColour = juce::Colour::fromString("#ff1A2039");

    juce::Colour driveSliderFillColour = juce::Colour::fromString("#ffDC603C");

    juce::Colour filterSliderFillColour = juce::Colour::fromString("#ff8371C3");

    juce::Colour gainSliderFillColour = juce::Colour::fromString("#ffBF4467");

    juce::Colour dryWetMixFillColour = juce::Colour::fromString("#ffB1C371");

    bool uiModeSwitcher = true;
    bool settingsMenuIsActiveWindow = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FMPDistortionPluginAudioProcessorEditor)
};
