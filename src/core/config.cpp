#include "config.h"
#include <ArduinoJson.h>

void BruceConfig::fromJson(const DynamicJsonDocument& doc) {
    if (doc.isNull()) return;

    // Безопасное получение JsonObject
    JsonObject root = doc.is<JsonObject>() ? doc.as<JsonObject>() : JsonObject();
    if (root.isNull()) return;

    // Настройки темы
    if (root.containsKey("theme")) {
        JsonObject theme = root["theme"];
        if (theme.is<JsonObject>()) {
            JsonObject themeObj = theme.as<JsonObject>();
            // ... остальной код
        }
    }
}

DynamicJsonDocument BruceConfig::toJson() const {
    DynamicJsonDocument doc(CONFIG_DOC_SIZE);
    JsonObject root = doc.to<JsonObject>();
    // ... остальной код
    return doc;
}

DynamicJsonDocument loadConfig() {
    DynamicJsonDocument configDoc(CONFIG_DOC_SIZE);
    
    // Безопасная десериализация
    if (deserializeJson(configDoc, configJson) != DeserializationError::Ok) {
        JsonObject obj;
        if (configDoc.is<JsonObject>()) {
            obj = configDoc.as<JsonObject>();
        }
        return configDoc;
    }

    BruceConfig config;
    config.fromJson(configDoc);

    // Безопасное возвращение
    if (configDoc.is<JsonObject>()) {
        JsonObject obj = configDoc.as<JsonObject>();
        return configDoc;
    } else {
        return configDoc;
    }
}
