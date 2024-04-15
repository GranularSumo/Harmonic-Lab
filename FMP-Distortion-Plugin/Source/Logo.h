/*
  ==============================================================================

    Logo.h
    Created: 6 Feb 2024 4:47:14pm
    Author:  zeush

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Theme.h"

//==============================================================================
/*
*/
class Logo  : public juce::Component
{
public:
    Logo();
    ~Logo() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void mouseEnter(const juce::MouseEvent& event) override;
    void mouseExit(const juce::MouseEvent& event) override;
    void mouseDown(const juce::MouseEvent& event) override;

    void setTheme(const Theme& currentTheme);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Logo)

    bool isMouseOver = false;
    juce::Colour logoColour;
};
