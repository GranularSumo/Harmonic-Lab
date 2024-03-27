/*
  ==============================================================================

    AdvancedModeDescriptionSection.h
    Created: 23 Feb 2024 5:47:59pm
    Author:  zeush

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Theme.h"
#include "TextLoader.h"

//==============================================================================
/*
*/
class AdvancedModeDescriptionSection  : public juce::Component
{
public:
    AdvancedModeDescriptionSection();
    ~AdvancedModeDescriptionSection() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setDescription(juce::String& algorithm);

    void setTheme(const Theme& currentTheme);

private:

    juce::TextEditor descriptionBox;
    juce::Label descriptionLabel;

    TextLoader textLoader;

    juce::Colour backgroundColour;
    juce::Colour textColour;
    juce::Colour highlightColour;
    juce::Colour shadowColour;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdvancedModeDescriptionSection)
};
