/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"

//==============================================================================
FMPDistortionPluginAudioProcessorEditor::FMPDistortionPluginAudioProcessorEditor (FMPDistortionPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    settingsMenu.setThemeChangeListener(this);
    setTheme(themeManager.getCurrentTheme());

    logo.setAlwaysOnTop(true);
    addAndMakeVisible(logo);

    addAndMakeVisible(basicModeUI);
    addAndMakeVisible(advancedModeUI);
    advancedModeUI.setVisible(false);

    uiSelectorButton.setButtonText("Advanced View");
    uiSelectorButton.onClick = [this]()
        {
            if (uiModeSwitcher)
            {
                basicModeUI.setVisible(false);
                advancedModeUI.setVisible(true);
                uiModeSwitcher = false;
                uiSelectorButton.setButtonText("Basic View");
            }
            else
            {
                advancedModeUI.setVisible(false);
                basicModeUI.setVisible(true);
                uiModeSwitcher = true;
                uiSelectorButton.setButtonText("Advanced View");
            }
        };
    uiSelectorButton.setAlwaysOnTop(true);
    addAndMakeVisible(uiSelectorButton);
    
    settingsButton.setButtonText("Settings");
    settingsButton.onClick = [this]()
        {
            if (!settingsMenuIsActiveWindow)
            {
                // Hide both UIs and show settings menu
                basicModeUI.setVisible(false);
                advancedModeUI.setVisible(false);
                uiSelectorButton.setVisible(false);
                addAndMakeVisible(settingsMenu);
                settingsButton.setButtonText("Close");
                settingsMenuIsActiveWindow = true; // Update flag
            }
            else
            {
                // Hide settings menu
                uiSelectorButton.setVisible(true);
                settingsMenu.setVisible(false);
                settingsButton.setButtonText("Settings");

                // Return to the appropriate UI based on `uiModeSwitcher`
                if (uiModeSwitcher)
                {
                    basicModeUI.setVisible(true);
                    setSize(basicModeUI.getWidth(), basicModeUI.getHeight());
                }
                else
                {
                    advancedModeUI.setVisible(true);
                    setSize(advancedModeUI.getWidth(), advancedModeUI.getHeight());
                }
                settingsMenuIsActiveWindow = false; // Update flag
            }

        };
    settingsButton.setAlwaysOnTop(true);
    addAndMakeVisible(settingsButton);

    
    setSize (basicModeUI.getWidth(), basicModeUI.getHeight());
}

FMPDistortionPluginAudioProcessorEditor::~FMPDistortionPluginAudioProcessorEditor()
{
}

//==============================================================================
void FMPDistortionPluginAudioProcessorEditor::paint (juce::Graphics& g)
{

}

void FMPDistortionPluginAudioProcessorEditor::resized()
{
    auto header = getLocalBounds().removeFromTop(pluginHeight * 0.1f);

    // set bounds for the constant elements.
    logo.setBounds(header.removeFromLeft(pluginWidth * 0.2).reduced(10));
    uiSelectorButton.setBounds(header.removeFromLeft(header.getWidth() * 0.5f).reduced(10));
    settingsButton.setBounds(header.removeFromRight(header.getWidth() * 0.5f));

    // set the bounds for the UI container components.
    advancedModeUI.setBounds(getLocalBounds());
    basicModeUI.setBounds(getLocalBounds());



}

void FMPDistortionPluginAudioProcessorEditor::setTheme(const Theme& currentTheme)
{
    backgroundColour = themeManager.getCurrentTheme().backgroundColour;
    ShadowColour = themeManager.getCurrentTheme().shadowColour;
    highlightColour = themeManager.getCurrentTheme().highlightColour;
    driveSliderFillColour = themeManager.getCurrentTheme().driveSliderFillColour;
    filterSliderFillColour = themeManager.getCurrentTheme().filterSliderFillColour;
    gainSliderFillColour = themeManager.getCurrentTheme().gainSliderFillColour;
    dryWetMixFillColour = themeManager.getCurrentTheme().mixSliderFillColour;
    sliderBackgroundColour = themeManager.getCurrentTheme().sliderBackgroundColour;
    themeType = themeManager.getCurrentTheme().ThemeType;


    logo.setTheme(themeManager.getCurrentTheme());
    basicModeUI.setTheme(themeManager.getCurrentTheme());
    advancedModeUI.setTheme(themeManager.getCurrentTheme());

    repaint();
}

void FMPDistortionPluginAudioProcessorEditor::themeChanged(int newThemeId)
{
    themeManager.switchTheme(static_cast<ThemeManager::ThemeId>(newThemeId));

    setTheme(themeManager.getCurrentTheme());
}








