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
#include "SettingsMenu.h"
#include "ThemeManager.h"
#include "UiSwitcherButton.h"
#include "AdvancedModeDescriptionSection.h"
#include "TutorialSection.h"


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
    int getTheme(int themeId);
    ThemeManager& getThemeManager();
    void themeChanged(int newThemeId) override;


    void restoreUiState();

    void visibilityChanged() override;

protected:
    


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FMPDistortionPluginAudioProcessor& audioProcessor;

    const float pluginWidth = 900.0f;
    const float advancedModePluginWidthOffset = 300.0f;
    const float pluginHeight = 675.0f;

    juce::TextButton uiSelectorButton;
    juce::TextButton settingsButton;

    Logo logo;

    BasicModeUI basicModeUI = BasicModeUI(audioProcessor, pluginHeight, pluginWidth);
    AdvancedModeUI advancedModeUI = AdvancedModeUI(audioProcessor, pluginHeight, pluginWidth);
    SettingsMenu settingsMenu = SettingsMenu(audioProcessor, pluginHeight, pluginWidth);

    UiSwitcherButton uiModeButton = UiSwitcherButton("Basic");

    ThemeManager themeManager;
    

    AdvancedModeDescriptionSection descriptionSection;
    TutorialSection tutorialSection;

    juce::Colour backgroundColour = themeManager.getCurrentTheme().backgroundColour;
    juce::Colour shadowColour = themeManager.getCurrentTheme().shadowColour;
    juce::Colour highlightColour = themeManager.getCurrentTheme().highlightColour;
    juce::Colour driveSliderFillColour = themeManager.getCurrentTheme().driveSliderFillColour;
    juce::Colour filterSliderFillColour = themeManager.getCurrentTheme().filterSliderFillColour;
    juce::Colour gainSliderFillColour = themeManager.getCurrentTheme().gainSliderFillColour;
    juce::Colour dryWetMixFillColour = themeManager.getCurrentTheme().mixSliderFillColour;
    juce::Colour sliderBackgroundColour = themeManager.getCurrentTheme().sliderBackgroundColour;
    juce::String themeType = themeManager.getCurrentTheme().themeType;

    bool basicModeIsSelected = true;
    bool settingsMenuIsActiveWindow = false;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FMPDistortionPluginAudioProcessorEditor)
};
