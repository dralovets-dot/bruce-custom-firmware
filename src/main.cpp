#include <Arduino.h>
#include <ArduinoJson.h>
#include "core/config.h"
#include "bruteforce/AdvancedBruteforce.h"

AdvancedBruteforce bruteforce;

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("=== Bruce Firmware - Enhanced Bruteforce ===");
    Serial.println("Initializing...");
    
    // Настройка брутфорса
    AdvancedBruteforce::BruteforceConfig config;
    config.startKey = 0x00000000;
    config.endKey = 0x0000FFFF;  // Только для теста
    config.attemptsPerSecond = 50;
    config.protocol = 0;
    config.autoRewind = true;
    config.verifyFoundKey = true;
    config.saveProgress = true;
    
    bruteforce.setConfig(config);
    
    // Callback для найденного ключа
    bruteforce.setKeyFoundCallback([](uint32_t key) {
        Serial.printf("\n🎉 KEY FOUND: 0x%08X\n", key);
        Serial.println("Starting verification...");
    });
    
    // Callback для изменения состояния
    bruteforce.setStateChangeCallback([](AdvancedBruteforce::State state) {
        const char* states[] = {"IDLE", "RUNNING", "PAUSED", "STOPPED", 
                               "KEY_FOUND", "REWINDING", "VERIFYING"};
        Serial.printf("State changed to: %s\n", states[static_cast<int>(state)]);
    });
    
    // Callback для прогресса
    bruteforce.setProgressCallback([](uint32_t currentKey, uint32_t attempts, float progress) {
        if (attempts % 100 == 0) {
            Serial.printf("Progress: %08X | Attempts: %lu | %.2f%%\r", 
                         currentKey, attempts, progress);
        }
    });
    
    Serial.println("System ready. Type commands:");
    Serial.println("  'start' - start bruteforce");
    Serial.println("  'pause' - pause bruteforce");
    Serial.println("  'stop'  - stop bruteforce");
    Serial.println("  'resume' - resume bruteforce");
    Serial.println("  'rewind' - rewind to start");
    Serial.println("  'verify' - verify found key");
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
        }
    }
    
    delay(10);
}
