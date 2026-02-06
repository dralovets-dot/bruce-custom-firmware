#include <Arduino.h>
#include "display/DisplayManager_ST7789.h"

DisplayManager_ST7789 display;

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("=== T-Embed Bruce RF ===");
    
    if(display.begin()) {
        Serial.println("Display: OK");
        display.drawBruteforceStatus(0xA1B2C3D4, 0, 1250, 0.65f, "TEST");
    } else {
        Serial.println("Display: FAIL");
    }
}

void loop() {
    delay(1000);
}
