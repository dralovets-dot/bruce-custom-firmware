#ifndef CONFIG_H
#define CONFIG_H

#include <ArduinoJson.h>
#include <vector>
#include <string>

struct QRCode {
    std::string name;
    std::string data;
};

class BruceConfig : public BruceTheme {
public:
    static constexpr const char* CONFIG_FILE = "/config.json";
    
    // Настройки
    std::string theme = "default";
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
    
    // Загрузка/сохранение
    void load() { fromFile(); }
    void save() { saveFile(); }
};

extern BruceConfig config;

#endif
