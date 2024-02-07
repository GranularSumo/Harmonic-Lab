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
    void setSampleRate(float sampleRate);

    float arctanSoftClipper(float currentSample);
    float hardClipper(float currentSample);
    float bitCrusher(float currentSample);
    float squareFolder(float currentSample, int channel);
    float wavefolder(float currentSample);
    float wavefolderXs(float currentSample);
    float feedbackWavefolder(float currentSample, int channel);
    float downSample(float currentSample, int channel);
    
    void resetDelaySamples();
    void resetCounters();
    void process(juce::dsp::AudioBlock<float>& block);

    void algorithmSelector(float& sample, int channel);

    juce::LinearSmoothedValue<float>& getSmoothedDrive();


private:
    const float piDivisor = 2.0f / juce::MathConstants<float>::pi;
    float originalSampleRate = 0.0f;
    float alpha = 1.0f;
    float sampleDelay1 = 0.0f;
    float sampleDelay2 = 0.0f;
    int counter1 = 0;
    int counter2 = 0;
    float lastProcessedSample = 0.0f;


    bool procesState = false;

    juce::LinearSmoothedValue<float> smoothedDrive;
    
    enum Algorithm {
        softclip,
        hardclip,
        bitcrush,
        squareFold,
        wavefold,
        wfxs,
        feedbackwavefold,
        downsample,
    };

    Algorithm currentAlgorithm = Algorithm::softclip;

};


