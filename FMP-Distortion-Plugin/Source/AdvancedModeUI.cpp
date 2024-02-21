/*
  ==============================================================================

    AdvancedModeUI.cpp
    Created: 8 Feb 2024 12:10:50pm
    Author:  zeush

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdvancedModeUI.h"

//==============================================================================
AdvancedModeUI::AdvancedModeUI(FMPDistortionPluginAudioProcessor& processor, float height, float width) : audioProcessor(processor), pluginHeight(height), pluginWidth(width)
{
    // Algorithm selector setup

    addAndMakeVisible(algorithmSelector);
    algorithmSelector.setJustificationType(juce::Justification::centred);
    algorithmSelector.addSectionHeading("Odd Harmonics");
    algorithmSelector.addItem("Softclipper", 1);
    algorithmSelector.addItem("Broken Softclipper", 2);
    algorithmSelector.addItem("Hardclipper", 3);
    algorithmSelector.addItem("Wavefolder", 4);
    algorithmSelector.addItem("Foldback", 5);

    algorithmSelector.addSeparator();
    algorithmSelector.addSectionHeading("Even Harmonics");
    algorithmSelector.addItem("Asymetric Softclipper", 6);
    algorithmSelector.addItem("Bias Shaper", 7);
    algorithmSelector.addItem("Bias Folder", 8);
    algorithmSelector.addItem("Fold Crusher", 9);
    algorithmSelector.addItem("Dual Path BitFolder", 10);

    algorithmSelector.addSeparator();
    algorithmSelector.addSectionHeading("Quantization");
    algorithmSelector.addItem("Bitcrusher", 11);
    algorithmSelector.addItem("Square Folder", 12);
    algorithmSelector.addItem("Downsample", 13);

    algorithmSelector.onChange = [this]()
        {
            pathSelector.setCurrentPath(pathSelector.getPath(algorithmSelector.getSelectedId()));
        };

    selectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, parameterInfo::distortionTypeId, algorithmSelector);

    // Drive slider setup

    addAndMakeVisible(driveSlider);
    driveSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

    distortionAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treestate, parameterInfo::driveId, driveSlider);

    // Pre Filter Setup

    addAndMakeVisible(preFilterLabel);
    preFilterLabel.setText("Pre-Filter", juce::dontSendNotification);
    preFilterLabel.setJustificationType(juce::Justification::centredTop);

    addAndMakeVisible(preFilterButton);
    preFilterCheckBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treestate, parameterInfo::preFilterId, preFilterButton);

    addAndMakeVisible(preFilterSelector);
    preFilterSelector.setJustificationType(juce::Justification::centred);
    preFilterSelector.addItem("Lowpass", 1);
    preFilterSelector.addItem("Highpass", 2);
    preFilterSelector.addItem("Bandpass", 3);
    preFilterSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, parameterInfo::preFilterTypeId, preFilterSelector);

    addAndMakeVisible(preFilterFreqSlider);
    preFilterFreqSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    preFilterFreqSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    preFilterCutoffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treestate, parameterInfo::preFilterCutoffId, preFilterFreqSlider);


    addAndMakeVisible(preFilterResSlider);
    preFilterResSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    preFilterResSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    preFilterResAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treestate, parameterInfo::preFilterResId, preFilterResSlider);
    
    // Post filter setup

    addAndMakeVisible(postFilterLabel);
    postFilterLabel.setText("Post-Filter", juce::dontSendNotification);
    postFilterLabel.setJustificationType(juce::Justification::centredTop);

    addAndMakeVisible(postFilterButton);
    postFilterCheckBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treestate, parameterInfo::postFilterId, postFilterButton);

    addAndMakeVisible(postFilterSelector);
    postFilterSelector.setJustificationType(juce::Justification::centred);
    postFilterSelector.addItem("Lowpass", 1);
    postFilterSelector.addItem("Highpass", 2);
    postFilterSelector.addItem("Bandpass", 3);
    postFilterSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, parameterInfo::postFilterTypeId, postFilterSelector);

    addAndMakeVisible(postFilterFreqSlider);
    postFilterFreqSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    postFilterFreqSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    postFilterCutoffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treestate, parameterInfo::postFilterCutoffId, postFilterFreqSlider);

    addAndMakeVisible(postFilterResSlider);
    postFilterResSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    postFilterResSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    postFilterResAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treestate, parameterInfo::postFilterResId, postFilterResSlider);

    // Input slider setup

    addAndMakeVisible(inputGainSlider);
    inputGainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    inputGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    inputGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treestate, parameterInfo::inputGainId, inputGainSlider);

    // Output slider setup

    addAndMakeVisible(outputGainSlider);
    outputGainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    outputGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    outputGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treestate, parameterInfo::outputGainId, outputGainSlider);

    // Mix slider setup

    addAndMakeVisible(dryWetMixSlider);
    dryWetMixSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    dryWetMixSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    dryWetAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treestate, parameterInfo::dryWetId, dryWetMixSlider);

    addAndMakeVisible(sinePath);
    sinePath.setCurrentPath(SvgPathManager::sine);

    addAndMakeVisible(pathSelector);
    pathSelector.setCurrentPath(SvgPathManager::softclip);
}

AdvancedModeUI::~AdvancedModeUI()
{
}

void AdvancedModeUI::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    auto headerBounds = bounds.removeFromTop(pluginHeight * 0.1f);
    auto footerBounds = bounds.removeFromBottom(pluginHeight * 0.05f);
    auto mainAreaHeight = bounds.getHeight();
    auto row1Bounds = bounds.removeFromTop(mainAreaHeight * 0.2f);
    auto row2Bounds = bounds.removeFromTop(mainAreaHeight * 0.25f);
    auto row3Bounds = bounds.removeFromTop(mainAreaHeight * 0.375f);
    

    g.fillAll(backgroundColour);

    // colours the background of the header section
    g.setColour(shadowColour);
    g.fillRect(headerBounds);

    // colours the background of the footer section
    g.fillRect(footerBounds);

    // draws a line to highlight the bottom of the header section
    g.setColour(lineHighlightColour);
    g.drawLine(
        headerBounds.getX(), 
        headerBounds.getBottom(), 
        headerBounds.getRight(), 
        headerBounds.getBottom());

    // draws a line to shade the top of the footer section
    g.setColour(shadowColour.darker(0.3f));
    g.drawLine(
        footerBounds.getX(), 
        footerBounds.getY(), 
        footerBounds.getRight(), 
        footerBounds.getY());

    // draws a separator line between row 2 and row 3
    g.setColour(lineHighlightColour);
    g.drawLine(
        row2Bounds.getX() + (row2Bounds.getWidth() * 0.1f), 
        row2Bounds.getBottom(), 
        row2Bounds.getRight() - (row2Bounds.getWidth() * 0.1f), 
        row2Bounds.getBottom());

    // draws a separator line in the middle of row 3
    g.drawLine(
        row3Bounds.getCentreX(),
        row3Bounds.getY() + row3Bounds.getHeight() * 0.25,
        row3Bounds.getCentreX(),
        row3Bounds.getBottom() - row3Bounds.getHeight() * 0.25);

    // draws a separator line between row 3 and row 4
    g.drawLine(
        row3Bounds.getX() + (row3Bounds.getWidth() * 0.1f),
        row3Bounds.getBottom(),
        row3Bounds.getRight() - (row3Bounds.getWidth() * 0.1f),
        row3Bounds.getBottom());


    // draws a shadow for the separator line between row 2 and row 3
    g.setColour(shadowColour);
    g.drawLine(
        row2Bounds.getX() + (row2Bounds.getWidth() * 0.1f),
        row2Bounds.getBottom() - 1,
        row2Bounds.getRight() - (row2Bounds.getWidth() * 0.1f),
        row2Bounds.getBottom() - 1);

    // draws a shadow for the separator line between row 3 and row 4
    g.drawLine(
        row3Bounds.getX() + (row3Bounds.getWidth() * 0.1f),
        row3Bounds.getBottom() - 1,
        row3Bounds.getRight() - (row3Bounds.getWidth() * 0.1f),
        row3Bounds.getBottom() - 1);
    
    // draws a shadow in the middle of row 3
    g.drawLine(
        row3Bounds.getCentreX() - 1,
        row3Bounds.getY() + row3Bounds.getHeight() * 0.25,
        row3Bounds.getCentreX() - 1,
        row3Bounds.getBottom() - row3Bounds.getHeight() * 0.25);

    // draws an arrow between sinePath and drive slider
    g.setColour(lineHighlightColour);
    auto leftArrowStart = juce::Point<float>(sinePath.getRight() + 10.0f, sinePath.getBounds().getCentreY());
    auto leftArrowEnd = juce::Point<float>(sinePath.getRight() + 50.0f, sinePath.getBounds().getCentreY());
    auto leftArrow = juce::Line<float>(leftArrowStart, leftArrowEnd);
    g.drawArrow(leftArrow, 3.0f, 10.0f, 10.0f);

    // draws an arrow between drive slider and path selector
    g.setColour(lineHighlightColour);
    auto rightArrowStart = juce::Point<float>(pathSelector.getX() - 50.0f, sinePath.getBounds().getCentreY());
    auto rightArrowEnd = juce::Point<float>(pathSelector.getX() - 10.0f, sinePath.getBounds().getCentreY());
    auto rightArrow = juce::Line<float>(rightArrowStart, rightArrowEnd);
    g.drawArrow(rightArrow, 3.0f, 10.0f, 10.0f);

}

void AdvancedModeUI::resized()
{
    auto bounds = getLocalBounds();
    auto headerBounds = bounds.removeFromTop(pluginHeight * 0.1f);
    auto footerBounds = bounds.removeFromBottom(pluginHeight * 0.05f);
    auto mainAreaHeight = bounds.getHeight();
    auto row1Bounds = bounds.removeFromTop(mainAreaHeight * 0.2f);
    auto row2Bounds = bounds.removeFromTop(mainAreaHeight * 0.25f);
    auto row3Bounds = bounds.removeFromTop(mainAreaHeight * 0.375f);
    auto row3LeftBounds = row3Bounds.removeFromLeft(row3Bounds.getWidth() * 0.5);
    
    // setting the bounds for components in row 1
    algorithmSelector.setBounds(
        row1Bounds.getX() + (row1Bounds.getWidth() * 0.375f), 
        row1Bounds.getY() + (row1Bounds.getHeight() * 0.4f), 
        row1Bounds.getWidth() * 0.25f,
        row1Bounds.getHeight() * 0.25f);

    // setting the bounds for the components in row 2
    driveSlider.setBounds(
        row2Bounds.getX() + (row2Bounds.getWidth() * 0.375f), 
        row2Bounds.getY() - (row1Bounds.getHeight() * 0.25), 
        row2Bounds.getWidth() *  0.25, 
        row2Bounds.getHeight());

    //setting the bounds for the left components in row 3
    preFilterLabel.setBounds(
        row3LeftBounds.getX() + row3Bounds.getWidth() * 0.375,
        row3LeftBounds.getY() + row3Bounds.getHeight() * 0.1f,
        row3LeftBounds.getWidth() * 0.5,
        row3LeftBounds.getHeight() * 0.1f);

    preFilterButton.setBounds(
        row3LeftBounds.getRight() - row3LeftBounds.getWidth() * 0.3,
        row3LeftBounds.getY() + row3Bounds.getHeight() * 0.1f,
        row3LeftBounds.getWidth() * 0.1,
        row3LeftBounds.getHeight() * 0.1f);

    preFilterSelector.setBounds(
        row3LeftBounds.getX() + row3Bounds.getWidth() * 0.375,
        row3LeftBounds.getY() + row3Bounds.getHeight() * 0.25f,
        row3LeftBounds.getWidth() * 0.5,
        row3LeftBounds.getHeight() * 0.15f);

    preFilterFreqSlider.setBounds(
        row3LeftBounds.getX() + row3Bounds.getWidth() * 0.375,
        row3LeftBounds.getY() + row3Bounds.getHeight() * 0.45f,
        row3LeftBounds.getWidth() * 0.25,
        row3LeftBounds.getHeight() * 0.4f);

    preFilterResSlider.setBounds(
        row3LeftBounds.getX() + (row3Bounds.getWidth() * 0.375) + row3LeftBounds.getWidth() * 0.25f,
        row3LeftBounds.getY() + row3Bounds.getHeight() * 0.45f,
        row3LeftBounds.getWidth() * 0.25f,
        row3LeftBounds.getHeight() * 0.4f);

    //setting the bounds for the right components in row 3
    auto postFilterLabelHeight = row3Bounds.getHeight() * 0.1f;
    postFilterLabel.setBounds(
        row3Bounds.getX() + row3Bounds.getWidth() * 0.125f,
        row3Bounds.getY() + postFilterLabelHeight,
        row3Bounds.getWidth() * 0.5f,
        postFilterLabelHeight);

    postFilterButton.setBounds(
        row3Bounds.getRight() - row3Bounds.getWidth() * 0.55,
        row3Bounds.getY() + row3Bounds.getHeight() * 0.1f,
        row3Bounds.getWidth() * 0.1,
        row3Bounds.getHeight() * 0.1f);

    postFilterSelector.setBounds(
        row3Bounds.getX() + row3Bounds.getWidth() * 0.125,
        row3Bounds.getY() + row3Bounds.getHeight() * 0.25f,
        row3Bounds.getWidth() * 0.5,
        row3Bounds.getHeight() * 0.15f);

    postFilterFreqSlider.setBounds(
        row3Bounds.getX() + row3Bounds.getWidth() * 0.125,
        row3Bounds.getY() + row3Bounds.getHeight() * 0.45f,
        row3Bounds.getWidth() * 0.25,
        row3Bounds.getHeight() * 0.4f);

    postFilterResSlider.setBounds(
        row3Bounds.getX() + (row3Bounds.getWidth() * 0.125) + row3Bounds.getWidth() * 0.25f,
        row3Bounds.getY() + row3Bounds.getHeight() * 0.45f,
        row3Bounds.getWidth() * 0.25f,
        row3Bounds.getHeight() * 0.4f);

    //setting the bounds for the sliders in row 4
    auto inputSliderWidth = bounds.getWidth() * 0.075f;
    auto inputSliderX = bounds.getX() + ((bounds.getWidth() - inputSliderWidth) / 2.0f) - (inputSliderWidth * 1.25f);
    inputGainSlider.setBounds(
        inputSliderX, 
        bounds.getY() + (bounds.getHeight() * 0.1f),
        inputSliderWidth, 
        bounds.getWidth() * 0.1f);

    auto outputSliderWidth = bounds.getWidth() * 0.075f;
    auto outputSliderX = bounds.getX() + ((bounds.getWidth() - outputSliderWidth) / 2.0f) + (outputSliderWidth * 1.25f);
    outputGainSlider.setBounds(
        outputSliderX, 
        bounds.getY() + (bounds.getHeight() * 0.1f), 
        outputSliderWidth, 
        bounds.getWidth() * 0.1f);

    auto dryWetSliderWidth = bounds.getWidth() * 0.1f;
    auto dryWetSliderX = bounds.getX() + (bounds.getWidth() - dryWetSliderWidth) / 2.0f;
    dryWetMixSlider.setBounds(
        dryWetSliderX,
        bounds.getY(),
        dryWetSliderWidth,
        dryWetSliderWidth);

    // setting the bounds for the sinePath
    auto sinePathWidth = row2Bounds.getHeight() * 0.75f;
    sinePath.setBounds(
        row2Bounds.getX() + (row2Bounds.getWidth() * 0.25f),
        row2Bounds.getY() + row2Bounds.getHeight() * 0.1f,
        sinePathWidth,
        sinePathWidth * 0.5f);

    // setting the bounds for the pathSelector
    pathSelector.setBounds(
        row2Bounds.getX() + (row2Bounds.getWidth() * 0.75f) - sinePathWidth,
        row2Bounds.getY() + row2Bounds.getHeight() * 0.1f,
        sinePathWidth,
        sinePathWidth * 0.5f);
}

void AdvancedModeUI::setTheme(const Theme& currentTheme)
{
    setBackgroundColour(currentTheme.backgroundColour);
    setShadowColour(currentTheme.shadowColour);
    setLineHighlightColour(currentTheme.highlightColour);
    setDriveSliderColours(currentTheme.driveSliderFillColour, currentTheme.sliderBackgroundColour);
    setFilterSliderColours(currentTheme.filterSliderFillColour, currentTheme.sliderBackgroundColour);
    setGainSliderColours(currentTheme.gainSliderFillColour, currentTheme.sliderBackgroundColour);
    setMixSliderColours(currentTheme.mixSliderFillColour, currentTheme.sliderBackgroundColour);

    pathSelector.setTheme(currentTheme);
    sinePath.setTheme(currentTheme);

}

void AdvancedModeUI::setBackgroundColour(const juce::Colour& colour)
{
    backgroundColour = colour;
}

void AdvancedModeUI::setShadowColour(const juce::Colour& colour)
{
    shadowColour = colour;
}

void AdvancedModeUI::setLineHighlightColour(const juce::Colour& colour)
{
    lineHighlightColour = colour;
}

void AdvancedModeUI::setDriveSliderColours(const juce::Colour& fillColour, const juce::Colour& backgroundColour)
{
    driveSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColour);
    driveSlider.setColour(juce::Slider::rotarySliderOutlineColourId, backgroundColour);
    driveSlider.setColour(juce::Slider::thumbColourId, backgroundColour.brighter(0.4f));
}

void AdvancedModeUI::setFilterSliderColours(const juce::Colour& fillColour, const juce::Colour& backgroundColour)
{
    preFilterFreqSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColour);
    preFilterFreqSlider.setColour(juce::Slider::rotarySliderOutlineColourId, backgroundColour);
    preFilterFreqSlider.setColour(juce::Slider::thumbColourId, backgroundColour.brighter(0.4f));

    preFilterResSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColour);
    preFilterResSlider.setColour(juce::Slider::rotarySliderOutlineColourId, backgroundColour);
    preFilterResSlider.setColour(juce::Slider::thumbColourId, backgroundColour.brighter(0.4f));

    postFilterFreqSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColour);
    postFilterFreqSlider.setColour(juce::Slider::rotarySliderOutlineColourId, backgroundColour);
    postFilterFreqSlider.setColour(juce::Slider::thumbColourId, backgroundColour.brighter(0.4f));

    postFilterResSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColour);
    postFilterResSlider.setColour(juce::Slider::rotarySliderOutlineColourId, backgroundColour);
    postFilterResSlider.setColour(juce::Slider::thumbColourId, backgroundColour.brighter(0.4f));
}

void AdvancedModeUI::setGainSliderColours(const juce::Colour& fillColour, const juce::Colour& backgroundColour)
{
    inputGainSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColour);
    inputGainSlider.setColour(juce::Slider::rotarySliderOutlineColourId, backgroundColour);
    inputGainSlider.setColour(juce::Slider::thumbColourId, backgroundColour.brighter(0.4f));

    outputGainSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColour);
    outputGainSlider.setColour(juce::Slider::rotarySliderOutlineColourId, backgroundColour);
    outputGainSlider.setColour(juce::Slider::thumbColourId, backgroundColour.brighter(0.4f));
}

void AdvancedModeUI::setMixSliderColours(const juce::Colour& fillColour, const juce::Colour& backgroundColour)
{
    dryWetMixSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColour);
    dryWetMixSlider.setColour(juce::Slider::rotarySliderOutlineColourId, backgroundColour);
    dryWetMixSlider.setColour(juce::Slider::thumbColourId, backgroundColour.brighter(0.4f));
}


