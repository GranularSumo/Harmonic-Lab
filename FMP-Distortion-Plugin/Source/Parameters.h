/*
  ==============================================================================

    Parameters.h
    Created: 9 Oct 2023 3:11:51pm
    Author:  zeush

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


namespace parameterInfo
{
    const juce::String inputGainName = "Input Gain";
    const juce::String inputGainId = "inputGain";

    const juce::String sautrationName = "Saturation";
    const juce::String saturationId = "saturation";

    const juce::String oversamplingName = "Oversampling";
    const juce::String oversamplingId = "oversampling";

    const juce::String dryWetName = "Dry/Wet";
    const juce::String dryWetId = "dry/wet";

    const juce::String distortionTypeName = "Distortion Type";
    const juce::String distortionTypeId = "distortionType";
    const juce::StringArray distortionTypes = { "softclip", "hardclip", "bitcrush", "wavefold", "wfxs", "feedbackWavefold", "chaos"};

    const juce::String driveName = "Drive";
    const juce::String driveId = "drive";

}

