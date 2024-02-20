/*
  ==============================================================================

    Settings.cpp
    Created: 20 Feb 2024 4:58:07pm
    Author:  zeush

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Settings.h"

//==============================================================================
Settings::Settings(float height, float width) : pluginHeight(height), pluginWidth(width)
{

    themePickerLabel.setText("Themes", juce::dontSendNotification);
    juce::Font h2Font = juce::Font(20.0f, juce::Font::bold);
    themePickerLabel.setFont(h2Font);
    addAndMakeVisible(themePickerLabel); // Make the label visible

    themePicker.addSectionHeading("Dark Themes");
    themePicker.addItem("Default", 1);
    themePicker.addItem("Vamp", 2);
    themePicker.addSeparator();
    themePicker.addSectionHeading("Light Themes");

    themePicker.setSelectedId(1, juce::dontSendNotification);
    addAndMakeVisible(themePicker);


    oversampling.setButtonText("oversampling");
    addAndMakeVisible(oversampling);

    setSize(pluginWidth, pluginHeight);
}

Settings::~Settings()
{
}

void Settings::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
}

void Settings::resized()
{
    auto bounds = getLocalBounds();

    oversampling.setBounds(bounds.getCentreX(), bounds.getCentreY(), 100, 100);


    auto themePickerWidth = 250.0f;
    auto themePickerHeight = 50.0f;

    themePickerLabel.setBounds(100, 100, 250, 30);
    themePicker.setBounds(bounds.getCentreX() - (themePickerWidth * 0.5), bounds.getY() + 50 + themePickerHeight, themePickerWidth, themePickerHeight);
}
