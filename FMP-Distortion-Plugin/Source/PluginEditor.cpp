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

    setTheme(themeManager.getCurrentTheme());

    addAndMakeVisible(uiModeButton);
    uiModeButton.setAlwaysOnTop(true);
    uiModeButton.onClick = [this]()
        {
            // Toggle the mode
            basicModeIsSelected = !basicModeIsSelected;
            audioProcessor.treestate.getParameter(parameterInfo::uiModeId)->setValueNotifyingHost(basicModeIsSelected ? 1.0f : 0.0f);

            // Update UI based on the new state
            if (basicModeIsSelected)
            {
                basicModeUI.setVisible(true);
                advancedModeUI.setVisible(false);
                uiModeButton.setButtonText("Advanced View");
                setSize(basicModeUI.getWidth(), basicModeUI.getHeight());
            }
            else
            {
                basicModeUI.setVisible(false);
                advancedModeUI.setVisible(true);
                uiModeButton.setButtonText("Basic View");
                setSize(advancedModeUI.getWidth(), advancedModeUI.getHeight());
            }
        };

    settingsMenu.setThemeChangeListener(this);


    logo.setAlwaysOnTop(true);
    addAndMakeVisible(logo);

    addAndMakeVisible(basicModeUI);
    addAndMakeVisible(advancedModeUI);
    advancedModeUI.setVisible(false);

    uiSelectorButton.setButtonText("Advanced View");
    uiSelectorButton.onClick = [this]()
        {
            // Toggle the mode
            basicModeIsSelected = !basicModeIsSelected;
            audioProcessor.treestate.getParameter(parameterInfo::uiModeId)->setValueNotifyingHost(basicModeIsSelected ? 1.0f : 0.0f);

            // Update UI based on the new state
            if (basicModeIsSelected)
            {
                basicModeUI.setVisible(true);
                advancedModeUI.setVisible(false);
                uiSelectorButton.setButtonText("Advanced View");
                setSize(basicModeUI.getWidth(), basicModeUI.getHeight());
            }
            else
            {
                basicModeUI.setVisible(false);
                advancedModeUI.setVisible(true);
                uiSelectorButton.setButtonText("Basic View");
                setSize(advancedModeUI.getWidth(), advancedModeUI.getHeight());
            }
        };
    //uiSelectorButton.setAlwaysOnTop(true);
    //addAndMakeVisible(uiSelectorButton);
    
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
                if (basicModeIsSelected)
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
    uiModeButton.setBounds(header.removeFromLeft(header.getWidth() * 0.5f).reduced(100, 20));

    //uiSelectorButton.setBounds(header.removeFromLeft(header.getWidth() * 0.5f).reduced(10));
    settingsButton.setBounds(header.removeFromRight(header.getWidth() * 0.5f).reduced(50, 20));

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
    themeType = themeManager.getCurrentTheme().themeType;


    logo.setTheme(themeManager.getCurrentTheme());
    uiModeButton.setTheme(themeManager.getCurrentTheme());
    basicModeUI.setTheme(themeManager.getCurrentTheme());
    advancedModeUI.setTheme(themeManager.getCurrentTheme());

    repaint();
}

void FMPDistortionPluginAudioProcessorEditor::themeChanged(int newThemeId)
{
    themeManager.switchTheme(static_cast<ThemeManager::ThemeId>(newThemeId));

    setTheme(themeManager.getCurrentTheme());
}


void FMPDistortionPluginAudioProcessorEditor::restoreUiState()
{
    bool uiMode = *audioProcessor.treestate.getRawParameterValue(parameterInfo::uiModeId);
    basicModeIsSelected = uiMode;

    if (basicModeIsSelected)
    {
        basicModeUI.setVisible(true);
        advancedModeUI.setVisible(false);
        uiSelectorButton.setButtonText("Advanced View");
        setSize(basicModeUI.getWidth(), basicModeUI.getHeight());
    }
    else
    {
        advancedModeUI.setVisible(true);
        basicModeUI.setVisible(false);
        uiSelectorButton.setButtonText("Basic View");
        setSize(advancedModeUI.getWidth(), advancedModeUI.getHeight());
    }
    
}

void FMPDistortionPluginAudioProcessorEditor::visibilityChanged()
{
    if (isVisible())
    {
        restoreUiState();
    }
    else
    {
        audioProcessor.treestate.getParameter(parameterInfo::uiModeId)->setValue(basicModeIsSelected);
    }

}








