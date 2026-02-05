#include <Arduino.h>
#include <ArduinoJson.h>
#include "core/config.h"

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("=== Bruce Firmware - WORKING VERSION ===");
    
    // Простая инициализация
    DynamicJsonDocument doc(1024);
    doc["version"] = "1.0";
    doc["status"] = "ready";
    
    Serial.println("System initialized successfully");
}

void loop() {
    delay(3000);
    static int counter = 0;
    Serial.printf("Counter: %d\n", counter++);
}
