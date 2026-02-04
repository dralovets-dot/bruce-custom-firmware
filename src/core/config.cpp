#include "config.h"
#include <LittleFS.h>

DynamicJsonDocument BruceConfig::toJson() const {
    DynamicJsonDocument jsonDoc(4096);
    
    JsonObject root = jsonDoc.to<JsonObject>();
    
    // Настройки темы
    #ifndef HAS_BRUCETHEME
    root["theme"] = theme;
    root["primaryColor"] = primaryColor;
    root["secondaryColor"] = secondaryColor;
    root["backgroundColor"] = backgroundColor;
    root["textColor"] = textColor;
    #endif
    
    // Общие настройки
    root["brightness"] = brightness;
    root["dimTime"] = dimTime;
    root["orientation"] = orientation;
    root["sleepTime"] = sleepTime;
    root["bootSound"] = bootSound;
    
    // Настройки WiFi
    JsonObject wifiObj = root.createNestedObject("wifi");
    wifiObj["ssid"] = wifiSSID;
    wifiObj["password"] = wifiPassword;
    wifiObj["apSSID"] = apSSID;
    wifiObj["apPassword"] = apPassword;
    
    // Настройки часов
    JsonObject clockObj = root.createNestedObject("clock");
    clockObj["ntpServer"] = ntpServer;
    clockObj["timezone"] = timezone;
    clockObj["24h"] = clock24h;
    
    // QR коды
    JsonArray qrArray = root.createNestedArray("qrCodes");
    for (const auto& qr : qrCodes) {
        JsonObject qrEntry = qrArray.createNestedObject();
        qrEntry["name"] = qr.name;
        qrEntry["data"] = qr.data;
    }
    
    return jsonDoc;
}

void BruceConfig::fromJson(const DynamicJsonDocument& doc) {
    // Проверяем, что это JsonObject без использования as<JsonObject>()
    if (!doc.isNull() && doc.is<JsonObject>()) {
        JsonObject root = doc.as<JsonObject>();
        
        // Настройки темы
        #ifndef HAS_BRUCETHEME
        theme = root["theme"] | "default";
        primaryColor = root["primaryColor"] | 0x0000FF;
        secondaryColor = root["secondaryColor"] | 0xFF0000;
        backgroundColor = root["backgroundColor"] | 0x000000;
        textColor = root["textColor"] | 0xFFFFFF;
        #endif
        
        // Общие настройки
        brightness = root["brightness"] | 255;
        dimTime = root["dimTime"] | 30;
        orientation = root["orientation"] | 0;
        sleepTime = root["sleepTime"] | 0;
        bootSound = root["bootSound"] | true;
        
        // Настройки WiFi
        if (root.containsKey("wifi")) {
            JsonObject wifiObj = root["wifi"];
            wifiSSID = wifiObj["ssid"] | "";
            wifiPassword = wifiObj["password"] | "";
            apSSID = wifiObj["apSSID"] | "BruceAP";
            apPassword = wifiObj["apPassword"] | "bruce123";
        }
        
        // Настройки часов
        if (root.containsKey("clock")) {
            JsonObject clockObj = root["clock"];
            ntpServer = clockObj["ntpServer"] | "pool.ntp.org";
            timezone = clockObj["timezone"] | 0;
            clock24h = clockObj["24h"] | true;
        }
        
        // QR коды
        qrCodes.clear();
        if (root.containsKey("qrCodes")) {
            JsonArray qrArray = root["qrCodes"];
            for (JsonObject qrEntry : qrArray) {
                QRCode qr;
                qr.name = qrEntry["name"] | "";
                qr.data = qrEntry["data"] | "";
                qrCodes.push_back(qr);
            }
        }
    }
}

void BruceConfig::fromFile(bool resetOnError) {
    if (!LittleFS.begin()) {
        if (resetOnError) resetToDefaults();
        return;
    }
    
    if (!LittleFS.exists(CONFIG_FILE)) {
        if (resetOnError) resetToDefaults();
        LittleFS.end();
        return;
    }
    
    File file = LittleFS.open(CONFIG_FILE, "r");
    if (!file) {
        if (resetOnError) resetToDefaults();
        LittleFS.end();
        return;
    }
    
    DynamicJsonDocument jsonDoc(4096);
    DeserializationError error = deserializeJson(jsonDoc, file);
    file.close();
    LittleFS.end();
    
    if (error) {
        if (resetOnError) resetToDefaults();
        return;
    }
    
    fromJson(jsonDoc);
}

void BruceConfig::saveFile() {
    if (!LittleFS.begin()) return;
    
    DynamicJsonDocument jsonDoc = toJson();
    
    File file = LittleFS.open(CONFIG_FILE, "w");
    if (!file) {
        LittleFS.end();
        return;
    }
    
    serializeJson(jsonDoc, file);
    file.close();
    LittleFS.end();
}

void BruceConfig::resetToDefaults() {
    // Сброс к значениям по умолчанию
    #ifndef HAS_BRUCETHEME
    theme = "default";
    primaryColor = 0x0000FF;
    secondaryColor = 0xFF0000;
    backgroundColor = 0x000000;
    textColor = 0xFFFFFF;
    #endif
    
    brightness = 255;
    dimTime = 30;
    orientation = 0;
    sleepTime = 0;
    bootSound = true;
    
    wifiSSID = "";
    wifiPassword = "";
    apSSID = "BruceAP";
    apPassword = "bruce123";
    
    ntpServer = "pool.ntp.org";
    timezone = 0;
    clock24h = true;
    
    qrCodes.clear();
    
    // Сохраняем настройки по умолчанию
    saveFile();
}

BruceConfig config;
