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
    Dsp();
    enum Algorithm {
        softclip,
        brokenSoftclip,
        hardclip,
        wavefold,
        foldback,
        asymetricSoftclip,
        biasShape,
        biasFold,
        foldCrush,
        dualPathBitFold,
        bitcrush,
        squarefold,
        downsample,
    };

    void setDistortionType(Algorithm algorithm);
    void setDriveAmount(float amount);
    void setSampleRate(float sampleRate);

    void updateDcBlockerCoefficient(float sampleRate);
    float processDcBlocker(float sample, int channel);


    // odd harmonic algorithms
    float softClipper(float currentSample);
    float brokenSoftclipper(float currentSample);
    float hardClipper(float currentSample);
    float wavefolder(float currentSample);
    float saturatedWavefolder(float currentSample);
    float feedbackWavefolder(float currentSample, int channel);


    //even harmonic algorithms
    float asymetricSoftClipper(float currentSample);
    float BiasShaper(float currentSample);
    float BiasFolder(float currentSample, int channel);
    float foldCrusher(float currentSample, int channel);
    float dualPathBitFolder(float currentSample, int channel);

    // quantization algorithms
    float bitCrusher(float currentSample);
    float squareFolder(float currentSample, int channel);
    float downSampler(float currentSample, int channel);




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

    float phase = 0.0f;

    bool dcFilterOn = true;
    bool procesState = false;

    juce::LinearSmoothedValue<float> smoothedDrive;
    juce::Random random;
    


    Algorithm currentAlgorithm = Algorithm::softclip;


    // dc filter stuff
    float pi = juce::MathConstants<float>::pi;
    float prevInput[2] = { 0.0f, 0.0f }; // Previous input samples for left and right channels
    float prevOutput[2] = { 0.0f, 0.0f }; // Previous output samples for left and right channels
    float dcBlockerAlpha;
};



