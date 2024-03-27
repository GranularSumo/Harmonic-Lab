/*
  ==============================================================================

    Settings.h
    Created: 20 Feb 2024 4:58:07pm
    Author:  zeush

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/

class ThemeChangeListener
{
public:
    virtual ~ThemeChangeListener() = default;
    virtual void themeChanged(int newThemeId) = 0;
};

class SettingsMenu : public juce::Component
{
public:
    SettingsMenu(FMPDistortionPluginAudioProcessor& processor, float height, float width);
    ~SettingsMenu() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void setTheme(const Theme& currentTheme);

    void setThemeChangeListener(ThemeChangeListener* listener);
    void notifyThemeChange();

private:
    FMPDistortionPluginAudioProcessor& audioProcessor;

    ThemeChangeListener* themeChangeListener = nullptr;

    const float pluginWidth;
    const float pluginHeight;

    juce::Label themePickerLabel;
    juce::ComboBox themePicker;
    juce::ToggleButton oversampling;

    juce::Colour backgroundColour;
    juce::Colour shadowColour;
    juce::Colour lineHighlightColour;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> themePickerAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsMenu)
};