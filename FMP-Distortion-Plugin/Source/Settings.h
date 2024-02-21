/*
  ==============================================================================

    Settings.h
    Created: 20 Feb 2024 4:58:07pm
    Author:  zeush

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/

class ThemeChangeListener
{
public:
    virtual ~ThemeChangeListener() = default;
    virtual void themeChanged(int newThemeId) = 0;
};

class Settings  : public juce::Component
{
public:
    Settings(float height, float width);
    ~Settings() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setThemeChangeListener(ThemeChangeListener* listener);
    void notifyThemeChange();

private:
    ThemeChangeListener* themeChangeListener = nullptr;

    const float pluginWidth;
    const float pluginHeight;

    juce::Label themePickerLabel;
    juce::ComboBox themePicker;
    juce::ToggleButton oversampling;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> themePickerAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Settings)
};


