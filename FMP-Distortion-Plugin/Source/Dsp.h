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
    void setProcessState();

    float arctanSoftClipper(float currentSample, float amount);
    float hardClipper(float currentSample, float amount);
    float bitcrusher(float currentSample, float bitDepth);
    float wavefolder(float currentSample, float amount);

    void process(juce::dsp::AudioBlock<float>& block);

    void algorithmSelector(float& sample);


private:
    const float piDivisor = juce::MathConstants<float>::halfPi;

    bool procesState = false;
    
    enum Algorithm {
        softclip,
        hardclip,
        bitcrush,
        wavefolde
    };

    Algorithm currentAlgorithm = Algorithm::softclip;

};


