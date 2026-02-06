#include <Arduino.h>
#include "display/DisplayManager_ST7789.h"

DisplayManager_ST7789 display;

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("=== BRUCE RF T-Embed CC1101 ===");
    
    // Инициализация дисплея
    if(display.begin()) {
        Serial.println("ST7789 Display: OK");
        
        // Тест 1: Статус брутфорса
        display.drawBruteforceStatus(0xA1B2C3D4, 0, 1250, 0.65f, "RUNNING");
        delay(3000);
        
        // Тест 2: Меню
        String menuItems[] = {"Bruteforce", "Learn Key", "Settings", "RF Scan", "About"};
        display.drawMenu(menuItems, 5, 1);
        delay(3000);
        
        // Тест 3: Очистка и простой текст
        display.clear();
        display.drawText(10, 10, "BRUCE RF READY", 0x07E0, 2); // Зеленый
        display.drawText(10, 40, "T-Embed CC1101", 0xFFFF, 1); // Белый
        display.drawText(10, 70, "Display: ST7789 320x170", 0xF800, 1); // Красный
        
    } else {
        Serial.println("ST7789 Display: FAILED!");
    }
}

void loop() {
    static uint32_t counter = 0;
    
    // Простой счетчик на дисплее
    display.drawText(200, 100, String(counter++), 0xFFE0, 2); // Желтый
    
    delay(1000);
}
