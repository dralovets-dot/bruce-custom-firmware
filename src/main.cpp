#include <Arduino.h>
#include "display/DisplayManager_TFT_eSPI.h"

DisplayManager_TFT_eSPI display;

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("=== T-Embed Bruce RF (TFT_eSPI) ===");
    
    if(display.begin()) {
        Serial.println("Display: OK");
        display.drawText(10, 10, "T-Embed CC1101", TFT_GREEN, 2);
        display.drawText(10, 40, "TFT_eSPI Ready", TFT_WHITE, 1);
    } else {
        Serial.println("Display: FAIL");
    }
}

void loop() {
    delay(1000);
}
