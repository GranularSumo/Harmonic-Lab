/*
  ==============================================================================

    ThemeManager.h
    Created: 20 Feb 2024 10:38:00pm
    Author:  zeush

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Theme.h"

class ThemeManager {
public:
    enum ThemeId { Default, Vista, Candy };

    ThemeManager();

    void switchTheme(ThemeId newTheme);
    const Theme& getCurrentTheme();
    int getCurrentThemeId();
private:
    std::map<ThemeId, Theme> themes;
    ThemeId currentThemeId;
};