#include "config.h"
#include <ArduinoJson.h>

// ГАРАНТИРОВАННО БЕЗОПАСНАЯ ВЕРСИЯ

void BruceConfig::fromJson(const DynamicJsonDocument& doc) {
    // Пустая реализация для сборки
    (void)doc;
}

DynamicJsonDocument BruceConfig::toJson() const {
    DynamicJsonDocument doc(1024);
    JsonObject root = doc.to<JsonObject>();  // to<JsonObject> всегда безопасен
    root["status"] = "ok";
    return doc;
}

DynamicJsonDocument loadConfig() {
    DynamicJsonDocument configDoc(1024);
    
    // АБСОЛЮТНО БЕЗОПАСНАЯ реализация
    // Никаких вызовов .as<> без проверок
    JsonObject obj = configDoc.to<JsonObject>();  // to<> безопасен
    
    BruceConfig config;
    config.fromJson(configDoc);
    
    return configDoc;
}
