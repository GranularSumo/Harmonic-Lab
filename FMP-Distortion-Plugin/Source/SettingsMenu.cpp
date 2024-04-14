/*
  ==============================================================================

    Settings.cpp
    Created: 20 Feb 2024 4:58:07pm
    Author:  zeush

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SettingsMenu.h"


//==============================================================================
SettingsMenu::SettingsMenu(FMPDistortionPluginAudioProcessor& processor, float height, float width) : audioProcessor(processor), pluginHeight(height), pluginWidth(width)
{

    themePickerLabel.setText("Themes", juce::dontSendNotification);
    juce::Font h2Font = juce::Font(20.0f, juce::Font::bold);
    themePickerLabel.setFont(h2Font);
    themePickerLabel.setJustificationType(juce::Justification::centred);
    themePicker.onChange = [this] {notifyThemeChange(); };
    addAndMakeVisible(themePickerLabel); // Make the label visible

    themePicker.addSectionHeading("Dark Themes");
    themePicker.addItem("Default", 1);
    themePicker.addItem("Vista", 2);
    themePicker.addSeparator();
    themePicker.addSectionHeading("Light Themes");
    themePicker.addItem("Candy", 3);

    themePickerAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, parameterInfo::themeId, themePicker);

    themePicker.setSelectedId(1, juce::dontSendNotification);
    addAndMakeVisible(themePicker);

    addAndMakeVisible(oversamplingLabel);
    oversamplingLabel.setText("Oversampling", juce::dontSendNotification);
    oversamplingLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(oversamplingNoticeLabel);
    oversamplingNoticeLabel.setText("**Oversampling will increase the quality and reduce aliasing which can be a good thing, but when using quantization based algorithms it will reduce the effect as those algorithms are purposely introducing aliasing.**", juce::dontSendNotification);
    oversamplingNoticeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(oversamplingButton);

    oversamplingAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treestate, parameterInfo::oversamplingId, oversamplingButton);

    setSize(pluginWidth, pluginHeight);
}

SettingsMenu::~SettingsMenu()
{
}

void SettingsMenu::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    auto headerBounds = bounds.removeFromTop(pluginHeight * 0.1f);
    auto footerBounds = bounds.removeFromBottom(pluginHeight * 0.05f);
    auto mainAreaHeight = bounds.getHeight();
    auto row1Bounds = bounds.removeFromTop(mainAreaHeight * 0.2f);
    auto row2Bounds = bounds.removeFromTop(mainAreaHeight * 0.25f);
    auto row3Bounds = bounds.removeFromTop(mainAreaHeight * 0.375f);

}

void SettingsMenu::resized()
{
    auto bounds = getLocalBounds();

    // Common widths and heights
    auto themePickerWidth = 250.0f;
    auto themePickerHeight = 50.0f;
    auto labelHeight = 30; // Height for labels
    auto buttonWidth = 25; // Corrected width for the button
    auto buttonHeight = 25; // Height for the oversamplingButton
    auto gap = 25; // Gap between elements

    // Center positions for all elements, ensuring they use their own widths for accurate centering
    auto themePickerLabelCenterX = bounds.getCentreX() - (themePickerWidth / 2);
    auto themePickerCenterX = bounds.getCentreX() - (themePickerWidth / 2);
    auto oversamplingLabelCenterX = bounds.getCentreX() - (themePickerWidth / 2);
    auto oversamplingButtonCenterX = bounds.getCentreX() - (buttonWidth / 2); // Using buttonWidth to center the button specifically
    auto oversamplingNoticeCentreX = bounds.getCentreX() - (themePickerWidth);

    // Calculate Y positions
    auto themePickerLabelY = bounds.getCentreY() - (themePickerHeight / 2 + labelHeight + gap); // Position themePickerLabel above themePicker
    auto themePickerY = themePickerLabelY + labelHeight + gap; // Position themePicker below its label
    auto oversamplingLabelY = themePickerY + themePickerHeight + gap; // Position oversamplingLabel below themePicker with a gap
    auto oversamplingButtonY = oversamplingLabelY + labelHeight; // Position oversamplingButton directly below oversamplingLabel
    auto oversamplingNoticeY = oversamplingLabelY + labelHeight * 2;

    // Set bounds for themePickerLabel and themePicker centered on the screen
    themePickerLabel.setBounds(themePickerLabelCenterX, themePickerLabelY, themePickerWidth, labelHeight);
    themePicker.setBounds(themePickerCenterX, themePickerY, themePickerWidth, themePickerHeight);

    // Set bounds for oversamplingLabel centered on the screen
    oversamplingLabel.setBounds(oversamplingLabelCenterX, oversamplingLabelY, themePickerWidth, labelHeight);

    // Set bounds for oversamplingButton centered based on its own width
    oversamplingButton.setBounds(oversamplingButtonCenterX, oversamplingButtonY, buttonWidth, buttonHeight);

    oversamplingNoticeLabel.setBounds(oversamplingNoticeCentreX, oversamplingNoticeY, themePickerWidth * 2, themePickerHeight);
}

void SettingsMenu::setTheme(const Theme& currentTheme)
{
    backgroundColour = currentTheme.backgroundColour;
    shadowColour = currentTheme.shadowColour;
    lineHighlightColour = currentTheme.highlightColour;
	repaint();
}

void SettingsMenu::setThemeChangeListener(ThemeChangeListener* listener)
{
    themeChangeListener = listener;
}

void SettingsMenu::notifyThemeChange()
{
    if (themeChangeListener != nullptr && themePicker.getSelectedId() > 0) {
        themeChangeListener->themeChanged(themePicker.getSelectedId() - 1);
    }
}