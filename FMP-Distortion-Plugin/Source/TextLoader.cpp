/*
  ==============================================================================

    TextLoader.cpp
    Created: 7 Feb 2024 10:45:59am
    Author:  zeush

  ==============================================================================
*/

#include "TextLoader.h"

void TextLoader::setAlgorithm(juce::String algorithm)
{
    if (algorithm == "Softclipper")
    {
        algorithmDescription = "This is the Softclip Algorithm.";
    }
    else if (algorithm == "Hardclipper")
    {
        algorithmDescription = "This is the Hardclip Algorithm.";
    }
    else if (algorithm == "BitCrusher")
    {
        algorithmDescription = "This is the Bitcrush Algorithm.";
    }
    else if (algorithm == "SquareFolder")
    {
        algorithmDescription = "This is the Squarefold Algorithm.";
    }
    else if (algorithm == "WaveShaper")
    {
        algorithmDescription = "This is the Waveshaper Algorithm.";
    }
    else if (algorithm == "Feedback-Waveshaper")
    {
        algorithmDescription = "This is the Feedback-Waveshaper Algorithm.";
    }
    else if (algorithm == "Downsample")
    {
        algorithmDescription = "This is the Downsample Algorithm.";
    }

}

juce::String TextLoader::getAlgorithmDescription(juce::String algorithm)
{
    setAlgorithm(algorithm);
    return algorithmDescription;
}
