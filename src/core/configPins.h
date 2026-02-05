#ifndef CONFIGPINS_H
#define CONFIGPINS_H

#include <ArduinoJson.h>

class BruceConfigPins {
public:
    void fromJson(const DynamicJsonDocument& doc);
    void toJson(JsonObject& root) const;
    void loadFile();
    void saveFile();
};

#endif
