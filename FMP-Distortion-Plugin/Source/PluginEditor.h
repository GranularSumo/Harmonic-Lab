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
#include "ThemeManager.h"


//==============================================================================
/**
*/
class FMPDistortionPluginAudioProcessorEditor : public juce::AudioProcessorEditor, public ThemeChangeListener
{
public:
    FMPDistortionPluginAudioProcessorEditor(FMPDistortionPluginAudioProcessor&);
    ~FMPDistortionPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

    void setTheme(const Theme& currentTheme);
    void themeChanged(int newThemeId) override;


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

    ThemeManager themeManager;

    juce::Colour backgroundColour = themeManager.getCurrentTheme().backgroundColour;
    juce::Colour ShadowColour = themeManager.getCurrentTheme().shadowColour;
    juce::Colour highlightColour = themeManager.getCurrentTheme().highlightColour;
    juce::Colour driveSliderFillColour = themeManager.getCurrentTheme().driveSliderFillColour;
    juce::Colour filterSliderFillColour = themeManager.getCurrentTheme().filterSliderFillColour;
    juce::Colour gainSliderFillColour = themeManager.getCurrentTheme().gainSliderFillColour;
    juce::Colour dryWetMixFillColour = themeManager.getCurrentTheme().mixSliderFillColour;
    juce::Colour sliderBackgroundColour = themeManager.getCurrentTheme().sliderBackgroundColour;
    juce::String themeType = themeManager.getCurrentTheme().ThemeType;

    bool uiModeSwitcher = true;
    bool settingsMenuIsActiveWindow = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FMPDistortionPluginAudioProcessorEditor)
};
