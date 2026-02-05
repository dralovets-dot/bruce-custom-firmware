#include "display/ThemeManager.h"

ThemeManager::ThemeManager() {
    // Конструктор
}

DisplayManager::DisplayTheme ThemeManager::getDarkTheme() {
    DisplayManager::DisplayTheme theme;
    theme.backgroundColor = 0x000000;
    theme.textColor = 0xFFFFFF;
    theme.highlightColor = 0x00FF00;
    theme.buttonColor = 0x333333;
    theme.borderColor = 0x666666;
    theme.brightness = 255;
    theme.inverted = false;
    return theme;
}

DisplayManager::DisplayTheme ThemeManager::getLightTheme() {
    DisplayManager::DisplayTheme theme;
    theme.backgroundColor = 0xFFFFFF;
    theme.textColor = 0x000000;
    theme.highlightColor = 0x0000FF;
    theme.buttonColor = 0xDDDDDD;
    theme.borderColor = 0x999999;
    theme.brightness = 255;
    theme.inverted = false;
    return theme;
}
