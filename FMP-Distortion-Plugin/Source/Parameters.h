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
    const juce::StringArray distortionTypes = { "softclip", "hardclip", "bitcrush", "squareFold", "wavefold", "wfxs", "feedbackWavefold", "downsample"};
                                              
    const juce::String driveName = "Drive";   
    const juce::String driveId = "drive";  

    const juce::String preFilterName = "Pre-Filter";
    const juce::String preFilterId = "preFilter";

    const juce::String preFilterTypeName = "Pre Filter Type";
    const juce::String preFilterTypeId = "preFilterType";
    const juce::StringArray preFilterTypes = { "lowpass", "highpass", "bandpass" };

    const juce::String postFilterName = "Post-Filter";
    const juce::String postFilterId = "postFilter";

    const juce::String postFilterTypeName = "Post Filter Type";
    const juce::String postFilterTypeId = "postFilterType";
    const juce::StringArray postFilterTypes = { "lowpass", "highpass", "bandpass" };
    
                                             
}                                            
                                           
