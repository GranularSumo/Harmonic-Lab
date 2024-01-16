/*
  ==============================================================================

    Dsp.h
    Created: 5 Dec 2023 3:40:01pm
    Author:  zeush

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Dsp
{
public:
    void setDistortionType(juce::String newValue);
    void setDriveAmount(float amount);

    float arctanSoftClipper(float currentSample);
    float hardClipper(float currentSample);
    float bitcrusher(float currentSample, float bitDepth);
    float wavefolder(float currentSample);
    float wavefolderXs(float currentSample);
    float feedbackWavefolder(float currentSample, int channel);

    void process(juce::dsp::AudioBlock<float>& block);

    void algorithmSelector(float& sample, int channel);


private:
    const float piDivisor = 2.0f / juce::MathConstants<float>::pi;
    float alpha = 1.0f;
    float sampleDelay1 = 0.0f;
    float sampleDelay2 = 0.0f;

    bool procesState = false;
    
    enum Algorithm {
        softclip,
        hardclip,
        bitcrush,
        wavefold,
        wfxs,
        feedbackWavefold,

    };

    Algorithm currentAlgorithm = Algorithm::softclip;

};


