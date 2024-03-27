/*
  ==============================================================================

    AdvancedModeDescriptionSection.cpp
    Created: 23 Feb 2024 5:47:59pm
    Author:  zeush

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdvancedModeDescriptionSection.h"

//==============================================================================
AdvancedModeDescriptionSection::AdvancedModeDescriptionSection()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(descriptionBox);
    descriptionBox.setMultiLine(true);
    descriptionBox.setReadOnly(true);
    descriptionBox.setScrollbarsShown(true);
    descriptionBox.setCaretVisible(false);

    addAndMakeVisible(descriptionLabel);
    descriptionLabel.setText("Algorithm Description", juce::dontSendNotification);
    descriptionLabel.setJustificationType(juce::Justification::centred);
    juce::Font font(20.0f, juce::Font::bold);
    descriptionLabel.setFont(font);


}

AdvancedModeDescriptionSection::~AdvancedModeDescriptionSection()
{
}

void AdvancedModeDescriptionSection::paint (juce::Graphics& g)
{
    g.fillAll(backgroundColour.brighter(0.05f));
}

void AdvancedModeDescriptionSection::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto bounds = getLocalBounds();
    auto yOffSet = 50;
    auto descriptionBoxAdjustedBounds = bounds.reduced(10, yOffSet);
    descriptionBox.setBounds(descriptionBoxAdjustedBounds.getX(), descriptionBoxAdjustedBounds.getY(), descriptionBoxAdjustedBounds.getWidth(), descriptionBoxAdjustedBounds.getHeight() + yOffSet - 10);

    descriptionLabel.setBounds(bounds.removeFromTop(50.0f));

}

void AdvancedModeDescriptionSection::setDescription(juce::String& algorithm)
{
    descriptionBox.setText(textLoader.getAlgorithmDescription(algorithm), juce::dontSendNotification);
}

void AdvancedModeDescriptionSection::setTheme(const Theme& currentTheme)
{
    backgroundColour = currentTheme.backgroundColour;
    textColour = currentTheme.textColour;
    highlightColour = currentTheme.highlightColour;
    shadowColour = currentTheme.shadowColour;

    descriptionBox.setColour(juce::TextEditor::backgroundColourId, backgroundColour);
    descriptionBox.setColour(juce::TextEditor::textColourId, textColour);
    descriptionBox.setColour(juce::TextEditor::outlineColourId, highlightColour);
}
