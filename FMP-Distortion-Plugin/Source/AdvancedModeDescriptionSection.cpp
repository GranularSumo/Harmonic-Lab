/*
  ==============================================================================

    AdvancedModeDescriptionSection.cpp
    Created: 23 Feb 2024 5:47:59pm
    Author:  zeush

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdvancedModeDescriptionSection.h"

//==============================================================================
AdvancedModeDescriptionSection::AdvancedModeDescriptionSection()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    //addAndMakeVisible(descriptionBox);
    //descriptionBox.setMultiLine(true);
    //descriptionBox.setReadOnly(true);
    //descriptionBox.setScrollbarsShown(true);
    //descriptionBox.setCaretVisible(false);

    addAndMakeVisible(viewport);
    viewport.setViewedComponent(&attrStringComp, false);
    viewport.setScrollBarsShown(true, false);


    addAndMakeVisible(descriptionLabel);
    descriptionLabel.setText("Algorithm Description", juce::dontSendNotification);
    descriptionLabel.setJustificationType(juce::Justification::centred);
    juce::Font font(20.0f, juce::Font::bold);
    descriptionLabel.setFont(font);


}

AdvancedModeDescriptionSection::~AdvancedModeDescriptionSection()
{
}

void AdvancedModeDescriptionSection::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    g.fillAll(backgroundColour.brighter(0.1f));

    g.setColour(shadowColour);
    g.drawLine(bounds.getX(), bounds.getY(), bounds.getRight(), bounds.getY());
    g.drawLine(bounds.getX(), bounds.getBottom(), bounds.getRight(), bounds.getBottom());

    g.setColour(highlightColour.brighter(0.05f));
    g.drawLine(bounds.getX(), bounds.getY() + 1, bounds.getRight(), bounds.getY() + 1);
    g.drawLine(bounds.getX(), bounds.getBottom() - 1, bounds.getRight(), bounds.getBottom() - 1);

    auto area = getLocalBounds().reduced(10);
    area.removeFromTop(40);
    area.removeFromBottom(80);

    g.setColour(highlightColour);
    g.drawLine(area.getX(), area.getY() - 2, area.getRight() - 8, area.getY() - 2);
    g.setColour(highlightColour.brighter(0.1f));
    g.drawLine(area.getX(), area.getBottom() + 2, area.getRight() - 8, area.getBottom() + 2);
    g.setColour(shadowColour.darker(0.2f));
    g.drawLine(area.getX(), area.getY() - 1, area.getRight() - 8, area.getY() - 1);
    g.drawLine(area.getX(), area.getBottom() + 1, area.getRight() - 8, area.getBottom() + 1);
}

void AdvancedModeDescriptionSection::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto bounds = getLocalBounds();
    auto yOffSet = 50;
    auto descriptionBoxAdjustedBounds = bounds.reduced(10, yOffSet);
    //descriptionBox.setBounds(descriptionBoxAdjustedBounds.getX(), descriptionBoxAdjustedBounds.getY(), descriptionBoxAdjustedBounds.getWidth(), descriptionBoxAdjustedBounds.getHeight() + yOffSet - 10);
    viewport.setBounds(descriptionBoxAdjustedBounds.getX(), descriptionBoxAdjustedBounds.getY(), descriptionBoxAdjustedBounds.getWidth(), descriptionBoxAdjustedBounds.getHeight() + yOffSet - 10);
    attrStringComp.setSize(viewport.getWidth(), 900);

    descriptionLabel.setBounds(bounds.removeFromTop(50.0f));

}

void AdvancedModeDescriptionSection::setDescription(juce::String& algorithm)
{
    //descriptionBox.setText(textLoader.getAlgorithmDescription(algorithm), juce::dontSendNotification);

    juce::AttributedString description;

    // Match algorithm text and set description accordingly
    
    if (algorithm == "Softclipper")
    {
        description = textLoader.createSoftclipperDescription();
    }
    else if (algorithm == "Broken Softclipper")
    {
        description = textLoader.createBrokenSoftclipperDescription();
    }
    else if (algorithm == "Hardclipper")
    {
        description = textLoader.createHardclipperDescription();
    }
    else if (algorithm == "Wavefolder")
    {
        description = textLoader.createWavefolderDescription();
    }
    else if (algorithm == "Foldback")
    {
        description = textLoader.createFoldbackDescription();
    }
    else if (algorithm == "Asymmetric Softclipper")
    {
        description = textLoader.createAsymmetricSoftclipperDescription();
    }
    else if (algorithm == "Bias Shaper")
    {
        description = textLoader.createBiasShaperDescription();
    }
    else if (algorithm == "Bias Folder")
    {
        description = textLoader.createBiasFolderDescription();
    }
    else if (algorithm == "Fold Crusher")
    {
        description = textLoader.createFoldCrusherDescription();
    }
    else if (algorithm == "Dual Path BitFolder")
    {
        description = textLoader.createDualPathBitFolderDescription();
    }
    else if (algorithm == "Bitcrusher")
    {
        description = textLoader.createBitCrusherDescription();
    }
    else if (algorithm == "Square Folder")
    {
        description = textLoader.createSquareFolderDescription();
    }
    else if (algorithm == "Downsample")
    {
        description = textLoader.createDownSamplerDescription();
    }
    else
    {
        // Fallback for any algorithms without a specific description function
        description.append(textLoader.getAlgorithmDescription(algorithm), juce::Font(14.0f), textColour);
    }

    description.setColour(textColour);
    attrStringComp.setAttributedString(description);
    viewport.setViewPosition(0, 0);

}

void AdvancedModeDescriptionSection::setTheme(const Theme& currentTheme)
{
    backgroundColour = currentTheme.backgroundColour;
    textColour = currentTheme.textColour;
    highlightColour = currentTheme.highlightColour;
    shadowColour = currentTheme.shadowColour;

    attrStringComp.setTheme(currentTheme);
    descriptionLabel.setColour(juce::Label::textColourId, textColour);

    //descriptionBox.setColour(juce::TextEditor::backgroundColourId, backgroundColour);
    //descriptionBox.setColour(juce::TextEditor::textColourId, textColour);
    //descriptionBox.setColour(juce::TextEditor::outlineColourId, highlightColour);
}
