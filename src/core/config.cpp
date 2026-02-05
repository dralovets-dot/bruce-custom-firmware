#include "config.h"
#include <ArduinoJson.h>

void BruceConfig::fromJson(const DynamicJsonDocument& doc) {
    if (doc.isNull()) return;
    
    JsonObject root;
    if (doc.is<JsonObject>()) {
        root = doc.as<JsonObject>();
    } else {
        return;
    }
    
    if (root.isNull()) return;
    
    // Безопасная обработка
    if (root.containsKey("theme")) {
        if (root["theme"].is<JsonObject>()) {
            JsonObject theme = root["theme"].as<JsonObject>();
        }
    }
}

DynamicJsonDocument BruceConfig::toJson() const {
    DynamicJsonDocument doc(1024);
    JsonObject root = doc.to<JsonObject>();
    root["version"] = "1.0";
    return doc;
}

DynamicJsonDocument loadConfig() {
    DynamicJsonDocument configDoc(1024);
    const char* configJson = "{}";
    
    DeserializationError error = deserializeJson(configDoc, configJson);
    if (error) {
        return configDoc;
    }
    
    BruceConfig config;
    config.fromJson(configDoc);
    return configDoc;
}
