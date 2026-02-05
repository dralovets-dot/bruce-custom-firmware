#include "config.h"
#include <ArduinoJson.h>

void BruceConfig::fromJson(const DynamicJsonDocument& doc) {
    (void)doc;
}

DynamicJsonDocument BruceConfig::toJson() const {
    DynamicJsonDocument doc(1024);
    JsonObject root = doc.to<JsonObject>();
    root["status"] = "ok";
    return doc;
}

DynamicJsonDocument loadConfig() {
    DynamicJsonDocument configDoc(1024);
    JsonObject obj = configDoc.to<JsonObject>();
    obj["loaded"] = true;
    return configDoc;
}
