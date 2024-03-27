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
    algorithmSelector.addSectionHeading("Symmetrical");
    algorithmSelector.addItem("Softclipper", 1);
    algorithmSelector.addItem("Broken Softclipper", 2);
    algorithmSelector.addItem("Hardclipper", 3);
    algorithmSelector.addItem("Wavefolder", 4);
    algorithmSelector.addItem("Foldback", 5);

    algorithmSelector.addSeparator();
    algorithmSelector.addSectionHeading("Asymmetrical");
    algorithmSelector.addItem("Assymetric Softclipper", 6);
    algorithmSelector.addItem("Bias Shaper", 7);
    algorithmSelector.addItem("Bias Folder", 8);
    algorithmSelector.addItem("Fold Crusher", 9);
    algorithmSelector.addItem("Dual Path BitFolder", 10);

    algorithmSelector.addSeparator();
    algorithmSelector.addSectionHeading("Quantization");
    algorithmSelector.addItem("Bitcrusher", 11);
    algorithmSelector.addItem("Square Folder", 12);
    algorithmSelector.addItem("Downsample", 13);



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

    addAndMakeVisible(preFilterFreqLabel);
    preFilterFreqLabel.setText("Cutoff", juce::dontSendNotification);
    preFilterFreqLabel.setJustificationType(juce::Justification::centredTop);


    addAndMakeVisible(preFilterResSlider);
    preFilterResSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    preFilterResSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    preFilterResAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treestate, parameterInfo::preFilterResId, preFilterResSlider);

    addAndMakeVisible(preFilterResLabel);
    preFilterResLabel.setText("Res", juce::dontSendNotification);
	preFilterResLabel.setJustificationType(juce::Justification::centredTop);
    
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


    addAndMakeVisible(postFilterFreqLabel);
    postFilterFreqLabel.setText("Cutoff", juce::dontSendNotification);
    postFilterFreqLabel.setJustificationType(juce::Justification::centredTop);

    addAndMakeVisible(postFilterResSlider);
    postFilterResSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    postFilterResSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    postFilterResAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treestate, parameterInfo::postFilterResId, postFilterResSlider);

    addAndMakeVisible(postFilterResLabel);
    postFilterResLabel.setText("Res", juce::dontSendNotification);
	postFilterResLabel.setJustificationType(juce::Justification::centredTop);

    // Input slider setup

    addAndMakeVisible(inputGainSlider);
    inputGainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    inputGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    inputGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treestate, parameterInfo::inputGainId, inputGainSlider);

    addAndMakeVisible(inputGainLabel);
    inputGainLabel.setText("Input", juce::dontSendNotification);
    inputGainLabel.setJustificationType(juce::Justification::centredTop);

    // Output slider setup

    addAndMakeVisible(outputGainSlider);
    outputGainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    outputGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    outputGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treestate, parameterInfo::outputGainId, outputGainSlider);

    addAndMakeVisible(outputGainLabel);
    outputGainLabel.setText("Output", juce::dontSendNotification);
    outputGainLabel.setJustificationType(juce::Justification::centredTop);

    // Mix slider setup

    addAndMakeVisible(dryWetMixSlider);
    dryWetMixSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    dryWetMixSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    dryWetAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treestate, parameterInfo::dryWetId, dryWetMixSlider);

    addAndMakeVisible(dryWetMixLabel);
    dryWetMixLabel.setText("Mix", juce::dontSendNotification);
    dryWetMixLabel.setJustificationType(juce::Justification::centredTop);

    // svg path setup

    addAndMakeVisible(sinePath);
    sinePath.setCurrentPath(SvgPathManager::sine);
    addAndMakeVisible(pathSelector);
    pathSelector.setCurrentPath(pathSelector.getPath(algorithmSelector.getSelectedId()));


    addAndMakeVisible(focusOverlay);
    focusOverlay.setInterceptsMouseClicks(false, false);
    showOverlay(false);
}

AdvancedModeUI::~AdvancedModeUI()
{
}

