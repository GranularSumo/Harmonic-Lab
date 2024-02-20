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
    advancedModeUI.setBackgroundColour(backgroundColour);
    advancedModeUI.setShadowColour(ShadowColour);
    advancedModeUI.setLineHighlightColour(lineHighlightColour);
    advancedModeUI.setDriveSliderColours(driveSliderFillColour, sliderBackgroundColour);
    advancedModeUI.setFilterSliderColours(filterSliderFillColour, sliderBackgroundColour);
    advancedModeUI.setGainSliderColours(gainSliderFillColour, sliderBackgroundColour);
    advancedModeUI.setMixSliderColours(dryWetMixFillColour, sliderBackgroundColour);

    basicModeUI.setBackgroundColour(backgroundColour);
    basicModeUI.setShadowColour(ShadowColour);
    basicModeUI.setLineHighlightColour(lineHighlightColour);
    basicModeUI.setDriveSliderColours(driveSliderFillColour, sliderBackgroundColour);

    

    logo.setAlwaysOnTop(true);
    addAndMakeVisible(logo);

    addAndMakeVisible(basicModeUI);
    addAndMakeVisible(advancedModeUI);
    advancedModeUI.setVisible(false);

    uiSelectorButton.setColour(juce::TextButton::buttonColourId, juce::Colour::fromString("#ff253353"));
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






