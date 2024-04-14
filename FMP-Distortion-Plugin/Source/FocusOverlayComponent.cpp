/*
  ==============================================================================

    FocusOverlayComponent.cpp
    Created: 26 Mar 2024 4:01:47pm
    Author:  zeush

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FocusOverlayComponent.h"

//==============================================================================
FocusOverlayComponent::FocusOverlayComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

FocusOverlayComponent::~FocusOverlayComponent()
{
}

void FocusOverlayComponent::paint(juce::Graphics& g)
{
    auto area = getLocalBounds();

    int borderWidth = 2; // Define the border width
    g.setColour(juce::Colours::white); // Border colour

    g.setColour(juce::Colours::white); // Set to desired line colour
    for (const auto& line : linesToDraw) {
        g.drawLine(line, borderWidth); // Assuming 'borderWidth' is your desired line width
    }

    // The endpoint for lines is the center of the right side of the screen
    juce::Point<float> lineEnd(area.getRight() - 1, area.getCentreY()); // -1 to ensure it's within bounds

    // For each highlighted area
    for (const auto& bounds : highlightedAreas) {
        // Calculate the starting point for the line as the right middle of the highlighted area
        juce::Point<float> lineStart(bounds.getRight(), bounds.getCentreY());

        // Draw the line from the right side border of the highlighted area to the right side of the screen
        g.drawLine(lineStart.getX(), lineStart.getY(), lineEnd.getX(), lineEnd.getY(), borderWidth);

        // Make the exclusion area smaller to leave space for the border
        auto innerBounds = bounds.reduced(borderWidth / 2);
        g.excludeClipRegion(innerBounds); // Exclude a slightly smaller area

        // Draw the border around the original bounds
        g.drawRect(bounds, borderWidth); // Draw the border with the specified thickness
    }



    // Re-fill the overlay, which will respect the excluded regions
    g.fillAll(juce::Colours::black.withAlpha(0.7f));
}

void FocusOverlayComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void FocusOverlayComponent::setHighlightedAreaBounds(const juce::Rectangle<int>& bounds)
{
    highlightedAreas.push_back(bounds);
    repaint();
}

void FocusOverlayComponent::addHighlightedAreaBounds(const juce::Rectangle<int>& bounds)
{
    highlightedAreas.push_back(bounds);
    repaint();
}

void FocusOverlayComponent::clearHighlightedAreas()
{
    highlightedAreas.clear();
    linesToDraw.clear();
    repaint();
}

void FocusOverlayComponent::drawLineToComponent(juce::Rectangle<int> componentBounds)
{
    // Assuming componentBounds is already in local coordinates relative to this component
    // If not, you will need to adjust its position based on this component's position.

    // Find the center of the right-hand side of this component
    auto thisRightCenter = juce::Point<float>(getLocalBounds().getRight(), getHeight() / 2.0f);

    // Find the center of the right-hand side of the passed bounds
    auto targetRightCenter = juce::Point<float>(componentBounds.getRight(), componentBounds.getY() + componentBounds.getHeight() / 2.0f);

    // Create a line between these two points
    juce::Line<float> line(thisRightCenter, targetRightCenter);

    // Store the line
    linesToDraw.push_back(line);

    // Request a repaint to draw the new line
    repaint();
}

