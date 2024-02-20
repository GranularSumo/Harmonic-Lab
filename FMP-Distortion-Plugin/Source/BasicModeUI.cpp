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

            auto selectedAlgorithm = algorithmSelector.getText();
            textLoader.setAlgorithm(selectedAlgorithm);
            infoBox.setText(textLoader.getAlgorithmDescription(selectedAlgorithm), juce::dontSendNotification);

            pathSelector.setCurrentPath(pathSelector.getPath(algorithmSelector.getSelectedId()));
        };

    addAndMakeVisible(algorithmSelector);

    selectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, parameterInfo::distortionTypeId, algorithmSelector);


    infoBox.setReadOnly(true);
    infoBox.setColour(juce::TextEditor::backgroundColourId, juce::Colour::fromString("#ff253353"));
    infoBox.setColour(juce::TextEditor::outlineColourId, juce::Colour::fromString("#ff47526D"));
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
    pathSelector.setCurrentPath(SvgPathManager::softclip);

    setSize(pluginWidth, pluginHeight);
}

BasicModeUI::~BasicModeUI()
{
}

void BasicModeUI::paint (juce::Graphics& g)
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

    // draws a shadow for the separator line between row 2 and row 3
    g.setColour(shadowColour);
    g.drawLine(
        row2Bounds.getX() + (row2Bounds.getWidth() * 0.1f),
        row2Bounds.getBottom() - 1,
        row2Bounds.getRight() - (row2Bounds.getWidth() * 0.1f),
        row2Bounds.getBottom() - 1);

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
    auto footerBounds = bounds.removeFromBottom(pluginHeight * 0.05f);
    auto mainAreaHeight = bounds.getHeight();
    auto row1Bounds = bounds.removeFromTop(mainAreaHeight * 0.2f);
    auto row2Bounds = bounds.removeFromTop(mainAreaHeight * 0.25f);
    auto row3Bounds = bounds.removeFromTop(bounds.getHeight() * 0.2);

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
        row2Bounds.getWidth() * 0.25,
        row2Bounds.getHeight());


    float heightToRemove = row3Bounds.getHeight() * 0.15f;
    infoBoxTitle.setBounds(
        row3Bounds.getX(),
        row3Bounds.getY(),
        row3Bounds.getWidth(),
        row3Bounds.getHeight());

    
    float widthToRemove = pluginWidth * 0.1f;
    infoBox.setBounds(
        bounds.getX() + widthToRemove,
        bounds.getY(),
        bounds.getWidth() - (widthToRemove * 2),
        bounds.getHeight() - (heightToRemove * 2));

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

void BasicModeUI::setBackgroundColour(juce::Colour& colour)
{
    backgroundColour = colour;
}

void BasicModeUI::setShadowColour(juce::Colour& colour)
{
    shadowColour = colour;
}

void BasicModeUI::setLineHighlightColour(juce::Colour& colour)
{
    lineHighlightColour = colour;
}

void BasicModeUI::setDriveSliderColours(juce::Colour& fillColour, juce::Colour& backgroundColour)
{
    driveSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColour);
    driveSlider.setColour(juce::Slider::rotarySliderOutlineColourId, backgroundColour);
    driveSlider.setColour(juce::Slider::thumbColourId, backgroundColour.brighter(0.4f));
}