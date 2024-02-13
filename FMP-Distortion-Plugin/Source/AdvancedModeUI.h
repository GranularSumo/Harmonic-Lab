/*
  ==============================================================================

    AdvancedModeUI.h
    Created: 8 Feb 2024 12:10:50pm
    Author:  zeush

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "TextLoader.h"
#include "Logo.h" 

//==============================================================================
/*
*/
class AdvancedModeUI  : public juce::Component
{
public:
    AdvancedModeUI(FMPDistortionPluginAudioProcessor& processor, float height, float width);
    ~AdvancedModeUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setBackgroundColour(juce::Colour& colour);
    void setShadowColour(juce::Colour& colour);
    void setLineHighlightColour(juce::Colour& colour);
    void setDriveSliderColours(juce::Colour& fillColour, juce::Colour& backgroundColour);
    void setFilterSliderColours(juce::Colour& fillColour, juce::Colour& backgroundColour);
    void setGainSliderColours(juce::Colour& fillColour, juce::Colour& backgroundColour);
    void setMixSliderColours(juce::Colour& fillColour, juce::Colour& backgroundColour);
private:

    FMPDistortionPluginAudioProcessor& audioProcessor;



    float pluginHeight;
    float pluginWidth;

    juce::Colour backgroundColour;
    juce::Colour shadowColour;
    juce::Colour lineHighlightColour;

    juce::ComboBox algorithmSelector;
    juce::Slider driveSlider;

    juce::Label preFilterLabel;
    juce::ToggleButton preFilterButton;
    juce::ComboBox preFilterSelector;
    juce::Slider preFilterFreqSlider;
    juce::Slider preFilterResSlider;

    juce::Label postFilterLabel;
    juce::ToggleButton postFilterButton;
    juce::ComboBox postFilterSelector;
    juce::Slider postFilterFreqSlider;
    juce::Slider postFilterResSlider;

    juce::Slider inputGainSlider;
    juce::Slider outputGainSlider;
    juce::Slider dryWetMixSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> distortionAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> selectorAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> preFilterCheckBoxAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> preFilterSelectorAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> preFilterCutoffAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> preFilterResAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> postFilterCheckBoxAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> postFilterSelectorAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> postFilterCutoffAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> postFilterResAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dryWetAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdvancedModeUI)
};
