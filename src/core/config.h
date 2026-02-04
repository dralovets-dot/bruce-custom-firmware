#ifndef CONFIG_H
#define CONFIG_H

#include <ArduinoJson.h>
#include <vector>
#include <string>

struct QRCode {
    std::string name;
    std::string data;
};

class BruceConfig {
public:
    static constexpr const char* CONFIG_FILE = "/config.json";
    
    // Настройки
    std::string theme = "default";
    uint32_t primaryColor = 0x0000FF;
    uint32_t secondaryColor = 0xFF0000;
    uint32_t backgroundColor = 0x000000;
    uint32_t textColor = 0xFFFFFF;
    
    uint8_t brightness = 255;
    uint8_t dimTime = 30;
    uint8_t orientation = 0;
    uint16_t sleepTime = 0;
    bool bootSound = true;
    
    std::string wifiSSID;
    std::string wifiPassword;
    std::string apSSID = "BruceAP";
    std::string apPassword = "bruce123";
    
    std::string ntpServer = "pool.ntp.org";
    int timezone = 0;
    bool clock24h = true;
    
    std::vector<QRCode> qrCodes;
    
    DynamicJsonDocument toJson() const;
    void fromJson(const DynamicJsonDocument& doc);
    void fromFile(bool resetOnError = true);
    void saveFile();
    void resetToDefaults();
};

extern BruceConfig config;

#endif
