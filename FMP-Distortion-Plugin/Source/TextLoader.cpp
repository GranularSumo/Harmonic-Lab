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
        algorithmDescription = "this is a test to see if softclip is working.";
    }
    else if (algorithm == "Hardclipper")
    {
        algorithmDescription = "this is a test to see if hardclip is working.";
    }
    else if (algorithm == "BitCrusher")
    {
        algorithmDescription = "this is a test to see if bitcrush is working.";
    }
    else if (algorithm == "SquareFolder")
    {
        algorithmDescription = "test";
    }
    else if (algorithm == "WaveShaper")
    {
        algorithmDescription = "this is a test to see if wavefold is working.";
    }
    else if (algorithm == "WaveShaped-Clipper")
    {
        algorithmDescription = "this is a test to see if wfxs is working.";
    }
    else if (algorithm == "Feedback-Waveshaper")
    {
        algorithmDescription = "this is a test to see if feedbackwavefold is working.";
    }
    else if (algorithm == "Downsample")
    {
        algorithmDescription = "this is a test to see if chaos is working.";
    }

}

juce::String TextLoader::getAlgorithmDescription(juce::String algorithm)
{
    setAlgorithm(algorithm);
    return algorithmDescription;
}