void AdvancedModeUI::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    auto headerBounds = bounds.removeFromTop(pluginHeight * 0.1f);
    auto footerBounds = bounds.removeFromBottom(pluginHeight * 0.06f);
    auto mainAreaHeight = bounds.getHeight();
    auto row1Bounds = bounds.removeFromTop(mainAreaHeight * 0.2f);
    auto row2Bounds = bounds.removeFromTop(mainAreaHeight * 0.25f);
    auto row3Bounds = bounds.removeFromTop(mainAreaHeight * 0.375f);
    

    float yOffset = headerBounds.getHeight() * 0.25f;

    // draws a separator line between row 2 and row 3
    g.setColour(lineHighlightColour);
    g.drawLine(
        row2Bounds.getX() + (row2Bounds.getWidth() * 0.1f), 
        row2Bounds.getBottom() - yOffset, 
        row2Bounds.getRight() - (row2Bounds.getWidth() * 0.1f), 
        row2Bounds.getBottom() - yOffset);

    // draws a separator line in the middle of row 3
    g.drawLine(
        row3Bounds.getCentreX(),
        row3Bounds.getY() + row3Bounds.getHeight() * 0.25 - yOffset,
        row3Bounds.getCentreX(),
        row3Bounds.getBottom() - row3Bounds.getHeight() * 0.25);

    // draws a separator line between row 3 and row 4
    g.drawLine(
        row3Bounds.getX() + (row3Bounds.getWidth() * 0.1f),
        row3Bounds.getBottom() - yOffset,
        row3Bounds.getRight() - (row3Bounds.getWidth() * 0.1f),
        row3Bounds.getBottom() - yOffset);


    // draws a shadow for the separator line between row 2 and row 3
    g.setColour(shadowColour);
    g.drawLine(
        row2Bounds.getX() + (row2Bounds.getWidth() * 0.1f),
        row2Bounds.getBottom() - 1 - yOffset,
        row2Bounds.getRight() - (row2Bounds.getWidth() * 0.1f),
        row2Bounds.getBottom() - 1 - yOffset);
    g.drawLine(
        row2Bounds.getX() + (row2Bounds.getWidth() * 0.1f),
        row2Bounds.getBottom() - 2 - yOffset,
        row2Bounds.getRight() - (row2Bounds.getWidth() * 0.1f),
        row2Bounds.getBottom() - 2 - yOffset);

    // draws a shadow for the separator line between row 3 and row 4
    g.drawLine(
        row3Bounds.getX() + (row3Bounds.getWidth() * 0.1f),
        row3Bounds.getBottom() - 1 - yOffset,
        row3Bounds.getRight() - (row3Bounds.getWidth() * 0.1f),
        row3Bounds.getBottom() - 1 - yOffset);
    g.drawLine(
        row3Bounds.getX() + (row3Bounds.getWidth() * 0.1f),
        row3Bounds.getBottom() - 2 - yOffset,
        row3Bounds.getRight() - (row3Bounds.getWidth() * 0.1f),
        row3Bounds.getBottom() - 2 - yOffset);
    
    // draws a shadow in the middle of row 3
    g.drawLine(
        row3Bounds.getCentreX() - 1,
        row3Bounds.getY() + row3Bounds.getHeight() * 0.25 - yOffset,
        row3Bounds.getCentreX() - 1,
        row3Bounds.getBottom() - row3Bounds.getHeight() * 0.25 - yOffset);

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
    auto footerBounds = bounds.removeFromBottom(pluginHeight * 0.06f);
    float yOffset = headerBounds.getHeight() * 0.25f;

    focusOverlay.setBounds(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight() - 12.0f);

    auto mainAreaHeight = bounds.getHeight();
    auto row1Bounds = bounds.removeFromTop(mainAreaHeight * 0.2f);
    auto row2Bounds = bounds.removeFromTop(mainAreaHeight * 0.25f);
    auto row3Bounds = bounds.removeFromTop(mainAreaHeight * 0.375f);
    auto row3LeftBounds = row3Bounds.removeFromLeft(row3Bounds.getWidth() * 0.5);
    



    // setting the bounds for components in row 1
    algorithmSelector.setBounds(
        row1Bounds.getX() + (row1Bounds.getWidth() * 0.375f), 
        row1Bounds.getY() + (row1Bounds.getHeight() * 0.4f) - yOffset, 
        row1Bounds.getWidth() * 0.25f,
        row1Bounds.getHeight() * 0.25f);

    // setting the bounds for the components in row 2
    driveSlider.setBounds(
        row2Bounds.getX() + (row2Bounds.getWidth() * 0.375f), 
        row2Bounds.getY() - (row1Bounds.getHeight() * 0.25) - yOffset, 
        row2Bounds.getWidth() *  0.25, 
        row2Bounds.getHeight());

    //setting the bounds for the left components in row 3
    preFilterLabel.setBounds(
        row3LeftBounds.getX() + row3Bounds.getWidth() * 0.375,
        row3LeftBounds.getY() + row3Bounds.getHeight() * 0.1f - yOffset,
        row3LeftBounds.getWidth() * 0.5,
        row3LeftBounds.getHeight() * 0.1f);

    preFilterButton.setBounds(
        row3LeftBounds.getRight() - row3LeftBounds.getWidth() * 0.3,
        row3LeftBounds.getY() + row3Bounds.getHeight() * 0.1f - yOffset,
        row3LeftBounds.getWidth() * 0.1,
        row3LeftBounds.getHeight() * 0.1f);

    preFilterSelector.setBounds(
        row3LeftBounds.getX() + row3Bounds.getWidth() * 0.375f,
        row3LeftBounds.getY() + row3Bounds.getHeight() * 0.25f - yOffset,
        row3LeftBounds.getWidth() * 0.5,
        row3LeftBounds.getHeight() * 0.15f);

    preFilterFreqSlider.setBounds(
        row3LeftBounds.getX() + row3Bounds.getWidth() * 0.375f,
        row3LeftBounds.getY() + row3Bounds.getHeight() * 0.45f - yOffset,
        row3LeftBounds.getWidth() * 0.25,
        row3LeftBounds.getHeight() * 0.4f);

    preFilterFreqLabel.setBounds(
		row3LeftBounds.getX() + row3Bounds.getWidth() * 0.375f,
		row3LeftBounds.getY() + row3Bounds.getHeight() * 0.8f - yOffset,
		row3LeftBounds.getWidth() * 0.25,
		row3LeftBounds.getHeight() * 0.1f);

    preFilterResSlider.setBounds(
        row3LeftBounds.getX() + (row3Bounds.getWidth() * 0.375) + row3LeftBounds.getWidth() * 0.25f,
        row3LeftBounds.getY() + row3Bounds.getHeight() * 0.45f - yOffset,
        row3LeftBounds.getWidth() * 0.25f,
        row3LeftBounds.getHeight() * 0.4f);

    preFilterResLabel.setBounds(
        row3LeftBounds.getX() + (row3Bounds.getWidth() * 0.375) + row3LeftBounds.getWidth() * 0.25f,
        row3LeftBounds.getY() + row3Bounds.getHeight() * 0.8f - yOffset,
        row3LeftBounds.getWidth() * 0.25f,
        row3LeftBounds.getHeight() * 0.1f);

    //setting the bounds for the right components in row 3
    auto postFilterLabelHeight = row3Bounds.getHeight() * 0.1f;
    postFilterLabel.setBounds(
        row3Bounds.getX() + row3Bounds.getWidth() * 0.125f,
        row3Bounds.getY() + postFilterLabelHeight - yOffset,
        row3Bounds.getWidth() * 0.5f,
        postFilterLabelHeight);

    postFilterButton.setBounds(
        row3Bounds.getRight() - row3Bounds.getWidth() * 0.55,
        row3Bounds.getY() + row3Bounds.getHeight() * 0.1f - yOffset,
        row3Bounds.getWidth() * 0.1,
        row3Bounds.getHeight() * 0.1f);

    postFilterSelector.setBounds(
        row3Bounds.getX() + row3Bounds.getWidth() * 0.125,
        row3Bounds.getY() + row3Bounds.getHeight() * 0.25f - yOffset,
        row3Bounds.getWidth() * 0.5,
        row3Bounds.getHeight() * 0.15f);

    postFilterFreqSlider.setBounds(
        row3Bounds.getX() + row3Bounds.getWidth() * 0.125,
        row3Bounds.getY() + row3Bounds.getHeight() * 0.45f - yOffset,
        row3Bounds.getWidth() * 0.25,
        row3Bounds.getHeight() * 0.4f);

    postFilterFreqLabel.setBounds(
        row3Bounds.getX() + row3Bounds.getWidth() * 0.125,
		row3Bounds.getY() + row3Bounds.getHeight() * 0.8f - yOffset,
		row3Bounds.getWidth() * 0.25,
		row3Bounds.getHeight() * 0.1f);

    postFilterResSlider.setBounds(
        row3Bounds.getX() + (row3Bounds.getWidth() * 0.125) + row3Bounds.getWidth() * 0.25f,
        row3Bounds.getY() + row3Bounds.getHeight() * 0.45f - yOffset,
        row3Bounds.getWidth() * 0.25f,
        row3Bounds.getHeight() * 0.4f);

    postFilterResLabel.setBounds(
        row3Bounds.getX() + (row3Bounds.getWidth() * 0.125) + row3Bounds.getWidth() * 0.25f,
        row3Bounds.getY() + row3Bounds.getHeight() * 0.8f - yOffset,
        row3Bounds.getWidth() * 0.25f,
        row3Bounds.getHeight() * 0.1f);
    

    //setting the bounds for the sliders in row 4
    auto inputSliderWidth = bounds.getWidth() * 0.075f;
    auto inputSliderX = bounds.getX() + ((bounds.getWidth() - inputSliderWidth) / 2.0f) - (inputSliderWidth * 1.25f);
    inputGainSlider.setBounds(
        inputSliderX, 
        bounds.getY() + (bounds.getHeight() * 0.1f) - yOffset,
        inputSliderWidth, 
        bounds.getWidth() * 0.1f);

    inputGainLabel.setBounds(
		inputSliderX,
		bounds.getY() + (bounds.getHeight() * 0.76f) - yOffset,
		inputSliderWidth,
		bounds.getWidth() * 0.1f);

    auto outputSliderWidth = bounds.getWidth() * 0.075f;
    auto outputSliderX = bounds.getX() + ((bounds.getWidth() - outputSliderWidth) / 2.0f) + (outputSliderWidth * 1.25f);
    outputGainSlider.setBounds(
        outputSliderX, 
        bounds.getY() + (bounds.getHeight() * 0.1f) - yOffset, 
        outputSliderWidth, 
        bounds.getWidth() * 0.1f);

    outputGainLabel.setBounds(
        outputSliderX,
        bounds.getY() + (bounds.getHeight() * 0.76f) - yOffset,
        outputSliderWidth,
        bounds.getWidth() * 0.1f);

    auto dryWetSliderWidth = bounds.getWidth() * 0.1f;
    auto dryWetSliderX = bounds.getX() + (bounds.getWidth() - dryWetSliderWidth) / 2.0f;
    dryWetMixSlider.setBounds(
        dryWetSliderX,
        bounds.getY() - yOffset,
        dryWetSliderWidth,
        dryWetSliderWidth);

    dryWetMixLabel.setBounds(
        dryWetSliderX,
		bounds.getY() + (bounds.getHeight() * 0.76f) - yOffset,
		dryWetSliderWidth,
        bounds.getWidth() * 0.1f);

    // setting the bounds for the sinePath
    auto sinePathWidth = row2Bounds.getHeight() * 0.75f;
    sinePath.setBounds(
        row2Bounds.getX() + (row2Bounds.getWidth() * 0.25f),
        row2Bounds.getY() + row2Bounds.getHeight() * 0.1f - yOffset,
        sinePathWidth,
        sinePathWidth * 0.5f);

    // setting the bounds for the pathSelector
    pathSelector.setBounds(
        row2Bounds.getX() + (row2Bounds.getWidth() * 0.75f) - sinePathWidth,
        row2Bounds.getY() + row2Bounds.getHeight() * 0.1f - yOffset,
        sinePathWidth,
        sinePathWidth * 0.5f);

}

