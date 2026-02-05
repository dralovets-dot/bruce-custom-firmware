#ifndef ADVANCED_BRUTEFORCE_H
#define ADVANCED_BRUTEFORCE_H

#include <Arduino.h>
#include <vector>
#include <functional>

class AdvancedBruteforce {
public:
    enum class State {
        IDLE,
        RUNNING,
        PAUSED,
        STOPPED,
        KEY_FOUND,
        REWINDING,
        VERIFYING
    };

    struct BruteforceConfig {
        uint32_t startKey = 0;
        uint32_t endKey = 0xFFFFFFFF;
        uint32_t currentKey = 0;
        uint32_t foundKey = 0;
        uint16_t attemptsPerSecond = 100;
        uint8_t protocol = 0;
        bool autoRewind = true;
        bool verifyFoundKey = true;
        bool saveProgress = true;
    };

    AdvancedBruteforce();
    
    void begin();
    void update();
    
    void start();
    void pause();
    void stop();
    void resume();
    void rewind(uint32_t toKey = 0);
    void verifyFoundKey();
    
    void setKeyFoundCallback(std::function<void(uint32_t)> callback);
    void setStateChangeCallback(std::function<void(State)> callback);
    void setProgressCallback(std::function<void(uint32_t, uint32_t, float)> callback);
    
    State getState() const { return state; }
    BruteforceConfig getConfig() const { return config; }
    void setConfig(const BruteforceConfig& newConfig);
    
    void saveProgressToFile();
    void loadProgressFromFile();
    
private:
    State state = State::IDLE;
    BruteforceConfig config;
    unsigned long lastAttemptTime = 0;
    uint32_t attemptsCount = 0;
    
    std::function<void(uint32_t)> keyFoundCallback = nullptr;
    std::function<void(State)> stateChangeCallback = nullptr;
    std::function<void(uint32_t, uint32_t, float)> progressCallback = nullptr;
    
    void changeState(State newState);
    void attemptKey(uint32_t key);
    void onKeyFound(uint32_t key);
    void generateNextKey();
    
    // RF операции
    bool sendKey(uint32_t key, uint8_t protocol);
    bool verifyKey(uint32_t key, uint8_t protocol);
};

#endif // ADVANCED_BRUTEFORCE_H
