/*
  ==============================================================================

    TutorialSection.h
    Created: 23 Feb 2024 6:00:10pm
    Author:  zeush

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Theme.h"
#include "AdvancedModeUI.h"
#include "AttrStringComponent.h"

//==============================================================================
/*
*/
class TutorialSection  : public juce::Component
{
public:
    struct TutorialPage {
        juce::AttributedString text;
        juce::String highlightedComponent;
    };
    struct TutorialSet {
        std::vector<TutorialPage> pages;
        int currentPageIndex = 0;
    };

    TutorialSection();
    ~TutorialSection() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setTheme(const Theme& currentTheme);

    void setAdvancedModeUI(AdvancedModeUI* advancedModeUI);

    void buttonClickedAction(const juce::String& highlightComponent);
    void closeOverlay();

    //void setTutorialText();
    void initializeTutorials();
    void loadTutorialPage(const juce::String& tutorialSetId, int pageIndex);

    juce::AttributedString generateDistortionPage1();
    juce::AttributedString generateDistortionPage2();
    juce::AttributedString generateDistortionPage3();

    juce::AttributedString generatePreFilterPage1();
    juce::AttributedString generatePreFilterPage2();
    juce::AttributedString generatePreFilterPage3();

    juce::AttributedString generatePostFilterPage1();
    juce::AttributedString generatePostFilterPage2();
    juce::AttributedString generatePostFilterPage3();

    juce::AttributedString generateUtilitiesPage1();
    juce::AttributedString generateUtilitiesPage2();

private:

    std::map<juce::String, TutorialSet> tutorialSets;
    juce::String currentTutorialSetId;

    AdvancedModeUI* ui = nullptr;

    juce::Label title;

    juce::TextButton distortionButton;
    juce::TextButton preFilterButton;
    juce::TextButton postFilterButton;
    juce::TextButton utilitiesButton;

    juce::TextButton previousButton;
    juce::TextButton nextButton;
    juce::TextButton closeButton;

    juce::TextEditor tutorialBox;
    juce::Viewport viewport;
    AttrStringComponent attrStringComp;

    juce::Colour backgroundColour;
    juce::Colour textColour;
    juce::Colour highlightColour;
    juce::Colour shadowColour;

    bool textEditorIsVisible = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TutorialSection)
};