juce::String AdvancedModeUI::getCurrentAlgorithm()
{ 
    return algorithmSelector.getText();
}

void AdvancedModeUI::setCurrentPath(int index)
{
    pathSelector.setCurrentPath(pathSelector.getPath(index));
}

juce::ComboBox& AdvancedModeUI::getAlgorithmSelector()
{
    return algorithmSelector;
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

    algorithmSelector.setColour(juce::ComboBox::backgroundColourId, currentTheme.shadowColour);
    algorithmSelector.setColour(juce::ComboBox::outlineColourId, currentTheme.highlightColour);

    preFilterSelector.setColour(juce::ComboBox::backgroundColourId, currentTheme.shadowColour);
	preFilterSelector.setColour(juce::ComboBox::outlineColourId, currentTheme.highlightColour);

	postFilterSelector.setColour(juce::ComboBox::backgroundColourId, currentTheme.shadowColour);
	postFilterSelector.setColour(juce::ComboBox::outlineColourId, currentTheme.highlightColour);

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
    driveSlider.setColour(juce::Slider::thumbColourId, juce::Colours::transparentBlack);
}

void AdvancedModeUI::setFilterSliderColours(const juce::Colour& fillColour, const juce::Colour& backgroundColour)
{
    preFilterFreqSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColour);
    preFilterFreqSlider.setColour(juce::Slider::rotarySliderOutlineColourId, backgroundColour);
    preFilterFreqSlider.setColour(juce::Slider::thumbColourId, juce::Colours::transparentBlack);

    preFilterResSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColour);
    preFilterResSlider.setColour(juce::Slider::rotarySliderOutlineColourId, backgroundColour);
    preFilterResSlider.setColour(juce::Slider::thumbColourId, juce::Colours::transparentBlack);

    postFilterFreqSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColour);
    postFilterFreqSlider.setColour(juce::Slider::rotarySliderOutlineColourId, backgroundColour);
    postFilterFreqSlider.setColour(juce::Slider::thumbColourId, juce::Colours::transparentBlack);

    postFilterResSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColour);
    postFilterResSlider.setColour(juce::Slider::rotarySliderOutlineColourId, backgroundColour);
    postFilterResSlider.setColour(juce::Slider::thumbColourId, juce::Colours::transparentBlack);
}

