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
#include "SvgPathManager.h"
#include "Theme.h"
#include "FocusOverlayComponent.h"

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

    juce::String getCurrentAlgorithm();
    void setCurrentPath(int index);

    juce::ComboBox& getAlgorithmSelector();

    void setTheme(const Theme& currentTheme);
    void setBackgroundColour(const juce::Colour& colour);
    void setShadowColour(const juce::Colour& colour);
    void setLineHighlightColour(const juce::Colour& colour);
    void setDriveSliderColours(const juce::Colour& fillColour, const juce::Colour& backgroundColour);
    void setFilterSliderColours(const juce::Colour& fillColour, const juce::Colour& backgroundColour);
    void setGainSliderColours(const juce::Colour& fillColour, const juce::Colour& backgroundColour);
    void setMixSliderColours(const juce::Colour& fillColour, const juce::Colour& backgroundColour);

    void setHighlightedArea(juce::String component);
    void clearHighlightedAreas();


    void showOverlay(bool shouldShow);


private:

    FMPDistortionPluginAudioProcessor& audioProcessor;

    float pluginHeight;
    float pluginWidth;

    FocusOverlayComponent focusOverlay;

    SvgPathManager sinePath;
    SvgPathManager pathSelector;

    juce::String currentAlgorithm;

    juce::Colour backgroundColour;
    juce::Colour shadowColour;
    juce::Colour lineHighlightColour;

    juce::ComboBox algorithmSelector;
    juce::Slider driveSlider;

    juce::Label preFilterLabel;
    juce::ToggleButton preFilterButton;
    juce::ComboBox preFilterSelector;
    juce::Slider preFilterFreqSlider;
    juce::Label preFilterFreqLabel;
    juce::Slider preFilterResSlider;
    juce::Label preFilterResLabel;

    juce::Label postFilterLabel;
    juce::ToggleButton postFilterButton;
    juce::ComboBox postFilterSelector;
    juce::Slider postFilterFreqSlider;
    juce::Label postFilterFreqLabel;
    juce::Slider postFilterResSlider;
    juce::Label postFilterResLabel;

    juce::Slider inputGainSlider;
    juce::Label inputGainLabel;
    juce::Slider outputGainSlider;
    juce::Label outputGainLabel;
    juce::Slider dryWetMixSlider;
    juce::Label dryWetMixLabel;

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
