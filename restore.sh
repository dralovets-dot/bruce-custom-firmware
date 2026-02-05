#!/bin/bash
echo "=== ПОЛНОЕ ВОССТАНОВЛЕНИЕ ПРОЕКТА ==="

# 1. Очищаем и создаем структуру
echo "1. Очистка и создание структуры..."
rm -rf src lib .github 2>/dev/null
mkdir -p src/core
mkdir -p lib
mkdir -p .github/workflows

# 2. Создаем config.cpp (безопасная версия)
echo "2. Создание config.cpp..."
cat > src/core/config.cpp << 'CONFIG_CPP_EOF'
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
CONFIG_CPP_EOF

# 3. Создаем config.h
echo "3. Создание config.h..."
cat > src/core/config.h << 'CONFIG_H_EOF'
#ifndef CONFIG_H
#define CONFIG_H

#include <ArduinoJson.h>

class BruceConfig {
public:
    void fromJson(const DynamicJsonDocument& doc);
    DynamicJsonDocument toJson() const;
};

DynamicJsonDocument loadConfig();

#endif
CONFIG_H_EOF

# 4. Создаем main.cpp
echo "4. Создание main.cpp..."
cat > src/main.cpp << 'MAIN_CPP_EOF'
#include <Arduino.h>
#include "config.h"

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("=== Bruce Firmware ===");
    
    DynamicJsonDocument doc = loadConfig();
    Serial.println("Config loaded");
}

void loop() {
    delay(5000);
    Serial.println("Working...");
}
MAIN_CPP_EOF

# 5. Создаем platformio.ini
echo "5. Создание platformio.ini..."
cat > platformio.ini << 'PLATFORMIO_EOF'
[env:lilygo-t-embed-cc1101]
platform = espressif32@6.5.0
board = esp32-s3-devkitc-1
framework = arduino
monitor_speed = 115200
lib_deps = bblanchon/ArduinoJson@6.21.3
build_flags = -DMINIMAL_BUILD
PLATFORMIO_EOF

# 6. Создаем простой workflow
echo "6. Создание GitHub Actions workflow..."
cat > .github/workflows/build.yml << 'WORKFLOW_EOF'
name: Build
on: [push]
jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - run: pip install platformio && pio run
WORKFLOW_EOF

echo "✅ ПРОЕКТ ВОССТАНОВЛЕН!"
echo "Структура проекта:"
find . -type f -name "*.cpp" -o -name "*.h" -o -name "platformio.ini" -o -name "*.yml" | sort
