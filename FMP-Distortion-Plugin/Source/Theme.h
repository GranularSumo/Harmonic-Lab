/*
  ==============================================================================

    Theme.h
    Created: 20 Feb 2024 10:28:37pm
    Author:  zeush

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

struct Theme {
    juce::Colour backgroundColour;
    juce::Colour shadowColour;
    juce::Colour highlightColour;
    juce::Colour driveSliderFillColour;
    juce::Colour filterSliderFillColour;
    juce::Colour mixSliderFillColour;
    juce::Colour gainSliderFillColour;
    juce::Colour sliderBackgroundColour;
    juce::Colour textColour;
    juce::String themeType;

    Theme() = default;

    Theme(
        const juce::Colour& bgColour,
        const juce::Colour& shadow,
        const juce::Colour& highlight,
        const juce::Colour& driveFill,
        const juce::Colour& filterFill,
        const juce::Colour& mixFill,
        const juce::Colour& gainFill,
        const juce::Colour& sliderBg,
        const juce::Colour& textColour,
        const juce::String& type)
        :
        backgroundColour(bgColour),
        shadowColour(shadow),
        highlightColour(highlight),
        driveSliderFillColour(driveFill),
        filterSliderFillColour(filterFill),
        mixSliderFillColour(mixFill),
        gainSliderFillColour(gainFill),
        sliderBackgroundColour(sliderBg),
        textColour(textColour),
        themeType(type)
        {}

};