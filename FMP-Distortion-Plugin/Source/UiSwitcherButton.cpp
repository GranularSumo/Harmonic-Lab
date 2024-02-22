/*
  ==============================================================================

    UiSwitcherButton.cpp
    Created: 21 Feb 2024 9:24:26pm
    Author:  zeush

  ==============================================================================
*/

#include <JuceHeader.h>
#include "UiSwitcherButton.h"

//==============================================================================


UiSwitcherButton::~UiSwitcherButton()
{
}

void UiSwitcherButton::setTheme(const Theme& currentTheme)
{
    highlightColour = currentTheme.highlightColour;
    shadowColour = currentTheme.shadowColour;
    textColour = currentTheme.textColour;
   
}


void UiSwitcherButton::paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    auto bounds = getLocalBounds().toFloat();
    auto rectangleCornerRadius = 15.0f; // corner radius
    auto intendedStrokeWidth = 1.0f; // Width of the "outline"

    // define the gradients to draw the shapes
    auto outlineTopPoint = juce::Point<float>(getLocalBounds().getCentreX(), getLocalBounds().getY());
    auto outlineBottomPoint = juce::Point<float>(getLocalBounds().getCentreX(), getLocalBounds().getBottom());
    auto outlineGradient = juce::ColourGradient(highlightColour.brighter(0.5f), outlineTopPoint, shadowColour.darker(1.5f), outlineBottomPoint, false);
    auto fillGradient = juce::ColourGradient(shadowColour.darker(0.1f), outlineBottomPoint, highlightColour, outlineTopPoint, false);

    // Adjust the fill gradient based on the button state
    if (shouldDrawButtonAsDown) {
        // Make the gradient brighter for the 'down' state
        fillGradient = juce::ColourGradient(shadowColour.darker(0.3f), outlineBottomPoint, highlightColour.darker(0.1f), outlineTopPoint, false);
    }
    else if (shouldDrawButtonAsHighlighted) {
        // Make the gradient slightly brighter for the 'highlighted' state
        fillGradient = juce::ColourGradient(shadowColour.brighter(0.1f), outlineBottomPoint, highlightColour.brighter(0.1f), outlineTopPoint, false);
    }

    // Calculate the bounds for the gradient "outline" shape
    // This makes the rectangle 1 pixel larger on all sides
    auto gradientOutlineBounds = bounds.expanded(intendedStrokeWidth);

    // Fill the main shape
    g.setGradientFill(fillGradient);
    g.fillRoundedRectangle(bounds.reduced(intendedStrokeWidth), rectangleCornerRadius);

    // Draw the outline around the main shape
    g.setGradientFill(outlineGradient);
    g.drawRoundedRectangle(bounds.reduced(intendedStrokeWidth / 2), rectangleCornerRadius, intendedStrokeWidth);

    // Draw the button text with padding
    g.setFont(getFont());
    g.setColour(textColour); // Text color
    g.drawText(getButtonText(), getLocalBounds(), juce::Justification::centred, true);

}




juce::Font UiSwitcherButton::getFont()
{
    return juce::Font(16.0f); // Customize your font size here
}
