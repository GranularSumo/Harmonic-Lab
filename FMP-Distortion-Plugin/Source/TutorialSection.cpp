/*
  ==============================================================================

    TutorialSection.cpp
    Created: 23 Feb 2024 6:00:10pm
    Author:  zeush

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TutorialSection.h"

//==============================================================================
TutorialSection::TutorialSection()
{

    //addAndMakeVisible(tutorialBox);
    //tutorialBox.setMultiLine(true);
    //tutorialBox.setReadOnly(true);
    //tutorialBox.setScrollbarsShown(true);
    //tutorialBox.setCaretVisible(false);
    //tutorialBox.setVisible(false);



    addAndMakeVisible(viewport);
    viewport.setViewedComponent(&attrStringComp, false);
    viewport.setVisible(false);
    viewport.setScrollBarsShown(true, false);

    addAndMakeVisible(distortionButton);
    distortionButton.setButtonText("Distortion");
    distortionButton.onClick = [this] 
        {
            viewport.setVisible(true);
            loadTutorialPage("distortion", 0);
            ui->showOverlay(true);
        };

    addAndMakeVisible(preFilterButton);
    preFilterButton.setButtonText("Pre Filter");
    preFilterButton.onClick = [this] 
        { 
            viewport.setVisible(true);
            loadTutorialPage("preFilter", 0);
            ui->showOverlay(true);
        };

    addAndMakeVisible(postFilterButton);
    postFilterButton.setButtonText("Post Filter");
    postFilterButton.onClick = [this] 
        { 
            viewport.setVisible(true);
            loadTutorialPage("postFilter", 0);
            ui->showOverlay(true);
        };

    addAndMakeVisible(utilitiesButton);
    utilitiesButton.setButtonText("Utilities");
    utilitiesButton.onClick = [this]
        { 
            viewport.setVisible(true);
            loadTutorialPage("utilities", 0);
            ui->showOverlay(true);
        };


    addAndMakeVisible(previousButton);
    previousButton.setButtonText("Previous");
    previousButton.setVisible(false);
    previousButton.onClick = [this] {
        auto& tutorialSet = tutorialSets[currentTutorialSetId];
        loadTutorialPage(currentTutorialSetId, tutorialSet.currentPageIndex - 1);
        };

    addAndMakeVisible(nextButton);
    nextButton.setButtonText("Next");
    nextButton.setVisible(false);
    nextButton.onClick = [this] {
        auto& tutorialSet = tutorialSets[currentTutorialSetId];
        loadTutorialPage(currentTutorialSetId, tutorialSet.currentPageIndex + 1);
        };

    addAndMakeVisible(closeButton);
    closeButton.setButtonText("Close");
    closeButton.setVisible(false);
    closeButton.onClick = [this] {
        this->closeOverlay();
        };

    addAndMakeVisible(title);
    title.setText("Tutorials", juce::NotificationType::dontSendNotification);
    title.setJustificationType(juce::Justification::centred);
    juce::Font font(20.0f, juce::Font::bold);
    title.setFont(font);

}

TutorialSection::~TutorialSection()
{
}

void TutorialSection::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    g.fillAll(backgroundColour.brighter(0.1f));

    g.setColour(shadowColour);
    g.drawLine(bounds.getX(), bounds.getY(), bounds.getRight(), bounds.getY());
    g.drawLine(bounds.getX(), bounds.getBottom(), bounds.getRight(), bounds.getBottom());

    g.setColour(highlightColour.brighter(0.05f));
    g.drawLine(bounds.getX(), bounds.getY() + 1, bounds.getRight(), bounds.getY() + 1);
    g.drawLine(bounds.getX(), bounds.getBottom() - 1, bounds.getRight(), bounds.getBottom() - 1);



    if (textEditorIsVisible)
    {
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

}


void TutorialSection::resized()
{
    auto area = getLocalBounds().reduced(10);
    auto buttonHeight = 30;

    

    title.setBounds(area.removeFromTop(30));
    area.removeFromTop(20);



    // Position other tutorial buttons similarly

    // Place the close button at the bottom or another appropriate location
    closeButton.setBounds(area.removeFromBottom(buttonHeight));

    area.removeFromBottom(10);
    auto navigationButtonArea = area.removeFromBottom(buttonHeight);
    previousButton.setBounds(navigationButtonArea.removeFromLeft(navigationButtonArea.getWidth() * 0.5f).reduced(15, 0));
    nextButton.setBounds(navigationButtonArea.removeFromLeft(navigationButtonArea.getWidth()).reduced(15, 0));

    if (textEditorIsVisible)
    {
        juce::Rectangle<int> viewportArea(area.getX(), area.getY() - 10, area.getWidth(), area.getHeight());
        viewport.setBounds(viewportArea);

    }
    else
    {
        distortionButton.setBounds(area.removeFromTop(buttonHeight));
        area.removeFromTop(10);
        preFilterButton.setBounds(area.removeFromTop(buttonHeight));
        area.removeFromTop(10);
        postFilterButton.setBounds(area.removeFromTop(buttonHeight));
        area.removeFromTop(10);
        utilitiesButton.setBounds(area.removeFromTop(buttonHeight));
        area.removeFromTop(10);

    }

}

void TutorialSection::setTheme(const Theme& currentTheme)
{
	backgroundColour = currentTheme.backgroundColour;
	textColour = currentTheme.textColour;
	highlightColour = currentTheme.highlightColour;
	shadowColour = currentTheme.shadowColour;

    distortionButton.setColour(juce::TextButton::buttonColourId, backgroundColour);
    preFilterButton.setColour(juce::TextButton::buttonColourId, backgroundColour);
    postFilterButton.setColour(juce::TextButton::buttonColourId, backgroundColour);
    utilitiesButton.setColour(juce::TextButton::buttonColourId, backgroundColour);
    previousButton.setColour(juce::TextButton::buttonColourId, backgroundColour);
    nextButton.setColour(juce::TextButton::buttonColourId, backgroundColour);
    closeButton.setColour(juce::TextButton::buttonColourId, backgroundColour);

    attrStringComp.setTheme(currentTheme);

    repaint();

}

void TutorialSection::setAdvancedModeUI(AdvancedModeUI* advancedModeUI)
{
    this->ui = advancedModeUI;
}


void TutorialSection::buttonClickedAction(const juce::String& highlightComponent)
{
    if (ui != nullptr)
    {
        ui->setHighlightedArea(highlightComponent);
    }

    // Hide tutorial buttons and show the "Close" button
    for (auto* btn : { &distortionButton, &preFilterButton, &postFilterButton, &utilitiesButton }) {
        btn->setVisible(false);
    }

    // Show the close button
    previousButton.setVisible(true);
    nextButton.setVisible(true);
    closeButton.setVisible(true);
    tutorialBox.setVisible(true);
    textEditorIsVisible = true;
    repaint();

    // Optionally, resize or re-layout your component if necessary
    resized();
}

void TutorialSection::closeOverlay()
{
    if (ui != nullptr) {
        ui->showOverlay(false);
    }

    loadTutorialPage(currentTutorialSetId, 0);

    // Update visibility states for buttons and the viewport
    for (auto* btn : { &distortionButton, &preFilterButton, &postFilterButton, &utilitiesButton }) {
        btn->setVisible(true);
    }
    previousButton.setVisible(false);
    nextButton.setVisible(false);
    closeButton.setVisible(false);
    tutorialBox.setVisible(false);
    viewport.setVisible(false);

    textEditorIsVisible = false;
    repaint();
}


void TutorialSection::initializeTutorials()
{
    TutorialSet distortionTutorial;
    distortionTutorial.pages.push_back({ generateDistortionPage1(), "Algorithm Selector" });
    distortionTutorial.pages.push_back({ generateDistortionPage2(), "Algorithm Display" });
    distortionTutorial.pages.push_back({ generateDistortionPage3(), "Drive" });
    tutorialSets["distortion"] = distortionTutorial;

    TutorialSet preFilterTutorial;
    preFilterTutorial.pages.push_back({generatePreFilterPage1(), "Pre Filter Bypass"});
    preFilterTutorial.pages.push_back({ generatePreFilterPage2(), "Pre Filter Selector" });
    preFilterTutorial.pages.push_back({ generatePreFilterPage3(), "Pre Filter Controls" });
    tutorialSets["preFilter"] = preFilterTutorial;

    TutorialSet postFilterTutorial;
    postFilterTutorial.pages.push_back({ generatePostFilterPage1(), "Post Filter Bypass" });
    postFilterTutorial.pages.push_back({ generatePostFilterPage2(), "Post Filter Selector" });
    postFilterTutorial.pages.push_back({ generatePostFilterPage3(), "Post Filter Controls" });
    tutorialSets["postFilter"] = postFilterTutorial;

    TutorialSet Utilities;
    Utilities.pages.push_back({ generateUtilitiesPage1(), "Mix" });
    Utilities.pages.push_back({ generateUtilitiesPage2(), "Output Gain" });
    tutorialSets["utilities"] = Utilities;
}

void TutorialSection::loadTutorialPage(const juce::String& tutorialSetId, int pageIndex)
{
    auto& tutorialSet = tutorialSets[tutorialSetId];
    if (pageIndex >= 0 && pageIndex < tutorialSet.pages.size())
    {
        const auto& page = tutorialSet.pages[pageIndex];
        attrStringComp.setAttributedString(page.text);
        attrStringComp.setSize(270, 600);
        //if (ui) ui->setHighlightedArea(page.highlightedComponent);
        buttonClickedAction(page.highlightedComponent);

        currentTutorialSetId = tutorialSetId;
        tutorialSet.currentPageIndex = pageIndex;

        previousButton.setVisible(pageIndex > 0);
        nextButton.setVisible(pageIndex < tutorialSet.pages.size() - 1);

        resized();
    }
}

juce::AttributedString TutorialSection::generateDistortionPage1()
{
    auto plainTextSize = 14.0f;
    auto titleTextSize = 24.0f;
    auto header1TextSize = 18.0f;
    auto header2TextSize = 16.0f;

    juce::AttributedString attrStr;
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize));
    attrStr.append("Algorithm Selection\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize));
    attrStr.append("You can use the algorithm selector dropdown menu to chose from a selection of different distortion algorithms.\n", juce::Font(plainTextSize));
    attrStr.append("Notice that the dropdown menu is separated into three sections: \n", juce::Font(plainTextSize));
    attrStr.append("____________________________________________\n", juce::Font(plainTextSize));
    attrStr.append("Symmetrical:\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("Symmetrical distortion treats both the 'up' and 'down' parts of a sound wave equally. This creates a rich, harmonious distortion that's often warm and full.\n", juce::Font(plainTextSize), juce::Colours::black);
    attrStr.append("____________________________________________\n", juce::Font(plainTextSize));
    attrStr.append("Asymmetrical:\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("Asymmetrical distortion treats the 'up' and 'down' parts of a sound wave separately. This results in the addition of harmonics that weren't present when using a symmetric algorithm, often but not always perceived as more aggressive sound.\n", juce::Font(plainTextSize), juce::Colours::black);
    attrStr.append("____________________________________________\n", juce::Font(plainTextSize));
    attrStr.append("Quantization:\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("Quantization based distortion is a bit different. Imagine taking a picture with lots of detail (your sound) and reducing the quality so some of that detail gets simplified. This process can introduce a kind of digital distortion that adds a unique texture or 'grit' to the sound. It's akin to pixelating an image, where the smooth contours are replaced with blocky edges, creating a starkly different feel..\n", juce::Font(plainTextSize), juce::Colours::black);

    attrStr.setColour(textColour);
    return attrStr;
}

juce::AttributedString TutorialSection::generateDistortionPage2()
{
    auto plainTextSize = 14.0f;
    auto titleTextSize = 24.0f;
    auto header1TextSize = 18.0f;
    auto header2TextSize = 16.0f;

    juce::AttributedString attrStr;
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize));
    attrStr.append("Algorithm Display\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize));
    attrStr.append("The image in the box on the right will update when you change the algorithm to give you a visual representation of what the signal might look like if you pass a sine wave through the plugin.\n", juce::Font(plainTextSize));
    attrStr.append("Test\n", juce::Font(plainTextSize));

    attrStr.setColour(textColour);
    return attrStr;
}

juce::AttributedString TutorialSection::generateDistortionPage3()
{
    auto plainTextSize = 14.0f;
    auto titleTextSize = 24.0f;
    auto header1TextSize = 18.0f;
    auto header2TextSize = 16.0f;

    juce::AttributedString attrStr;
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize));
    attrStr.append("Drive\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize));
    attrStr.append("Distortion Slider:\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("The large Distortion slider is used to decide how much you want to push the signal into the selected distortion algorithm. depending on the algorithm selected this actually does different things. for example most of the symmetric and asymmetric algorithms (but not all) work by applying 'drive' which usually means increasing the gain of the signal before the algorithm is applied (although other things could be happening at the same time.) On the other hand some of the quantisation algorithms work in a different way and increasing the distortion slider may actually be reducign the bitrate of the signal or downsampling instead.\n", juce::Font(plainTextSize));
    attrStr.append("\n____________________________________________\n", juce::Font(plainTextSize));
    attrStr.append("Input Slider:\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("The Input slider just increases or decreases the input gain of the signal before it is affected by anything else in the plugin. Because some of the algorithms are based on adding gain to the signal you can actually use the input gain slider to boost the drive even further if you want to resulting in an output signal that is even more distorted. You can also use this to dial back the distortion if the signal is coming in a bit too loud and you want the distortion to be a bit more subtle.\n", juce::Font(plainTextSize));

    attrStr.setColour(textColour);
    return attrStr;
}

juce::AttributedString TutorialSection::generatePreFilterPage1()
{
    auto plainTextSize = 14.0f;
    auto titleTextSize = 24.0f;
    auto header1TextSize = 18.0f;
    auto header2TextSize = 16.0f;

    juce::AttributedString attrStr;
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize));
    attrStr.append("Pre Filter Bypass\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize));
    attrStr.append("You can enable or disable the pre filter with this checkbox.\n", juce::Font(plainTextSize));
    //attrStr.append("Test\n", juce::Font(plainTextSize));

    attrStr.setColour(textColour);
    return attrStr;
}

juce::AttributedString TutorialSection::generatePreFilterPage2()
{
    auto plainTextSize = 14.0f;
    auto titleTextSize = 24.0f;
    auto header1TextSize = 18.0f;
    auto header2TextSize = 16.0f;

    juce::AttributedString attrStr;
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize));
    attrStr.append("Pre Filter Type Selector\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize));
    attrStr.append("The pre filter type selector has three options to choose from:\n", juce::Font(plainTextSize));
    attrStr.append("____________________________________________\n", juce::Font(plainTextSize));
    attrStr.append("Lowpass:\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("you can use the lowpass filter to block out the higher harmonics before the distortion is applied. This can result in a more blown out sound depending on the input signal.\n", juce::Font(plainTextSize));
    attrStr.append("____________________________________________\n", juce::Font(plainTextSize));
    attrStr.append("Highpass:\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("you can use the highpass filter to block out the lower harmonics before the distortion is applied. This can result in a more hissy or nasaly sound depending on the input signal.\n", juce::Font(plainTextSize));
    attrStr.append("____________________________________________\n", juce::Font(plainTextSize));
    attrStr.append("Bandpass:\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("you can use the bandpass filter to only let through a narrow band of the signal into the distortion effect. you can create quite a lot of different kinds of effects with a bandpass before the distortion, for example if you focus the filter around the mids and only distort the signal slightly you can create a very basic effect that sounds a bit like a guitar cabinet or something similar to a tubescreamer pedal.\n", juce::Font(plainTextSize));
    attrStr.append("____________________________________________\n", juce::Font(plainTextSize));
    attrStr.append("you should also try experimenting with the dry/wet mixer when you are using the pre filter as this can create more complex sounds by introducing the new harmonics that you are creating with the distortion into the original unmodified signal.\n", juce::Font(plainTextSize));
    attrStr.setColour(textColour);
    return attrStr;
}

juce::AttributedString TutorialSection::generatePreFilterPage3()
{
    auto plainTextSize = 14.0f;
    auto titleTextSize = 24.0f;
    auto header1TextSize = 18.0f;
    auto header2TextSize = 16.0f;

    juce::AttributedString attrStr;
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize));
    attrStr.append("Pre Filter Controls\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize));
    attrStr.append("Cutoff Slider:\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("The cutoff slider determines where in the frequency range the filter starts to filter out the incoming signal.\n", juce::Font(plainTextSize));
    attrStr.append("\n____________________________________________\n", juce::Font(plainTextSize));
    attrStr.append("Res Slider:\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("The res slider lets you set the resonance of the filter. In very simple terms the adds a boost to the freqency that the cutoff is set to. The higher the res slider is set the more of a boost is applied. These filters are designed to be able to give a huge resonance boost and you can use this bring out extreme harmonics in the distorted signal to the point where it almost sounds like feedback from a microphone.\n", juce::Font(plainTextSize));
    attrStr.append("\n____________________________________________\n", juce::Font(plainTextSize));

    attrStr.setColour(textColour);
    return attrStr;
}

juce::AttributedString TutorialSection::generatePostFilterPage1()
{
    auto plainTextSize = 14.0f;
    auto titleTextSize = 24.0f;
    auto header1TextSize = 18.0f;
    auto header2TextSize = 16.0f;

    juce::AttributedString attrStr;
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize));
    attrStr.append("Post Filter Bypass\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize));
    attrStr.append("You can enable or disable the post filter with this checkbox.\n", juce::Font(plainTextSize));

    attrStr.setColour(textColour);
    return attrStr;
}

juce::AttributedString TutorialSection::generatePostFilterPage2()
{
    auto plainTextSize = 14.0f;
    auto titleTextSize = 24.0f;
    auto header1TextSize = 18.0f;
    auto header2TextSize = 16.0f;

    juce::AttributedString attrStr;
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize), juce::Colours::black);
    attrStr.append("Post Filter Type Selector\n", juce::Font(titleTextSize, juce::Font::bold), juce::Colours::black);
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize), juce::Colours::black);
    attrStr.append("The post filter type selector has three options to choose from:\n", juce::Font(plainTextSize));
    attrStr.append("____________________________________________\n", juce::Font(plainTextSize));
    attrStr.append("Lowpass:\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("you can use the lowpass filter cut out some of the highend of the output signal, this will make the distortion effect a bit smoother sounding and less harsh.\n", juce::Font(plainTextSize));
    attrStr.append("____________________________________________\n", juce::Font(plainTextSize));
    attrStr.append("Highpass:\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("you can use the highpass filter cut out some of the lowend of the output signal, this will make the distortion effect a bit harsher, more fizzy sounding, and remove some of the body of the sound. \n", juce::Font(plainTextSize));
    attrStr.append("____________________________________________\n", juce::Font(plainTextSize));
    attrStr.append("Bandpass:\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("you can use the bandpass filter to only let through a narrow band of the signal into the distortion effect. Using this filter type on the post filter will probably result in a more lowfi type sound.\n", juce::Font(plainTextSize));
    attrStr.setColour(textColour);
    return attrStr;
}

juce::AttributedString TutorialSection::generatePostFilterPage3()
{
    auto plainTextSize = 14.0f;
    auto titleTextSize = 24.0f;
    auto header1TextSize = 18.0f;
    auto header2TextSize = 16.0f;

    juce::AttributedString attrStr;
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize), juce::Colours::black);
    attrStr.append("Post Filter Controls\n", juce::Font(titleTextSize, juce::Font::bold), juce::Colours::black);
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize), juce::Colours::black);
    attrStr.append("Cutoff Slider:\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("The cutoff slider determines where in the frequency range the filter starts to filter out the signal.\n", juce::Font(plainTextSize));
    attrStr.append("\n____________________________________________\n", juce::Font(plainTextSize));
    attrStr.append("Res Slider:\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("The res slider lets you set the resonance of the filter. In very simple terms the adds a boost to the freqency that the cutoff is set to. The higher the res slider is set the more of a boost is applied. These filters are designed to be able to give a huge resonance boost and you can use this bring out extreme harmonics in the distorted signal to the point where it almost sounds like feedback from a microphone.\n", juce::Font(plainTextSize));
    attrStr.append("\n____________________________________________\n", juce::Font(plainTextSize));

    attrStr.setColour(textColour);
    return attrStr;
}

juce::AttributedString TutorialSection::generateUtilitiesPage1()
{
    auto plainTextSize = 14.0f;
    auto titleTextSize = 24.0f;
    auto header1TextSize = 18.0f;
    auto header2TextSize = 16.0f;

    juce::AttributedString attrStr;
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize), juce::Colours::black);
    attrStr.append("Mix\n", juce::Font(titleTextSize, juce::Font::bold), juce::Colours::black);
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize), juce::Colours::black);
    attrStr.append("The mix slider is used to set how much of the distorted signal is mixed back into the original uneffected signal. The higher the slider is set the more of the distorted signal is being mixed. When the slider is at 0 you are only hearing the original signal, and when the slider is at 100 you are only hearing the distorted signal.\n", juce::Font(plainTextSize), juce::Colours::black);

    attrStr.setColour(textColour);
    return attrStr;
}

juce::AttributedString TutorialSection::generateUtilitiesPage2()
{
    auto plainTextSize = 14.0f;
    auto titleTextSize = 24.0f;
    auto header1TextSize = 18.0f;
    auto header2TextSize = 16.0f;

    juce::AttributedString attrStr;
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize), juce::Colours::black);
    attrStr.append("Output Gain\n", juce::Font(titleTextSize, juce::Font::bold), juce::Colours::black);
    attrStr.append("----------------------------------------------------------\n", juce::Font(plainTextSize), juce::Colours::black);
    attrStr.append("The ouptut gain slider increases or decreases the gain as it leaves the plugin. the main use for this would be to reduce the volume of the output signal as heavily distorting and filtering things can make the signal much louder that it would have originally been.\n", juce::Font(plainTextSize), juce::Colours::black);

    attrStr.setColour(textColour);
    return attrStr;
}





