#include "configPins.h"
#include <ArduinoJson.h>

// Минимальные заглушки для компиляции
void BruceConfigPins::fromJson(const DynamicJsonDocument& doc) {
    (void)doc;
    // Пустая реализация
}

void BruceConfigPins::toJson(JsonObject& root) const {
    (void)root;
    // Пустая реализация
}

void BruceConfigPins::loadFile() {
    // Пустая реализация
}

void BruceConfigPins::saveFile() {
    // Пустая реализация
}
