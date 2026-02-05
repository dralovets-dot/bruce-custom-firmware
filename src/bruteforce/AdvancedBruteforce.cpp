#include "AdvancedBruteforce.h"
#include <ArduinoJson.h>
#include "SPIFFS.h"

AdvancedBruteforce::AdvancedBruteforce() {
    config.currentKey = config.startKey;
}

void AdvancedBruteforce::begin() {
    // Инициализация если нужно
}

void AdvancedBruteforce::update() {
    if (state != State::RUNNING) return;
    
    unsigned long now = millis();
    if (now - lastAttemptTime >= (1000 / config.attemptsPerSecond)) {
        attemptKey(config.currentKey);
        config.currentKey++;
        attemptsCount++;
        lastAttemptTime = now;
        
        // Оповещение о прогрессе
        if (progressCallback) {
            float progress = ((float)(config.currentKey - config.startKey) / 
                            (float)(config.endKey - config.startKey)) * 100.0f;
            progressCallback(config.currentKey, attemptsCount, progress);
        }
        
        // Проверка окончания диапазона
        if (config.currentKey >= config.endKey) {
            changeState(State::STOPPED);
        }
    }
}

void AdvancedBruteforce::start() {
    if (state == State::IDLE || state == State::STOPPED) {
        loadProgressFromFile();
        changeState(State::RUNNING);
    }
}

void AdvancedBruteforce::pause() {
    if (state == State::RUNNING) {
        changeState(State::PAUSED);
        if (config.saveProgress) {
            saveProgressToFile();
        }
    }
}

void AdvancedBruteforce::stop() {
    changeState(State::STOPPED);
    if (config.saveProgress) {
        saveProgressToFile();
    }
}

void AdvancedBruteforce::resume() {
    if (state == State::PAUSED) {
        changeState(State::RUNNING);
    }
}

void AdvancedBruteforce::rewind(uint32_t toKey) {
    changeState(State::REWINDING);
    config.currentKey = (toKey > 0) ? toKey : config.startKey;
    attemptsCount = 0;
    
    if (config.saveProgress) {
        saveProgressToFile();
    }
    
    changeState(State::IDLE);
}

void AdvancedBruteforce::verifyFoundKey() {
    if (state == State::KEY_FOUND && config.verifyFoundKey) {
        changeState(State::VERIFYING);
        
        // Повторная отправка найденного ключа для проверки
        bool verified = sendKey(config.foundKey, config.protocol);
        
        if (verified) {
            Serial.printf("[Bruteforce] Key %08X verified successfully\n", config.foundKey);
        } else {
            Serial.printf("[Bruteforce] Key %08X verification failed\n", config.foundKey);
        }
        
        changeState(State::KEY_FOUND);
    }
}

void AdvancedBruteforce::setKeyFoundCallback(std::function<void(uint32_t)> callback) {
    keyFoundCallback = callback;
}

void AdvancedBruteforce::setStateChangeCallback(std::function<void(State)> callback) {
    stateChangeCallback = callback;
}

void AdvancedBruteforce::setProgressCallback(std::function<void(uint32_t, uint32_t, float)> callback) {
    progressCallback = callback;
}

void AdvancedBruteforce::setConfig(const BruteforceConfig& newConfig) {
    config = newConfig;
}

void AdvancedBruteforce::saveProgressToFile() {
    if (!SPIFFS.begin(true)) {
        Serial.println("[Bruteforce] Failed to mount SPIFFS");
        return;
    }
    
    File file = SPIFFS.open("/bruteforce_progress.json", "w");
    if (!file) {
        Serial.println("[Bruteforce] Failed to open file for writing");
        return;
    }
    
    DynamicJsonDocument doc(512);
    doc["currentKey"] = config.currentKey;
    doc["attemptsCount"] = attemptsCount;
    doc["foundKey"] = config.foundKey;
    doc["state"] = static_cast<int>(state);
    
    if (serializeJson(doc, file) == 0) {
        Serial.println("[Bruteforce] Failed to write to file");
    }
    
    file.close();
    SPIFFS.end();
    
    Serial.println("[Bruteforce] Progress saved");
}

void AdvancedBruteforce::loadProgressFromFile() {
    if (!SPIFFS.begin(true)) {
        Serial.println("[Bruteforce] Failed to mount SPIFFS");
        return;
    }
    
    if (!SPIFFS.exists("/bruteforce_progress.json")) {
        SPIFFS.end();
        return;
    }
    
    File file = SPIFFS.open("/bruteforce_progress.json", "r");
    if (!file) {
        Serial.println("[Bruteforce] Failed to open file for reading");
        SPIFFS.end();
        return;
    }
    
    DynamicJsonDocument doc(512);
    DeserializationError error = deserializeJson(doc, file);
    file.close();
    SPIFFS.end();
    
    if (error) {
        Serial.println("[Bruteforce] Failed to parse progress file");
        return;
    }
    
    config.currentKey = doc["currentKey"] | config.startKey;
    attemptsCount = doc["attemptsCount"] | 0;
    config.foundKey = doc["foundKey"] | 0;
    
    Serial.printf("[Bruteforce] Loaded progress: key=%08X, attempts=%lu\n", 
                  config.currentKey, attemptsCount);
}

void AdvancedBruteforce::changeState(State newState) {
    State oldState = state;
    state = newState;
    
    if (stateChangeCallback) {
        stateChangeCallback(newState);
    }
    
    Serial.printf("[Bruteforce] State changed: %d -> %d\n", 
                  static_cast<int>(oldState), static_cast<int>(newState));
}

void AdvancedBruteforce::attemptKey(uint32_t key) {
    bool success = sendKey(key, config.protocol);
    
    if (success) {
        onKeyFound(key);
    }
}

void AdvancedBruteforce::onKeyFound(uint32_t key) {
    config.foundKey = key;
    changeState(State::KEY_FOUND);
    
    if (keyFoundCallback) {
        keyFoundCallback(key);
    }
    
    Serial.printf("[Bruteforce] KEY FOUND: %08X\n", key);
    
    // Автоматическая перемотка если включена
    if (config.autoRewind) {
        rewind(config.startKey);
    }
}

bool AdvancedBruteforce::sendKey(uint32_t key, uint8_t protocol) {
    // Заглушка - будет реализована в RF модуле
    Serial.printf("[RF] Sending key %08X via protocol %d\n", key, protocol);
    
    // Имитация успеха (1% chance для теста)
    return (random(100) < 1);
}

bool AdvancedBruteforce::verifyKey(uint32_t key, uint8_t protocol) {
    // Заглушка для проверки ключа
    Serial.printf("[RF] Verifying key %08X via protocol %d\n", key, protocol);
    return sendKey(key, protocol);
}
