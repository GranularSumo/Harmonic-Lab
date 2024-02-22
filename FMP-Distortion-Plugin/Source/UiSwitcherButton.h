/*
  ==============================================================================

    UiSwitcherButton.h
    Created: 21 Feb 2024 9:24:26pm
    Author:  zeush

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Theme.h"

//==============================================================================
/*
*/
class UiSwitcherButton  : public juce::Button
{
public:
    UiSwitcherButton(const juce::String& buttonText) : juce::Button(buttonText) {};
    ~UiSwitcherButton() override;

    void setTheme(const Theme& currentTheme);

protected :
    void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    juce::Font getFont();

private:
    juce::Colour highlightColour;
    juce::Colour shadowColour;
    juce::Colour textColour;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UiSwitcherButton)
};
