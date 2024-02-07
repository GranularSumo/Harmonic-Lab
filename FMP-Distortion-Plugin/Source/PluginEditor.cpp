/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"

//==============================================================================
FMPDistortionPluginAudioProcessorEditor::FMPDistortionPluginAudioProcessorEditor (FMPDistortionPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    distortionSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    distortionSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(distortionSlider);

    distortionAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treestate, parameterInfo::driveId, distortionSlider);


    algorithmSelector.setColour(juce::ComboBox::backgroundColourId, juce::Colour::fromString("#ff253353"));
    algorithmSelector.addItem("Softclipper", 1);
    algorithmSelector.addItem("Hardclipper", 2);
    algorithmSelector.addItem("BitCrusher", 3);
    algorithmSelector.addItem("SquareFolder", 4);
    algorithmSelector.addItem("WaveShaper", 5);
    algorithmSelector.addItem("WaveShaped-Clipper", 6);
    algorithmSelector.addItem("Feedback-Waveshaper", 7);
    algorithmSelector.addItem("Downsample", 8);
    algorithmSelector.onChange = [this]()
        {
            
            auto selectedAlgorithm = algorithmSelector.getText();
            textLoader.setAlgorithm(selectedAlgorithm);
            infoBox.setText(textLoader.getAlgorithmDescription(selectedAlgorithm), juce::dontSendNotification);
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

    addAndMakeVisible(logo);

    uiSelectorButton.setColour(juce::TextButton::buttonColourId, juce::Colour::fromString("#ff253353"));
    uiSelectorButton.setButtonText("Advanced Mode");
    addAndMakeVisible(uiSelectorButton);


    setSize (pluginWidth, pluginHeight);
}

FMPDistortionPluginAudioProcessorEditor::~FMPDistortionPluginAudioProcessorEditor()
{
}

//==============================================================================
void FMPDistortionPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds();

    // The bounds for the main plugin area
    auto mainAreaBounds = bounds.removeFromBottom(pluginHeight - (pluginHeight * 0.1f)).reduced(40);



    juce::Colour backgroundColour = juce::Colour::fromString("#ff253353");
    g.fillAll (backgroundColour);



    //Top Separator Line
    juce::Point<float> startPoint(mainAreaBounds.getX(), mainAreaBounds.getY());
    juce::Point<float> endPoint(mainAreaBounds.getRight(), mainAreaBounds.getY());
    juce::Line<float> topLine(startPoint, endPoint);
    g.setColour(juce::Colour::fromString("#ff47526D"));
    g.drawLine(topLine, 1.0f);

    // The bounds for the top section
    auto topSectionBounds = mainAreaBounds.removeFromTop(mainAreaBounds.getHeight() * 0.5);

    // Bottom Separator Line
    float widthToRemove = pluginWidth * 0.1f;

    juce::Point<float> bottomLineStartPoint(topSectionBounds.getX() + widthToRemove, topSectionBounds.getBottom());
    juce::Point<float> bottomLineEndPoint(topSectionBounds.getRight() - widthToRemove, topSectionBounds.getBottom());
    juce::Line<float> bottomLine(bottomLineStartPoint, bottomLineEndPoint);
    g.drawLine(bottomLine, 1.0f);

    
}

void FMPDistortionPluginAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    auto mainAreaBounds = bounds.removeFromBottom(pluginHeight - (pluginHeight * 0.1f)).reduced(40);
    auto topSectionBounds = mainAreaBounds.removeFromTop(mainAreaBounds.getHeight() * 0.5).reduced(pluginWidth / 3, 20);
    auto header = getLocalBounds().removeFromTop(pluginHeight * 0.15f);

    logo.setBounds(header.removeFromLeft(pluginWidth * 0.2).reduced(10));
    uiSelectorButton.setBounds(header.removeFromRight(pluginWidth * 0.25).reduced(40, 30));

    algorithmSelector.setBounds(topSectionBounds.removeFromTop(topSectionBounds.getHeight() * 0.15));
    distortionSlider.setBounds(topSectionBounds.reduced(10, 10));



    infoBoxTitle.setBounds(mainAreaBounds.removeFromTop(mainAreaBounds.getHeight() * 0.2));

    float widthToRemove = pluginWidth * 0.1f;
    infoBox.setBounds(mainAreaBounds.reduced(widthToRemove, 0));

}

void FMPDistortionPluginAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBox)
{

}



