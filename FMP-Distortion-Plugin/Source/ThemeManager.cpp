/*
  ==============================================================================

    ThemeManager.cpp
    Created: 20 Feb 2024 10:38:00pm
    Author:  zeush

  ==============================================================================
*/

#include "ThemeManager.h"

ThemeManager::ThemeManager()
{

    /*
    * ----Theme Layout----
    * 
        Colour - background colour
        Colour - shadow colour
        Colour - highlight colour
        Colour - drive slider fill
        Colour - filter slider fill
        Colour - mix slider fill
        Colour - gain slider fill
        Colour - slider background
        Colour - text colour
        String - theme type
    
    */

    themes[Default] = Theme(juce::Colour::fromString("#ff253353"), 
                            juce::Colour::fromString("#ff222A3E"), 
                            juce::Colour::fromString("#ff47526D"), 
                            juce::Colour::fromString("#ffDC603C"), 
                            juce::Colour::fromString("#ff8371C3"), 
                            juce::Colour::fromString("#ffBF4467"), 
                            juce::Colour::fromString("#ffB1C371"), 
                            juce::Colour::fromString("#ff1A2039"),
                            juce::Colour::fromString("#ffEEEEEE"),
                            juce::String("Dark-Mode"));

    themes[DarkMode] = Theme(   juce::Colour::fromString("#ff252525"),
                            juce::Colour::fromString("#ff1F1F1F"),
                            juce::Colour::fromString("#ff3A3A3A"),
                            juce::Colour::fromString("#ffDC603C"),
                            juce::Colour::fromString("#ff8371C3"),
                            juce::Colour::fromString("#ffBF4467"),
                            juce::Colour::fromString("#ffB1C371"),
                            juce::Colour::fromString("#ff171717"),
                            juce::Colour::fromString("#ffEEEEEE"),
                            juce::String("Dark-Mode"));
    

    currentThemeId = Default;
}

void ThemeManager::switchTheme(ThemeId newTheme)
{
    if (themes.find(newTheme) != themes.end())
    {
        currentThemeId = newTheme;
    }
    else
    {
        currentThemeId = Default;
        //DBG("Theme ID not found, reverting to Default theme.");
    }
}

const Theme& ThemeManager::getCurrentTheme()
{
    return themes.at(currentThemeId);
}
