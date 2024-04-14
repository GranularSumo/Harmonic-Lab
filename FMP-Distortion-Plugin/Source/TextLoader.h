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

    juce::AttributedString createSoftclipperDescription();
    juce::AttributedString createBrokenSoftclipperDescription();
    juce::AttributedString createHardclipperDescription();
    juce::AttributedString createWavefolderDescription();
    juce::AttributedString createFoldbackDescription();
    juce::AttributedString createAsymmetricSoftclipperDescription();
    juce::AttributedString createBiasShaperDescription();
    juce::AttributedString createBiasFolderDescription();
    juce::AttributedString createFoldCrusherDescription();
    juce::AttributedString createDualPathBitFolderDescription();
    juce::AttributedString createBitCrusherDescription();
    juce::AttributedString createDownSamplerDescription();
    juce::AttributedString createSquareFolderDescription();



private:
    juce::String algorithmDescription = "";


    const float plainTextSize = 14.0f;
    const float titleTextSize = 24.0f;
    const float header1Size = 18.0f;

};
