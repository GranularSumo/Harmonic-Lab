/*
  ==============================================================================

    Dsp.cpp
    Created: 5 Dec 2023 3:40:01pm
    Author:  zeush

  ==============================================================================
*/

#include "Dsp.h"


void Dsp::setProcessState()
{
    procesState = !procesState;
}

float Dsp::arctanSoftClipper(float currentSample, float amount)
{
    return piDivisor * std::atan(currentSample * amount);
}

float Dsp::hardClipper(float currentSample, float amount)
{
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

float Dsp::bitcrusher(float currentSample, float bitDepth)
{
    return 0.0f;
}

float Dsp::wavefolder(float currentSample, float amount)
{
    return 0.0f;
}

void Dsp::process(juce::dsp::AudioBlock<float>& block)
{
    for (int channel = 0; channel < block.getNumChannels(); ++channel)
    {
        auto* channelData = block.getChannelPointer(channel);

        for (int sample = 0; sample < block.getNumSamples(); ++sample)
        {
            algorithmSelector(channelData[sample]);
        }
    }
}

void Dsp::algorithmSelector(float& sample)
{
    switch (currentAlgorithm) {
        case softclip:
             sample = arctanSoftClipper(sample, 8.0f);
             break;
        case hardclip:
            sample = hardClipper(sample, 10.0f);
            break;
    }
}




