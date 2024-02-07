/*
  ==============================================================================

    TextLoader.h
    Created: 7 Feb 2024 10:45:59am
    Author:  zeush

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class TextLoader
{
public:
    void setAlgorithm(juce::String algorithm);
    juce::String getAlgorithmDescription(juce::String algorithm);


private:
    juce::String algorithmDescription = "";


};
