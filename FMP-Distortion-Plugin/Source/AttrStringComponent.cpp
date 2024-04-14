/*
  ==============================================================================

    AttrStringComponent.cpp
    Created: 26 Mar 2024 7:59:12pm
    Author:  zeush

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AttrStringComponent.h"

//==============================================================================
AttrStringComponent::AttrStringComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

AttrStringComponent::~AttrStringComponent()
{
}

void AttrStringComponent::paint (juce::Graphics& g)
{

    g.fillAll(backgroundColour);

    auto bounds = getLocalBounds();

    int padding = 10;
    auto paddedBounds = bounds.reduced(padding);


    attrString.draw(g, paddedBounds.toFloat());
}

void AttrStringComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void AttrStringComponent::setAttributedString(const juce::AttributedString& newAttrString)
{
    attrString = newAttrString;
    repaint();
}

void AttrStringComponent::setTheme(const Theme& currentTheme)
{
    backgroundColour = currentTheme.backgroundColour;
    shadowColour = currentTheme.shadowColour;
    highlightColour = currentTheme.highlightColour;
}

void AttrStringComponent::setBackgroundColour(const juce::Colour& colour)
{
    backgroundColour = colour;
    repaint();
}
