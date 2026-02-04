#ifndef CONFIG_H
#define CONFIG_H

#include <ArduinoJson.h>
#include <vector>
#include <string>

// Временно отключаем наследование от BruceTheme
// #include "theme.h"

struct QRCode {
    std::string name;
    std::string data;
};

class BruceConfig {
public:
    static constexpr const char* CONFIG_FILE = "/config.json";
    
    // Настройки темы (временно здесь, пока не разберёмся с BruceTheme)
    std::string theme = "default";
    uint32_t primaryColor = 0x0000FF;
    uint32_t secondaryColor = 0xFF0000;
    uint32_t backgroundColor = 0x000000;
    uint32_t textColor = 0xFFFFFF;
    
    // Общие настройки
    uint8_t brightness = 255;
    uint8_t dimTime = 30;
    uint8_t orientation = 0;
    uint16_t sleepTime = 0;
    bool bootSound = true;
    
    // WiFi
    std::string wifiSSID;
    std::string wifiPassword;
    std::string apSSID = "BruceAP";
    std::string apPassword = "bruce123";
    
    // Часы
    std::string ntpServer = "pool.ntp.org";
    int timezone = 0;
    bool clock24h = true;
    
    // QR коды
    std::vector<QRCode> qrCodes;
    
    // Методы
    DynamicJsonDocument toJson() const;
    void fromJson(const DynamicJsonDocument& doc);
    void fromFile(bool resetOnError = true);
    void saveFile();
    void resetToDefaults();
};

extern BruceConfig config;

#endif
