/*
  ==============================================================================

    FocusOverlayComponent.h
    Created: 26 Mar 2024 4:01:47pm
    Author:  zeush

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FocusOverlayComponent  : public juce::Component
{
public:
    FocusOverlayComponent();
    ~FocusOverlayComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setHighlightedAreaBounds(const juce::Rectangle<int>& bounds);
    void addHighlightedAreaBounds(const juce::Rectangle<int>& bounds);
    void clearHighlightedAreas();

    void drawLineToComponent(juce::Rectangle<int> componentBounds);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FocusOverlayComponent)

    std::vector<juce::Rectangle<int>> highlightedAreas;
    std::vector<juce::Line<float>> linesToDraw;
};
