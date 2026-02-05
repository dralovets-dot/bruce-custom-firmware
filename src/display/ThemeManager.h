#ifndef THEME_MANAGER_H
#define THEME_MANAGER_H

#include <Arduino.h>
#include <vector>
#include "DisplayManager.h"

class ThemeManager {
public:
    struct SavedTheme {
        String name;
        DisplayManager::DisplayTheme theme;
        bool isDefault;
    };
    
    ThemeManager();
    
    void loadThemes();
    void saveThemes();
    
    void setCurrentTheme(const String& name);
    void setCurrentTheme(int index);
    DisplayManager::DisplayTheme getCurrentTheme() const;
    
    void addTheme(const String& name, const DisplayManager::DisplayTheme& theme);
    void removeTheme(const String& name);
    void updateTheme(const String& name, const DisplayManager::DisplayTheme& theme);
    
    std::vector<SavedTheme> getAvailableThemes() const { return themes; }
    String getCurrentThemeName() const { return currentThemeName; }
    
    // Предустановленные темы
    static DisplayManager::DisplayTheme getDarkTheme();
    static DisplayManager::DisplayTheme getLightTheme();
    static DisplayManager::DisplayTheme getHighContrastTheme();
    static DisplayManager::DisplayTheme getSolarizedTheme();
    static DisplayManager::DisplayTheme getCyberpunkTheme();
    
private:
    std::vector<SavedTheme> themes;
    String currentThemeName = "Dark";
    
    void createDefaultThemes();
    DisplayManager::DisplayTheme loadThemeFromJSON(const String& json);
    String saveThemeToJSON(const DisplayManager::DisplayTheme& theme);
};

#endif // THEME_MANAGER_H
