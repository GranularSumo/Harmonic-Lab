/*
  ==============================================================================

    Dsp.cpp
    Created: 5 Dec 2023 3:40:01pm
    Author:  zeush

  ==============================================================================
*/

#include "Dsp.h"
#include <math.h>

void Dsp::setDistortionType(juce::String newValue)
{
    if (newValue == "softclip")
    {
        currentAlgorithm = Algorithm::softclip;
    }
    else if (newValue == "hardclip")
    {
        currentAlgorithm = Algorithm::hardclip;
    }
    else if (newValue == "bitcrush")
    {
        currentAlgorithm = Algorithm::bitcrush;
    }
    else if (newValue == "squareFold")
    {
        currentAlgorithm = Algorithm::squareFold;
    }
    else if (newValue == "wavefold")
    {
        currentAlgorithm = Algorithm::wavefold;
    }
    else if (newValue == "wfxs")
    {
        currentAlgorithm = Algorithm::wfxs;
    }
    else if (newValue == "feedbackWavefold")
    {
        currentAlgorithm = Algorithm::feedbackwavefold;
    }
    else if (newValue == "downsample")
    {
        currentAlgorithm = Algorithm::downsample;
    }
}

void Dsp::setDriveAmount(float amount)
{
    alpha = amount;
}

void Dsp::setSampleRate(float sampleRate)
{
    originalSampleRate = sampleRate;
}


float Dsp::arctanSoftClipper(float currentSample)
{
    return piDivisor * std::atan(currentSample * alpha);
}

float Dsp::hardClipper(float currentSample)
{

    float drive = pow(10.0, alpha / 20.0f);
    currentSample = currentSample * drive;

    if (currentSample > 1.0f)
    {
        return 1.0f;
    }
    else if (currentSample < -1.0f)
    {
        return -1.0f;
    }
    else
    {
        return currentSample;
    }
}

float Dsp::bitCrusher(float currentSample)
{
    // this remaps the parameter that controlls alpha so that it has a range of 1 to 8.
    //float parameterRangeRemap = (alpha - 1.0f) * (8.0f - 1.0f) / (24.0f - 1.0f) + 1.0f; -- this would make it so that the effect happens as you lower the slider
    float parameterRangeRemap = 8.0f - (alpha - 1.0f) * (7.0f / 23.0f);
    float ampValues = pow(2, parameterRangeRemap) - 1;
    return round(ampValues * currentSample) * (1 / ampValues);

}

float Dsp::squareFolder(float currentSample, int channel)
{
    float feedback = 0;
    float output = 0;

    float feedbackMix = 0.2f;

    if (channel == 0)
    {
        feedback = bitCrusher(sampleDelay1);
        output = bitCrusher(currentSample) * (1.0f - feedbackMix) + feedback * feedbackMix;
        sampleDelay1 = output;
    }
    else
    {
        feedback = bitCrusher(sampleDelay2);
        output = bitCrusher(currentSample) * (1.0f - feedbackMix) + feedback * feedbackMix;
        sampleDelay2 = output;
    }
    return output;
    //return processFeedback(bitcrusher(currentSample), channel);
}

float Dsp::wavefolder(float currentSample)
{
    float drive = pow(10.0, alpha / 20.0f);
    currentSample = currentSample * drive;

    while (abs(currentSample) > 1.0f)
    {
        if (currentSample > 1.0f)
        {
            currentSample = 2.0f - currentSample;
        }
        else if (currentSample < -1.0f)
        {
            currentSample = -2.0 - currentSample;
        }
    }  
    return currentSample;
}

float Dsp::wavefolderXs(float currentSample)
{
    float wf = wavefolder(currentSample) * 0.5f;
    float sc = arctanSoftClipper(currentSample) * 0.5;
    return wf + sc;
}

float Dsp::feedbackWavefolder(float currentSample, int channel)
{
    float summedSample;
    float feedback;
    float output;
    if (channel == 0)
    {
        summedSample = wavefolderXs(currentSample);
        feedback = arctanSoftClipper(sampleDelay1);
        output = (summedSample + feedback) * 0.5;
        sampleDelay1 = output;
    }
    else
    {
        summedSample = wavefolderXs(currentSample);
        feedback = arctanSoftClipper(sampleDelay2);
        output = (summedSample + feedback) * 0.5;
        sampleDelay2 = output;
    }
    
    return output;
}

float Dsp::downSample(float currentSample, int channel)
{
    float minTargetSampleRate = 0.0f;
    float maxTargetSampleRate = 5000.0f;

    //normalize alpha to 0.0 - 1.0 range
    float normalizedAlpha = (alpha - 1.0f) / (24.0f - 1.0f);

    // Calculate the decimation factor based on alpha, controlling the downsampling effect.
    float targetSampleRate = maxTargetSampleRate - normalizedAlpha * (maxTargetSampleRate - minTargetSampleRate);
    float decimateFactor = originalSampleRate / targetSampleRate;

    // Use separate counters for each channel to maintain stereo processing integrity.
    if (channel == 0) {
        counter1++;
        if (counter1 >= decimateFactor) {
            counter1 = 0; // Reset counter
            currentSample = arctanSoftClipper(currentSample);
            sampleDelay1 = bitCrusher(currentSample); // Hold this sample until the counter resets again
        }
        return sampleDelay1; // Output held sample
    }
    else { // Assuming channel == 1 for stereo
        counter2++;
        if (counter2 >= decimateFactor) {
            counter2 = 0; // Reset counter
            currentSample = arctanSoftClipper(currentSample);
            sampleDelay2 = bitCrusher(currentSample); // Hold this sample until the counter resets again
        }
        return sampleDelay2; // Output held sample
    }
}

void Dsp::resetDelaySamples()
{
    sampleDelay1 = 0.0f;
    sampleDelay2 = 0.0f;
}

void Dsp::resetCounters()
{
    counter1 = 0;
    counter2 = 0;
}

void Dsp::process(juce::dsp::AudioBlock<float>& block)
{
    for (int channel = 0; channel < block.getNumChannels(); ++channel)
    {
        auto* channelData = block.getChannelPointer(channel);

        for (int sample = 0; sample < block.getNumSamples(); ++sample)
        {
            setDriveAmount(smoothedDrive.getNextValue());
            algorithmSelector(channelData[sample], channel); 
        }
    }
}

void Dsp::algorithmSelector(float& sample, int channel)
{
    switch (currentAlgorithm) {
        case softclip:
             sample = arctanSoftClipper(sample);
             //DBG("soft");
             break;
        case hardclip:
            sample = hardClipper(sample);
            //DBG("hard");
            break;
        case bitcrush:
            sample = bitCrusher(sample);
            //DBG("bit");
            break;
        case squareFold:
            sample = squareFolder(sample, channel);
            //DBG("working");
        case wavefold:
            sample = wavefolder(sample);
            //DBG("fold");
            break;
        case wfxs:
            sample = wavefolderXs(sample);
            //DBG("wfsx");
            break;
        case feedbackwavefold:
            sample = feedbackWavefolder(sample, channel);
            break;
        case downsample:
            sample = downSample(sample, channel);
            break;
    }
}

juce::LinearSmoothedValue<float>& Dsp::getSmoothedDrive()
{
    return smoothedDrive;
}





