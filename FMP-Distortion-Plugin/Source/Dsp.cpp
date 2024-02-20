/*
  ==============================================================================

    Dsp.cpp
    Created: 5 Dec 2023 3:40:01pm
    Author:  zeush

  ==============================================================================
*/

#include "Dsp.h"
#include <math.h>


Dsp::Dsp()
{
}

void Dsp::setDistortionType(Algorithm algorithm)
{
    currentAlgorithm = algorithm;
}

void Dsp::setDriveAmount(float amount)
{
    alpha = amount;
}

void Dsp::setSampleRate(float sampleRate)
{
    originalSampleRate = sampleRate;
}


void Dsp::updateDcBlockerCoefficient(float sampleRate)
{
    const float cutoffFrequency = 15.0f; // DC blocker cutoff frequency in Hz
    dcBlockerAlpha = 1.0f / (1.0f + (2.0f * pi * cutoffFrequency / sampleRate));
}

float Dsp::processDcBlocker(float sample, int channel)
{
    // Ensure channel index is either 0 (left) or 1 (right)
    if (channel < 0 || channel > 1) return sample;

    // Apply DC Blocker formula
    float output = sample - prevInput[channel] + dcBlockerAlpha * prevOutput[channel];
    prevInput[channel] = sample;
    prevOutput[channel] = output;
    return output;
}




float Dsp::softClipper(float currentSample)
{
    return piDivisor * std::atan(currentSample * alpha);
}

float Dsp::brokenSoftclipper(float currentSample)
{
    // map the alpha value to a range of 0.0 to 0.5
    float modulationDepth = (alpha - 1.0f) / (24.0f - 1.0f) * 0.5f;

    float noiseSample = random.getSystemRandom().nextFloat() * 2.0f - 1.0f;

    return softClipper(currentSample += currentSample * noiseSample * modulationDepth) * 0.5f + (currentSample += currentSample * noiseSample * modulationDepth) * 0.5f;
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
    float parameterRangeRemap = 8.0f - (alpha - 1.0f) * (7.0f / 23.0f);
    float ampValues = pow(2, parameterRangeRemap) - 1;
    return round(ampValues * currentSample) * (1 / ampValues);

}

float Dsp::squareFolder(float currentSample, int channel)
{
    return wavefolder(bitCrusher(currentSample));
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

float Dsp::saturatedWavefolder(float currentSample)
{
    float wf = wavefolder(currentSample) * 0.5f;
    float sc = softClipper(currentSample) * 0.5;
    return wf + sc;
}

float Dsp::feedbackWavefolder(float currentSample, int channel)
{
    float summedSample;
    float feedback;
    float output;
    if (channel == 0)
    {
        summedSample = saturatedWavefolder(currentSample);
        feedback = softClipper(sampleDelay1);
        output = (summedSample + feedback) * 0.5;
        sampleDelay1 = output;
    }
    else
    {
        summedSample = saturatedWavefolder(currentSample);
        feedback = softClipper(sampleDelay2);
        output = (summedSample + feedback) * 0.5;
        sampleDelay2 = output;
    }
    
    return output;
}

float Dsp::asymetricSoftClipper(float currentSample)
{
    float dcOffset = 0.5f;
    return softClipper(currentSample + dcOffset) - dcOffset;
}

float Dsp::BiasShaper(float currentSample)
{
    if (currentSample > 1)
    {
        return softClipper(currentSample);
    }
    else
    {
        return softClipper(currentSample + 0.75) - 0.75;
    }
}

float Dsp::BiasFolder(float currentSample, int channel)
{
    return feedbackWavefolder(currentSample + 0.75f, channel) - 0.75;
}

float Dsp::foldCrusher(float currentSample, int channel)
{
    if (currentSample > 0)
    {
        return feedbackWavefolder(currentSample, channel);
    }
    else
    {
        return bitCrusher(currentSample);
    }
}

float Dsp::dualPathBitFolder(float currentSample, int channel)
{
    if (currentSample > 0)
    {
        return squareFolder(currentSample, channel);
    }
    else
    {
        return feedbackWavefolder(downSampler(currentSample, channel), channel);
    }
}

float Dsp::downSampler(float currentSample, int channel)
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
            currentSample = softClipper(currentSample);
            sampleDelay1 = bitCrusher(currentSample); // Hold this sample until the counter resets again
        }
        return sampleDelay1; // Output held sample
    }
    else { // Assuming channel == 1 for stereo
        counter2++;
        if (counter2 >= decimateFactor) {
            counter2 = 0; // Reset counter
            currentSample = softClipper(currentSample);
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
            if (dcFilterOn)
            {
                channelData[sample] = processDcBlocker(channelData[sample], channel);
            }
        }

    }
}

void Dsp::algorithmSelector(float& sample, int channel)
{
    switch (currentAlgorithm) {

        // symetric algorithms

        case softclip:
            dcFilterOn = false;
             sample = softClipper(sample);
             break;
        
        case brokenSoftclip:
            dcFilterOn = false;
            sample = brokenSoftclipper(sample);
            break;

        case hardclip:
            dcFilterOn = false;
            sample = hardClipper(sample);
            break;

        case wavefold:
            dcFilterOn = false;
            sample = wavefolder(sample);
            break;

        case foldback:
            dcFilterOn = false;
            sample = feedbackWavefolder(sample, channel);
            break;


        // asymetric algorithms

        case asymetricSoftclip:
            dcFilterOn = true;
            sample = asymetricSoftClipper(sample);
            break;

        case biasShape:
            dcFilterOn = true;
            sample = BiasShaper(sample);
            break;

        case biasFold:
            dcFilterOn = true;
            sample = BiasFolder(sample, channel);
            break;

        case foldCrush:
            dcFilterOn = true;
            sample = foldCrusher(sample, channel);
            break;

        case dualPathBitFold:
            dcFilterOn = true;
            sample = dualPathBitFolder(sample, channel);
            break;


        // quantization algorithms

        case bitcrush:
            dcFilterOn = false;
            sample = bitCrusher(sample);
            break;

        case squarefold:
            dcFilterOn = false;
            sample = squareFolder(sample, channel);
            break;

        case downsample:
            dcFilterOn = false;
            sample = downSampler(sample, channel);
            break;

    }
}

juce::LinearSmoothedValue<float>& Dsp::getSmoothedDrive()
{
    return smoothedDrive;
}





