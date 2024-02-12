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

    uiSelectorButton.setColour(juce::TextButton::buttonColourId, juce::Colour::fromString("#ff253353"));
    uiSelectorButton.setButtonText("Advanced View");
    uiSelectorButton.onClick = [this]()
        {
            if (uiModeSwitcher)
            {
                removeChildComponent(&basicModeUI);
                setSize(advancedModeUI.getWidth(), advancedModeUI.getHeight());
                addAndMakeVisible(advancedModeUI);
                uiModeSwitcher = false;
                uiSelectorButton.setButtonText("Basic View");
            }
            else
            {
                removeChildComponent(&advancedModeUI);
                setSize(basicModeUI.getWidth(), basicModeUI.getHeight());
                addAndMakeVisible(basicModeUI);
                uiModeSwitcher = true;
                uiSelectorButton.setButtonText("Advanced View");
            }
        };
    uiSelectorButton.setAlwaysOnTop(true);
    addAndMakeVisible(uiSelectorButton);
    
    
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
    uiSelectorButton.setBounds(header.removeFromRight(pluginWidth * 0.2).reduced(10));

    // set the bounds for the UI container components.
    advancedModeUI.setBounds(getLocalBounds());
    basicModeUI.setBounds(getLocalBounds());

}






