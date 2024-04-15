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
    auto currentThemeIdParameter = audioProcessor.treestate.getRawParameterValue(parameterInfo::themeId);
    if (currentThemeIdParameter != nullptr)
    {
        // The actual index value is obtained directly since getRawParameterValue returns a pointer to the value
        int currentThemeId = static_cast<int>(*currentThemeIdParameter);

        // Use this index to switch the theme
        themeManager.switchTheme(static_cast<ThemeManager::ThemeId>(currentThemeId));

        // Assuming setTheme takes a Theme object, retrieve the current theme from the manager after switching
        setTheme(themeManager.getCurrentTheme());
    }
    //themeManager.switchTheme(currentThemeId);
    //setTheme(themeManager.getCurrentTheme());

    addAndMakeVisible(uiModeButton);
    addAndMakeVisible(descriptionSection);
    addAndMakeVisible(tutorialSection);
    uiModeButton.setAlwaysOnTop(true);
    uiModeButton.onClick = [this]()
        {
            // Toggle the mode
            basicModeIsSelected = !basicModeIsSelected;
            audioProcessor.treestate.getParameter(parameterInfo::uiModeId)->setValueNotifyingHost(basicModeIsSelected ? 1.0f : 0.0f);

            // Update UI based on the new state
            if (basicModeIsSelected)
            {
                basicModeUI.setVisible(true);
                advancedModeUI.setVisible(false);
                descriptionSection.setVisible(false);
                tutorialSection.setVisible(false);
                uiModeButton.setButtonText("Basic");
                setSize(pluginWidth, basicModeUI.getHeight());
            }
            else
            {
                basicModeUI.setVisible(false);
                advancedModeUI.setVisible(true);
                descriptionSection.setVisible(true);
                tutorialSection.setVisible(true);
                uiModeButton.setButtonText("Advanced");
                setSize(pluginWidth + (advancedModePluginWidthOffset * 2.0f), advancedModeUI.getHeight());
                
            }
        };

    settingsMenu.setThemeChangeListener(this);

    logo.setAlwaysOnTop(true);
    addAndMakeVisible(logo);

    addAndMakeVisible(basicModeUI);
    addAndMakeVisible(advancedModeUI);
    advancedModeUI.setVisible(false);
    
    settingsButton.setButtonText("Settings");
    settingsButton.onClick = [this]()
        {
            if (!settingsMenuIsActiveWindow)
            {
                // Hide both UIs and show settings menu
                basicModeUI.setVisible(false);
                advancedModeUI.setVisible(false);
                descriptionSection.setVisible(false);
                tutorialSection.setVisible(false);
                uiModeButton.setVisible(false);
                addAndMakeVisible(settingsMenu);
                settingsButton.setButtonText("Close");
                settingsMenuIsActiveWindow = true; // Update flag
            }
            else
            {
                // Hide settings menu
                uiModeButton.setVisible(true);
                settingsMenu.setVisible(false);
                settingsButton.setButtonText("Settings");


                // Return to the appropriate UI based on `uiModeSwitcher`
                if (basicModeIsSelected)
                {
                    basicModeUI.setVisible(true);
                    descriptionSection.setVisible(false);
                    tutorialSection.setVisible(false);
                    setSize(basicModeUI.getWidth(), basicModeUI.getHeight());
                }
                else
                {
                    advancedModeUI.setVisible(true);
                    descriptionSection.setVisible(true);
                    tutorialSection.setVisible(true);
                    setSize(pluginWidth + (advancedModePluginWidthOffset * 2.0f), advancedModeUI.getHeight());
                }
                settingsMenuIsActiveWindow = false; // Update flag
            }

        };
    settingsButton.setAlwaysOnTop(true);
    addAndMakeVisible(settingsButton);

    advancedModeUI.getAlgorithmSelector().onChange = [this]()
        {
            descriptionSection.setDescription(advancedModeUI.getCurrentAlgorithm());
            advancedModeUI.setCurrentPath(advancedModeUI.getAlgorithmSelector().getSelectedId());
        };
    descriptionSection.setDescription(advancedModeUI.getCurrentAlgorithm());

    tutorialSection.setAdvancedModeUI(&advancedModeUI);
    tutorialSection.initializeTutorials();


    setSize (basicModeUI.getWidth(), basicModeUI.getHeight());
}

FMPDistortionPluginAudioProcessorEditor::~FMPDistortionPluginAudioProcessorEditor()
{
}