void AdvancedModeUI::setGainSliderColours(const juce::Colour& fillColour, const juce::Colour& backgroundColour)
{
    inputGainSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColour);
    inputGainSlider.setColour(juce::Slider::rotarySliderOutlineColourId, backgroundColour);
    inputGainSlider.setColour(juce::Slider::thumbColourId, juce::Colours::transparentBlack);

    outputGainSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColour);
    outputGainSlider.setColour(juce::Slider::rotarySliderOutlineColourId, backgroundColour);
    outputGainSlider.setColour(juce::Slider::thumbColourId, juce::Colours::transparentBlack);
}

void AdvancedModeUI::setMixSliderColours(const juce::Colour& fillColour, const juce::Colour& backgroundColour)
{
    dryWetMixSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColour);
    dryWetMixSlider.setColour(juce::Slider::rotarySliderOutlineColourId, backgroundColour);
    dryWetMixSlider.setColour(juce::Slider::thumbColourId, juce::Colours::transparentBlack);
}

void AdvancedModeUI::setHighlightedArea(juce::String component)
{

    if (component == "Algorithm Selector")
    {
        focusOverlay.clearHighlightedAreas();
        auto algorithmSelectorBounds = focusOverlay.getLocalArea(this, algorithmSelector.getBounds().expanded(15, 10));
        focusOverlay.addHighlightedAreaBounds(algorithmSelectorBounds);

    }

    if (component == "Algorithm Display")
    {
        focusOverlay.clearHighlightedAreas();
        auto sinepathBounds = focusOverlay.getLocalArea(this, sinePath.getBounds().expanded(5, 5));
        focusOverlay.addHighlightedAreaBounds(sinepathBounds);

        auto pathSelectorBounds = focusOverlay.getLocalArea(this, pathSelector.getBounds().expanded(5, 5));
        focusOverlay.addHighlightedAreaBounds(pathSelectorBounds);
    }

    if (component == "Drive")
    {
        focusOverlay.clearHighlightedAreas(); // Clear existing highlights
        auto driveBounds = focusOverlay.getLocalArea(this, driveSlider.getBounds());
        focusOverlay.addHighlightedAreaBounds(driveBounds);

        auto inputBounds = focusOverlay.getLocalArea(this, inputGainSlider.getBounds());
        focusOverlay.addHighlightedAreaBounds(inputBounds);

    }
    else if (component == "Pre Filter Bypass")
    {
        focusOverlay.clearHighlightedAreas();
        juce::Rectangle<int> combinedBounds = preFilterButton.getBounds();
        combinedBounds = combinedBounds.getUnion(preFilterLabel.getBounds());
        auto overlayBounds = focusOverlay.getLocalArea(this, combinedBounds);
        focusOverlay.setHighlightedAreaBounds(overlayBounds.expanded(10));
    }
    else if (component == "Pre Filter Selector")
    {
        focusOverlay.clearHighlightedAreas(); // Clear existing highlights
        auto filterSelector = focusOverlay.getLocalArea(this, preFilterSelector.getBounds());
        focusOverlay.addHighlightedAreaBounds(filterSelector);
    }

    else if (component == "Pre Filter Controls")
    {

        focusOverlay.clearHighlightedAreas(); // Clear existing highlights
        juce::Rectangle<int> combinedBounds = preFilterFreqSlider.getBounds();
        combinedBounds = combinedBounds.getUnion(preFilterResSlider.getBounds());

        // Now, you need to translate these bounds to the coordinate space of the overlay component
        auto overlayBounds = focusOverlay.getLocalArea(this, combinedBounds);

        // Set the translated bounds as the highlighted area
        focusOverlay.setHighlightedAreaBounds(overlayBounds.expanded(10));
    }

    else if (component == "Post Filter Bypass")
    {

        focusOverlay.clearHighlightedAreas();
        juce::Rectangle<int> combinedBounds = postFilterButton.getBounds();
        combinedBounds = combinedBounds.getUnion(postFilterLabel.getBounds());
        auto overlayBounds = focusOverlay.getLocalArea(this, combinedBounds);

        focusOverlay.setHighlightedAreaBounds(overlayBounds.expanded(10));
    }
    else if (component == "Post Filter Selector")
    {
        focusOverlay.clearHighlightedAreas(); // Clear existing highlights
        auto filterSelector = focusOverlay.getLocalArea(this, postFilterSelector.getBounds());
        focusOverlay.addHighlightedAreaBounds(filterSelector);
    }
    else if (component == "Post Filter Controls")
    {

        focusOverlay.clearHighlightedAreas(); // Clear existing highlights
        juce::Rectangle<int> combinedBounds = postFilterFreqSlider.getBounds();
        combinedBounds = combinedBounds.getUnion(postFilterResSlider.getBounds());

        // Now, you need to translate these bounds to the coordinate space of the overlay component
        auto overlayBounds = focusOverlay.getLocalArea(this, combinedBounds);

        // Set the translated bounds as the highlighted area
        focusOverlay.setHighlightedAreaBounds(overlayBounds.expanded(10));
    }

    else if (component == "Mix")
    {
        focusOverlay.clearHighlightedAreas();
        auto mixBounds = focusOverlay.getLocalArea(this, dryWetMixSlider.getBounds());
        focusOverlay.addHighlightedAreaBounds(mixBounds);
    }

    else if (component == "Output Gain")
    {
        focusOverlay.clearHighlightedAreas();
        auto outputBounds = focusOverlay.getLocalArea(this, outputGainSlider.getBounds());
        focusOverlay.addHighlightedAreaBounds(outputBounds);
    }
}

void AdvancedModeUI::clearHighlightedAreas()
{
    focusOverlay.clearHighlightedAreas();
    repaint();
}

void AdvancedModeUI::showOverlay(bool shouldShow)
{
    focusOverlay.setVisible(shouldShow);
    if (!shouldShow)
    {
        clearHighlightedAreas();
    }
}


