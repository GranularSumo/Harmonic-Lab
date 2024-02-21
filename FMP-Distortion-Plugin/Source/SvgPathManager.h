/*
  ==============================================================================

    SvgPathManager.h
    Created: 15 Feb 2024 3:54:58pm
    Author:  zeush

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Theme.h"

class SvgPathManager : public juce::Component
{
public:
    enum PathType {
        sine, 
        softclip, 
        brokenSoftclip, 
        hardclip,
        wavefold, 
        feedbackWavefold,
        asymetricSoftclip,
        biasShape,
        biasFold,
        foldCrush,
        dualPathBitFold,
        bitcrush,
        squarefold,
        downsample};

    void setCurrentPath(PathType newPath);
    SvgPathManager::PathType getPath(int index);

    void setTheme(const Theme& currentTheme);

protected:
    void paint(juce::Graphics& g) override;



private:
    void drawPath(juce::Graphics& g, const unsigned char* pathData, size_t dataSize);

    void drawSine(juce::Graphics& g);
    void drawSoftclip(juce::Graphics& g);
    void drawBrokenSoftclip(juce::Graphics& g);
    void drawHardclip(juce::Graphics& g);
    void drawWavefold(juce::Graphics& g);
    void drawFeedbackWavefold(juce::Graphics& g);

    void drawAsymetricSoftclip(juce::Graphics& g);
    void drawBiasShape(juce::Graphics& g);
    void drawBiasFold(juce::Graphics& g);
    void drawFoldcrush(juce::Graphics& g);
    void drawDualPathBitfold(juce::Graphics& g);

    void drawBitcrush(juce::Graphics& g);
    void drawSquarefold(juce::Graphics& g);
    void drawDownsample(juce::Graphics& g);

    PathType currentPath;

    juce::Colour backgroundColour;
    juce::Colour shadowColour;
    juce::Colour highlightColour;
    juce::Colour pathColour;

    
};
