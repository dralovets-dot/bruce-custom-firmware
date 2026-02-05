#include <Arduino.h>
#include <ArduinoJson.h>
#include "core/config.h"
#include "bruteforce/AdvancedBruteforce.h"
#include "display/DisplayManager.h"
#include "display/ThemeManager.h"

AdvancedBruteforce bruteforce;
DisplayManager display;
ThemeManager themes;

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("=== Bruce Firmware - Enhanced Bruteforce ===");
    Serial.println("Initializing...");
    
    // Инициализация дисплея
    Serial.println("Initializing display...");
    display.begin();
    display.setTheme(themes.getDarkTheme());
    display.setFont(DisplayManager::FONT_MEDIUM);
    
    // Отображаем заставку
    display.clear();
    display.drawText(10, 10, "BRUCE RF FIRMWARE", DisplayManager::FONT_LARGE);
    display.drawText(20, 40, "Enhanced Bruteforce v1.0");
    display.drawText(30, 60, "Initializing...");
    display.refresh();
    
    delay(2000);
    
    // Настройка брутфорса
    AdvancedBruteforce::BruteforceConfig config;
    config.startKey = 0x00000000;
    config.endKey = 0x0000FFFF;  // Только для теста
    config.attemptsPerSecond = 50;
    config.protocol = 0;
    config.autoRewind = true;
    config.verifyFoundKey = true;
    config.saveProgress = false;  // Временно отключено
    
    bruteforce.setConfig(config);
    bruteforce.begin();
    
    // Callback для найденного ключа
    bruteforce.setKeyFoundCallback([](uint32_t key) {
        Serial.printf("\n🎉 KEY FOUND: 0x%08X\n", key);
        display.drawText(10, 100, "KEY FOUND!", DisplayManager::FONT_LARGE);
        display.drawText(20, 120, String("0x") + String(key, HEX));
        display.refresh();
    });
    
    // Callback для изменения состояния
    bruteforce.setStateChangeCallback([](AdvancedBruteforce::State state) {
        const char* states[] = {"IDLE", "RUNNING", "PAUSED", "STOPPED", 
                               "KEY_FOUND", "REWINDING", "VERIFYING"};
        Serial.printf("State changed to: %s\n", states[static_cast<int>(state)]);
        
        // Обновляем дисплей
        display.drawText(10, 80, String("State: ") + states[static_cast<int>(state)]);
        display.refresh();
    });
    
    // Callback для прогресса
    bruteforce.setProgressCallback([](uint32_t currentKey, uint32_t attempts, float progress) {
        if (attempts % 100 == 0) {
            Serial.printf("Progress: %08X | Attempts: %lu | %.2f%%\r", 
                         currentKey, attempts, progress);
            
            // Обновляем дисплей
            display.drawBruteforceStatus(currentKey, 0, attempts, progress, "RUNNING");
            display.refresh();
        }
    });
    
    // Очищаем дисплей и показываем главный экран
    display.clear();
    display.drawText(10, 10, "BRUTEFORCE READY", DisplayManager::FONT_MEDIUM);
    display.drawText(20, 30, "Type commands:");
    display.drawText(30, 50, "- start: begin");
    display.drawText(30, 65, "- stop:  halt");
    display.drawText(30, 80, "- pause: pause");
    display.refresh();
    
    Serial.println("System ready. Type commands:");
    Serial.println("  'start' - start bruteforce");
    Serial.println("  'pause' - pause bruteforce");
    Serial.println("  'stop'  - stop bruteforce");
    Serial.println("  'resume' - resume bruteforce");
    Serial.println("  'rewind' - rewind to start");
    Serial.println("  'verify' - verify found key");
    Serial.println("  'font [num]' - change font (0-7)");
    Serial.println("  'theme [name]' - change theme");
}

void loop() {
    bruteforce.update();
    
    // Обработка команд с Serial
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n');
        command.trim();
        
        if (command == "start") {
            Serial.println("Starting bruteforce...");
            bruteforce.start();
        } else if (command == "pause") {
            Serial.println("Pausing bruteforce...");
            bruteforce.pause();
        } else if (command == "stop") {
            Serial.println("Stopping bruteforce...");
            bruteforce.stop();
        } else if (command == "resume") {
            Serial.println("Resuming bruteforce...");
            bruteforce.resume();
        } else if (command == "rewind") {
            Serial.println("Rewinding to start...");
            bruteforce.rewind();
        } else if (command == "verify") {
            Serial.println("Verifying found key...");
            bruteforce.verifyFoundKey();
        } else if (command == "status") {
            auto state = bruteforce.getState();
            auto config = bruteforce.getConfig();
            Serial.printf("State: %d\n", static_cast<int>(state));
            Serial.printf("Current key: 0x%08X\n", config.currentKey);
            Serial.printf("Found key: 0x%08X\n", config.foundKey);
        } else if (command.startsWith("font ")) {
            int fontNum = command.substring(5).toInt();
            if (fontNum >= 0 && fontNum <= 7) {
                display.setFont(static_cast<DisplayManager::FontStyle>(fontNum));
                Serial.printf("Font changed to: %d\n", fontNum);
            }
        } else if (command.startsWith("theme ")) {
            String themeName = command.substring(6);
            // Здесь будет смена темы
            Serial.printf("Theme change to: %s\n", themeName.c_str());
        }
    }
    
    delay(10);
}
