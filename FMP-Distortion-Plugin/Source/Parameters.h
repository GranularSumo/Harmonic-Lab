/*
  ==============================================================================

    Parameters.h
    Created: 9 Oct 2023 3:11:51pm
    Author:  zeush

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Dsp.h"


namespace parameterInfo
{
    const juce::String inputGainName = "Input Gain";
    const juce::String inputGainId = "inputGain";

    const juce::String outputGainName = "Output Gain";
    const juce::String outputGainId = "outputGain";

    const juce::String sautrationName = "Saturation";
    const juce::String saturationId = "saturation";

    const juce::String oversamplingName = "Oversampling";
    const juce::String oversamplingId = "oversampling";

    const juce::String dryWetName = "Dry/Wet";
    const juce::String dryWetId = "dry/wet";

    const juce::String distortionTypeName = "Distortion Type";
    const juce::String distortionTypeId = "distortionType";

    const juce::StringArray distortionTypes = { "softclip", 
                                                "brokenSoftclip",
                                                "hardclip",
                                                "wavefold", 
                                                "foldback", 
                                                "asymetricSoftclip", 
                                                "biasShape", 
                                                "biasFold", 
                                                "foldCrush", 
                                                "dualPathBitFold", 
                                                "bitcrush", 
                                                "squarefold", 
                                                "downsample"};
                                              
    const juce::String driveName = "Drive";   
    const juce::String driveId = "drive";  

    const juce::String preFilterName = "Pre-Filter";
    const juce::String preFilterId = "preFilter";

    const juce::String preFilterTypeName = "Pre Filter Type";
    const juce::String preFilterTypeId = "preFilterType";

    const juce::StringArray preFilterTypes = { "lowpass", 
                                               "highpass", 
                                               "bandpass" };

    const juce::String preFilterCutoffName = "Pre Filter Cutoff";
    const juce::String preFilterCutoffId = "preFilterCutoff";

    const juce::String preFilterResName = "Pre Filter Res";
    const juce::String preFilterResId = "preFilterRes";

    const juce::String postFilterName = "Post-Filter";
    const juce::String postFilterId = "postFilter";

    const juce::String postFilterTypeName = "Post Filter Type";
    const juce::String postFilterTypeId = "postFilterType";

    const juce::StringArray postFilterTypes = { "lowpass",
                                                "highpass",
                                                "bandpass" };

    const juce::String postFilterCutoffName = "Post Filter Cutoff";
    const juce::String postFilterCutoffId = "postFilterCutoff";
                        
    const juce::String postFilterResName = "Post Filter Res";
    const juce::String postFilterResId = "postFilterRes";

    const juce::String themePickerName = "Theme Picker";
    const juce::String themePickerId = "themePicker";
    const juce::StringArray themePickerThemes = { "Default", "Vamp" };
    
    const juce::String uiModeName = "UI Mode";
    const juce::String uiModeId = "uiMode";

    Dsp::Algorithm indexToAlgorithm(int index);

}                                            
                                           
