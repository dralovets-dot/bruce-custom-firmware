#include <Arduino.h>
#include "display/DisplayManager_TFT_eSPI.h"

DisplayManager_TFT_eSPI display;

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("========================================");
    Serial.println("BRUCE RF T-Embed CC1101 - TFT_eSPI Test");
    Serial.println("========================================");
    
    // Инициализация дисплея
    if (display.begin()) {
        Serial.println("[OK] Display initialized with TFT_eSPI");
        
        // Тест 1: Простой текст
        display.clear();
        display.drawText(10, 10, "T-Embed CC1101", TFT_GREEN, 2);
        display.drawText(10, 40, "Display: ST7789 320x170", TFT_WHITE, 1);
        display.drawText(10, 60, "Library: TFT_eSPI", TFT_CYAN, 1);
        delay(2000);
        
        // Тест 2: Статус брутфорса
        display.drawBruteforceStatus(0xA1B2C3D4, 0, 1250, 0.65f, "RUNNING");
        Serial.println("[TEST] Displaying bruteforce status");
        delay(3000);
        
        // Тест 3: Меню
        String menuItems[] = {"Bruteforce", "Learn Key", "Settings", "RF Scan", "About"};
        display.drawMenu(menuItems, 5, 1);
        Serial.println("[TEST] Displaying menu");
        
    } else {
        Serial.println("[ERROR] Display initialization failed!");
    }
}

void loop() {
    static uint32_t counter = 0;
    static unsigned long lastUpdate = 0;
    
    // Простой счётчик в углу экрана
    if (millis() - lastUpdate > 1000) {
        display.drawText(280, 150, String(counter % 10), TFT_YELLOW, 2);
        counter++;
        lastUpdate = millis();
        
        if (counter % 5 == 0) {
            Serial.printf("[LOOP] Counter: %u\n", counter);
        }
    }
    
    delay(100);
}
