#include "config.h"
#include <ArduinoJson.h>

// Минимальные безопасные реализации

void BruceConfig::fromJson(const DynamicJsonDocument& doc) {
    if (doc.isNull()) return;
    
    JsonObject root;
    if (doc.is<JsonObject>()) {
        root = doc.as<JsonObject>();
    }
    
    if (root.isNull()) return;
    
    // Базовая обработка (можно расширить позже)
    if (root.containsKey("theme")) {
        // Обработка темы
    }
}

DynamicJsonDocument BruceConfig::toJson() const {
    DynamicJsonDocument doc(1024);
    JsonObject root = doc.to<JsonObject>();
    // Базовая сериализация
    return doc;
}

DynamicJsonDocument loadConfig() {
    DynamicJsonDocument configDoc(1024);
    
    // Минимальная безопасная реализация
    JsonObject obj;
    if (configDoc.is<JsonObject>()) {
        obj = configDoc.as<JsonObject>();
    }
    
    BruceConfig config;
    config.fromJson(configDoc);
    
    return configDoc;
}
