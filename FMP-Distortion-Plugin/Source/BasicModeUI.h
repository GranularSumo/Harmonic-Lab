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
#include "Theme.h"
#include "AttrStringComponent.h"

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

    void setTheme(const Theme& currentTheme);
    void setBackgroundColour(const juce::Colour& colour);
    void setShadowColour(const juce::Colour& colour);
    void setLineHighlightColour(const juce::Colour& colour);
    void setDriveSliderColours(const juce::Colour& fillColour, const juce::Colour& backgroundColour);
    void setInfoBoxColours(const juce::Colour& backgroundColour, const juce::Colour& highlightColour);

    void updateAlgorithmDescription();


private:

    FMPDistortionPluginAudioProcessor& audioProcessor;

    const float pluginWidth;
    const float pluginHeight;

    juce::Slider driveSlider;
    juce::ComboBox algorithmSelector;
    juce::Label infoBoxTitle;
    juce::TextEditor infoBox;

    AttrStringComponent attrStringComp;
    juce::Viewport viewport;
    juce::Colour textColour;

    SvgPathManager sinePath;
    SvgPathManager pathSelector;

    juce::Colour backgroundColour;
    juce::Colour shadowColour;
    juce::Colour lineHighlightColour;

    TextLoader textLoader;

    juce::String selectedPath;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> distortionAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> selectorAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicModeUI)
};
