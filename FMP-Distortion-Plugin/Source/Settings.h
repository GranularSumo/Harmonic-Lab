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
class Settings  : public juce::Component
{
public:
    Settings(float height, float width);
    ~Settings() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    const float pluginWidth;
    const float pluginHeight;

    juce::Label themePickerLabel;
    juce::ComboBox themePicker;
    juce::ToggleButton oversampling;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Settings)
};
