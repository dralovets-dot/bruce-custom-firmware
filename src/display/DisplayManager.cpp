#include "DisplayManager.h"
#include <Arduino.h>

// Конструктор
DisplayManager::DisplayManager() {
    // Инициализация
}

// Инициализация дисплея
void DisplayManager::init() {
    // Заглушка
}

// Установка шрифта
void DisplayManager::setFont(FontStyle style) {
    // Заглушка - используем параметр чтобы избежать warning
    (void)style;
}

// Отрисовка статуса брутфорса
void DisplayManager::drawBruteforceStatus(uint32_t currentKey, uint32_t foundKey,
                                         uint32_t attempts, float progress, const char* state) {
    // Заглушка
    (void)currentKey; (void)foundKey; (void)attempts; 
    (void)progress; (void)state;
}

// Установка темы
void DisplayManager::setTheme(const DisplayTheme& theme) {
    // Заглушка
    (void)theme;
}
