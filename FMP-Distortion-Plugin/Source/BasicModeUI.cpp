/*
  ==============================================================================

    BasicMode.cpp
    Created: 8 Feb 2024 12:44:20am
    Author:  zeush

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BasicModeUI.h"

//==============================================================================




BasicModeUI::BasicModeUI(FMPDistortionPluginAudioProcessor& processor, float height, float width) : audioProcessor(processor), pluginHeight(height), pluginWidth(width)
{


    driveSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(driveSlider);

    distortionAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treestate, parameterInfo::driveId, driveSlider);



    infoBox.setReadOnly(true);
    infoBox.setMultiLine(true);

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

    algorithmSelector.onChange = [this]()
        {

            selectedPath = algorithmSelector.getText();
            textLoader.setAlgorithm(selectedPath);
            infoBox.setText(textLoader.getAlgorithmDescription(selectedPath), juce::dontSendNotification);

            pathSelector.setCurrentPath(pathSelector.getPath(algorithmSelector.getSelectedId()));
        };

    addAndMakeVisible(algorithmSelector);

    selectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, parameterInfo::distortionTypeId, algorithmSelector);

    addAndMakeVisible(infoBox);


    infoBoxTitle.setText("Algorithm Details", juce::NotificationType::dontSendNotification);
    juce::Font h2Font = juce::Font(20.0f, juce::Font::bold);
    infoBoxTitle.setFont(h2Font);
    infoBoxTitle.setJustificationType(juce::Justification::centred);
    infoBoxTitle.setColour(juce::Label::textColourId, juce::Colour::fromString("#ffFAFBFB"));
    addAndMakeVisible(infoBoxTitle);

    addAndMakeVisible(sinePath);
    sinePath.setCurrentPath(SvgPathManager::sine);

    addAndMakeVisible(pathSelector);
    pathSelector.setCurrentPath(pathSelector.getPath(algorithmSelector.getSelectedId()));

    setSize(pluginWidth, pluginHeight);
}

BasicModeUI::~BasicModeUI()
{
}

void BasicModeUI::paint (juce::Graphics& g)
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

void BasicModeUI::resized()
{
    auto bounds = getLocalBounds();
    auto headerBounds = bounds.removeFromTop(pluginHeight * 0.1f);
    auto footerBounds = bounds.removeFromBottom(pluginHeight * 0.06f);
    auto mainAreaHeight = bounds.getHeight();
    auto row1Bounds = bounds.removeFromTop(mainAreaHeight * 0.2f);
    auto row2Bounds = bounds.removeFromTop(mainAreaHeight * 0.25f);
    auto row3Bounds = bounds.removeFromTop(bounds.getHeight() * 0.2);

    float yOffset = headerBounds.getHeight() * 0.25f;

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
        row2Bounds.getWidth() * 0.25,
        row2Bounds.getHeight());


    float heightToRemove = row3Bounds.getHeight() * 0.15f;
    infoBoxTitle.setBounds(
        row3Bounds.getX(),
        row3Bounds.getY() - yOffset,
        row3Bounds.getWidth(),
        row3Bounds.getHeight());

    
    float widthToRemove = pluginWidth * 0.1f;
    infoBox.setBounds(
        bounds.getX() + widthToRemove,
        bounds.getY() - yOffset,
        bounds.getWidth() - (widthToRemove * 2),
        bounds.getHeight() - (heightToRemove * 2));

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

void BasicModeUI::setTheme(const Theme& currentTheme)
{
    setBackgroundColour(currentTheme.backgroundColour);
    setShadowColour(currentTheme.shadowColour);
    setLineHighlightColour(currentTheme.highlightColour);
    setDriveSliderColours(currentTheme.driveSliderFillColour, currentTheme.sliderBackgroundColour);
    setInfoBoxColours(currentTheme.backgroundColour, currentTheme.highlightColour);

    pathSelector.setTheme(currentTheme);
    sinePath.setTheme(currentTheme);

    algorithmSelector.setColour(juce::ComboBox::backgroundColourId, currentTheme.shadowColour);
    algorithmSelector.setColour(juce::ComboBox::outlineColourId, currentTheme.highlightColour);
}

void BasicModeUI::setBackgroundColour(const juce::Colour& colour)
{
    backgroundColour = colour;
}

void BasicModeUI::setShadowColour(const juce::Colour& colour)
{
    shadowColour = colour;
}

void BasicModeUI::setLineHighlightColour(const juce::Colour& colour)
{
    lineHighlightColour = colour;
}

void BasicModeUI::setDriveSliderColours(const juce::Colour& fillColour, const juce::Colour& backgroundColour)
{
    driveSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColour);
    driveSlider.setColour(juce::Slider::rotarySliderOutlineColourId, backgroundColour);
    driveSlider.setColour(juce::Slider::thumbColourId, juce::Colours::transparentBlack);
}

void BasicModeUI::setInfoBoxColours(const juce::Colour& backgroundColour, const juce::Colour& highlightColour)
{
    infoBox.setColour(juce::TextEditor::backgroundColourId, backgroundColour);
    infoBox.setColour(juce::TextEditor::outlineColourId, lineHighlightColour);
}



