#include "display/ThemeManager.h"

// Конструктор
ThemeManager::ThemeManager() {
    // Инициализация
}

// Получение тёмной темы
DisplayManager::DisplayTheme ThemeManager::getDarkTheme() {
    DisplayManager::DisplayTheme theme;
    theme.backgroundColor = 0x000000;    // Чёрный
    theme.textColor = 0xFFFFFF;         // Белый
    theme.highlightColor = 0x00FF00;    // Зелёный
    theme.buttonColor = 0x333333;       // Тёмно-серый
    theme.borderColor = 0x666666;       // Серый
    theme.brightness = 255;
    theme.inverted = false;
    return theme;
}

// Получение светлой темы (если нужен)
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

// Получение пользовательской темы (заглушка)
DisplayManager::DisplayTheme ThemeManager::getCustomTheme(int id) {
    (void)id;
    return getDarkTheme(); // По умолчанию
}