//==============================================================================
void FMPDistortionPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    auto headerBounds = bounds.removeFromTop(pluginHeight * 0.1f);
    auto footerBounds = bounds.removeFromBottom(pluginHeight * 0.075f);

    g.fillAll(backgroundColour);

    // Paint the overall background
    g.fillAll(backgroundColour);

    // Paint header section
    g.setColour(shadowColour);
    g.fillRect(headerBounds);

    // Paint footer section
    g.fillRect(footerBounds);

    // Additional UI drawing code...

    if (!basicModeIsSelected) {
        // In advanced mode, fill the main area excluding header, footer, and potentially other sections

        auto bounds = getLocalBounds();
        auto mainAreaBounds = bounds;

        // Exclude header area
        auto headerHeight = pluginHeight * 0.1f; // adjust according to your UI structure
        mainAreaBounds.removeFromTop(headerHeight);

        // Exclude footer area
        auto footerHeight = pluginHeight * 0.075f; // adjust according to your UI structure
        mainAreaBounds.removeFromBottom(footerHeight);

        // At this point, mainAreaBounds should represent the main UI area without header and footer
        // Now fill this adjusted area with the darker color
        g.setColour(backgroundColour.brighter(0.05f));
        auto leftPanel = mainAreaBounds.removeFromLeft(advancedModePluginWidthOffset);
        auto rightPanel = mainAreaBounds.removeFromRight(advancedModePluginWidthOffset);
        g.fillRect(leftPanel);
        g.fillRect(rightPanel);

        g.setColour(shadowColour);
        g.drawLine(leftPanel.getRight() + 1, leftPanel.getY(), leftPanel.getRight() + 1, leftPanel.getBottom());
        g.drawLine(rightPanel.getX() - 1, rightPanel.getY(), rightPanel.getX() - 1, rightPanel.getBottom());
    }




    auto mainAreaHeight = bounds.getHeight();
    auto row1Bounds = bounds.removeFromTop(mainAreaHeight * 0.2f);
    auto row2Bounds = bounds.removeFromTop(mainAreaHeight * 0.25f);
    auto row3Bounds = bounds.removeFromTop(mainAreaHeight * 0.375f);



    // colours the background of the header section
    g.setColour(shadowColour);
    g.fillRect(headerBounds);

    // colours the background of the footer section
    g.fillRect(footerBounds);

    // draws a line to highlight the bottom of the header section
    g.setColour(shadowColour.darker(0.5f));
    g.drawLine(
        headerBounds.getX(),
        headerBounds.getBottom(),
        headerBounds.getRight(),
        headerBounds.getBottom());
    g.drawLine(
        headerBounds.getX(),
        headerBounds.getBottom() + 1,
        headerBounds.getRight(),
        headerBounds.getBottom() + 1);
    g.setColour(highlightColour);
    g.drawLine(
        headerBounds.getX(),
        headerBounds.getBottom() + 2,
        headerBounds.getRight(),
        headerBounds.getBottom() + 2);


    // draws a line to shade the top of the footer section
    g.setColour(shadowColour.darker(0.5f));
    g.drawLine(
        footerBounds.getX(),
        footerBounds.getY() - 3,
        footerBounds.getRight(),
        footerBounds.getY() - 3);
    g.drawLine(
        footerBounds.getX(),
        footerBounds.getY() - 2,
        footerBounds.getRight(),
        footerBounds.getY() - 2);
    g.setColour(highlightColour);
    g.drawLine(
        footerBounds.getX(),
        footerBounds.getY() - 1,
        footerBounds.getRight(),
        footerBounds.getY() - 1);

}

