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
    themePicker.onChange = [this] {notifyThemeChange(); };
    addAndMakeVisible(themePickerLabel); // Make the label visible

    themePicker.addSectionHeading("Dark Themes");
    themePicker.addItem("Default", 1);
    themePicker.addItem("Vista", 2);
    themePicker.addSeparator();
    themePicker.addSectionHeading("Light Themes");

    themePickerAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, parameterInfo::themeId, themePicker);

    themePicker.setSelectedId(1, juce::dontSendNotification);
    addAndMakeVisible(themePicker);

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

    oversampling.setBounds(bounds.getCentreX(), bounds.getCentreY(), 100, 100);


    auto themePickerWidth = 250.0f;
    auto themePickerHeight = 50.0f;

    themePickerLabel.setBounds(100, 100, 250, 30);
    themePicker.setBounds(bounds.getCentreX() - (themePickerWidth * 0.5), bounds.getY() + 50 + themePickerHeight, themePickerWidth, themePickerHeight);
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