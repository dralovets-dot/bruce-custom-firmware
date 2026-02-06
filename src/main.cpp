#include <Arduino.h>
#include "display/DisplayManager_ST7789.h"

DisplayManager_ST7789 display;

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("=== BRUCE RF T-Embed CC1101 ===");
    
    if(display.begin()) {
        Serial.println("ST7789 Display: OK");
        display.drawBruteforceStatus(0xA1B2C3D4, 0, 1250, 0.65f, "RUNNING");
    } else {
        Serial.println("ST7789 Display: FAILED!");
    }
}

void loop() {
    delay(1000);
}