void FMPDistortionPluginAudioProcessorEditor::resized()
{
    auto header = getLocalBounds().removeFromTop(pluginHeight * 0.1f);
    auto footerBounds = getLocalBounds().removeFromBottom(pluginHeight * 0.075f);

    // set bounds for the constant elements.
    if (basicModeIsSelected)
    {
        logo.setBounds(header.removeFromLeft(pluginWidth * 0.2).reduced(10));
        auto modeButtonWidth = header.getWidth() * 0.2f;
        uiModeButton.setBounds(
            getLocalBounds().getCentreX() - (modeButtonWidth * 0.5f),
            footerBounds.getY() + footerBounds.getHeight() * 0.1f,
            modeButtonWidth,
            footerBounds.getHeight() - footerBounds.getHeight() * 0.2f);
        settingsButton.setBounds(header.removeFromRight(header.getWidth() * 0.4f).reduced(100, 20));

        settingsMenu.setBounds(getLocalBounds());
    }
    else
    {
        auto advancedModeBounds = juce::Rectangle<int>(getLocalBounds().getX() + advancedModePluginWidthOffset, getLocalBounds().getY(), pluginWidth, pluginHeight);
        auto header = advancedModeBounds.removeFromTop(pluginHeight * 0.1f);
        auto footerBounds = advancedModeBounds.removeFromBottom(pluginHeight * 0.075f);
        logo.setBounds(header.removeFromLeft(pluginWidth * 0.2).reduced(10));
        auto modeButtonWidth = header.getWidth() * 0.2f;
        uiModeButton.setBounds(
            getLocalBounds().getCentreX() - (modeButtonWidth * 0.5f),
            footerBounds.getY() + footerBounds.getHeight() * 0.1f,
            modeButtonWidth,
            footerBounds.getHeight() - footerBounds.getHeight() * 0.2f);
        settingsButton.setBounds(header.removeFromRight(header.getWidth() * 0.5f).reduced(100, 20));

        settingsMenu.setBounds(advancedModeBounds);

        auto descriptionBounds = juce::Rectangle<int>(getLocalBounds().getX(), header.getBottom(), advancedModePluginWidthOffset, getLocalBounds().getHeight() - (footerBounds.getHeight() + header.getHeight()));
        descriptionSection.setBounds(descriptionBounds.reduced(5.0f, 8.0f));
        auto tutorialBounds = juce::Rectangle<int>(advancedModeBounds.getRight(), header.getBottom(), advancedModePluginWidthOffset, getLocalBounds().getHeight() - (footerBounds.getHeight() + header.getHeight()));
        tutorialSection.setBounds(tutorialBounds.reduced(5.0f, 8.0f));
    }




    //uiSelectorButton.setBounds(header.removeFromLeft(header.getWidth() * 0.5f).reduced(10));


    // set the bounds for the UI container components.

    auto advancedModeBounds = juce::Rectangle<int>(getLocalBounds().getX() + advancedModePluginWidthOffset, getLocalBounds().getY(), pluginWidth, pluginHeight);
    advancedModeUI.setBounds(advancedModeBounds);
    basicModeUI.setBounds(getLocalBounds());

}

void FMPDistortionPluginAudioProcessorEditor::setTheme(const Theme& currentTheme)
{
    backgroundColour = themeManager.getCurrentTheme().backgroundColour;
    shadowColour = themeManager.getCurrentTheme().shadowColour;
    highlightColour = themeManager.getCurrentTheme().highlightColour;
    driveSliderFillColour = themeManager.getCurrentTheme().driveSliderFillColour;
    filterSliderFillColour = themeManager.getCurrentTheme().filterSliderFillColour;
    gainSliderFillColour = themeManager.getCurrentTheme().gainSliderFillColour;
    dryWetMixFillColour = themeManager.getCurrentTheme().mixSliderFillColour;
    sliderBackgroundColour = themeManager.getCurrentTheme().sliderBackgroundColour;
    themeType = themeManager.getCurrentTheme().themeType;


    logo.setTheme(themeManager.getCurrentTheme());
    uiModeButton.setTheme(themeManager.getCurrentTheme());
    basicModeUI.setTheme(themeManager.getCurrentTheme());
    advancedModeUI.setTheme(themeManager.getCurrentTheme());
    settingsMenu.setTheme(themeManager.getCurrentTheme());
    descriptionSection.setTheme(themeManager.getCurrentTheme());
    tutorialSection.setTheme(themeManager.getCurrentTheme());

    settingsButton.setColour(juce::TextButton::buttonColourId, backgroundColour);
    settingsButton.setColour(juce::TextButton::textColourOnId, currentTheme.textColour);


    repaint();
}

int FMPDistortionPluginAudioProcessorEditor::getTheme(int themeId)
{
    return themeManager.getCurrentThemeId();
}

ThemeManager& FMPDistortionPluginAudioProcessorEditor::getThemeManager()
{
    return themeManager;
}

void FMPDistortionPluginAudioProcessorEditor::themeChanged(int newThemeId)
{
    themeManager.switchTheme(static_cast<ThemeManager::ThemeId>(newThemeId));

    setTheme(themeManager.getCurrentTheme());

}



void FMPDistortionPluginAudioProcessorEditor::restoreUiState()
{
    bool uiMode = *audioProcessor.treestate.getRawParameterValue(parameterInfo::uiModeId);
    basicModeIsSelected = uiMode;

    if (basicModeIsSelected)
    {

        basicModeUI.setVisible(true);
        advancedModeUI.setVisible(false);
        uiSelectorButton.setButtonText("Basic");
        setSize(basicModeUI.getWidth(), basicModeUI.getHeight());
    }
    else
    {

        advancedModeUI.setVisible(true);
        basicModeUI.setVisible(false);
        uiSelectorButton.setButtonText("Advanced");
        setSize(pluginWidth + (advancedModePluginWidthOffset * 2.0f), advancedModeUI.getHeight());
    }
    
}

void FMPDistortionPluginAudioProcessorEditor::visibilityChanged()
{
    if (isVisible())
    {
        restoreUiState();
    }
    else
    {
        audioProcessor.treestate.getParameter(parameterInfo::uiModeId)->setValue(basicModeIsSelected);
    }

}








