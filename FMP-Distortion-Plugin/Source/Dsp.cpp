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
        currentAlgorithm = Algorithm::feedbackWavefold;
    }
    else if (newValue == "chaos")
    {
        currentAlgorithm = Algorithm::chaos;
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

float Dsp::bitcrusher(float currentSample)
{
    // this remaps the parameter that controlls alpha so that it has a range of 1 to 8.
    float parameterRangeRemap = (alpha - 1.0f) * (8.0f - 1.0f) / (24.0f - 1.0f) + 1.0f;
    float ampValues = pow(2, parameterRangeRemap) - 1;
    return round(ampValues * currentSample) * (1 / ampValues);

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

float Dsp::Chaos(float currentSample, int channel)
{
    float minTargetSampleRate = 200.0f;
    float maxTargetSampleRate = 1000.0f;

    float targetSampleRate = minTargetSampleRate + (alpha - 1.0f) / (24.0f - 1.0f) * (maxTargetSampleRate - minTargetSampleRate);

    float decimateFactor = originalSampleRate / targetSampleRate;

    //float parameterRangeRemap = (alpha - 1.0f) * (100000.0f - 200.0f) / (24.0f - 1.0f) + 200.0f;
    if (channel == 0)
    {

        if (++counter1 >= decimateFactor)
        {
            counter1 = 0;
            sampleDelay1 = bitcrusher(currentSample);
        }
        return sampleDelay1;
    }
    else
    {
        if (++counter2 >= decimateFactor)
        {
            counter2 = 0;
            sampleDelay2 = bitcrusher(currentSample);
        }
        return sampleDelay2;
    }
}


void Dsp::process(juce::dsp::AudioBlock<float>& block)
{
    for (int channel = 0; channel < block.getNumChannels(); ++channel)
    {
        auto* channelData = block.getChannelPointer(channel);

        for (int sample = 0; sample < block.getNumSamples(); ++sample)
        {
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
            sample = bitcrusher(sample);
            //DBG("bit");
            break;
        case wavefold:
            sample = wavefolder(sample);
            //DBG("fold");
            break;
        case wfxs:
            sample = wavefolderXs(sample);
            //DBG("wfsx");
            break;
        case feedbackWavefold:
            sample = feedbackWavefolder(sample, channel);
            break;
        case chaos:
            sample = Chaos(sample, channel);
            break;
    }
}




