#ifndef CONFIG_H
#define CONFIG_H

#include <ArduinoJson.h>

class BruceConfig {
public:
    void fromJson(const DynamicJsonDocument& doc);
    DynamicJsonDocument toJson() const;
};

DynamicJsonDocument loadConfig();

#endif // CONFIG_H
