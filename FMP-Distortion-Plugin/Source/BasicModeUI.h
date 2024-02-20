/*
  ==============================================================================

    BasicMode.h
    Created: 8 Feb 2024 12:44:20am
    Author:  zeush

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "TextLoader.h"
#include "SvgPathManager.h"

//==============================================================================
/*
*/
class BasicModeUI  : public juce::Component
{
public:
    BasicModeUI(FMPDistortionPluginAudioProcessor& processor, float height, float width);
    ~BasicModeUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setBackgroundColour(juce::Colour& colour);
    void setShadowColour(juce::Colour& colour);
    void setLineHighlightColour(juce::Colour& colour);
    void setDriveSliderColours(juce::Colour& fillColour, juce::Colour& backgroundColour);

private:

    FMPDistortionPluginAudioProcessor& audioProcessor;

    const float pluginWidth;
    const float pluginHeight;

    juce::Slider driveSlider;
    juce::ComboBox algorithmSelector;
    juce::Label infoBoxTitle;
    juce::TextEditor infoBox;

    SvgPathManager sinePath;
    SvgPathManager pathSelector;

    juce::Colour backgroundColour;
    juce::Colour shadowColour;
    juce::Colour lineHighlightColour;

    TextLoader textLoader;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> distortionAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> selectorAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicModeUI)
};
