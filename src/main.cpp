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
