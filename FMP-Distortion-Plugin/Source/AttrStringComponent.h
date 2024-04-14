/*
  ==============================================================================

    AttrStringComponent.h
    Created: 26 Mar 2024 7:59:12pm
    Author:  zeush

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Theme.h"

//==============================================================================
/*
*/
class AttrStringComponent  : public juce::Component
{
public:
    AttrStringComponent();
    ~AttrStringComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setAttributedString(const juce::AttributedString& newAttrString);
    void setTheme(const Theme& currentTheme);
    void setBackgroundColour(const juce::Colour& colour);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AttrStringComponent)

    juce::AttributedString attrString;

    juce::Colour backgroundColour;
    juce::Colour highlightColour;
    juce::Colour shadowColour;
};
