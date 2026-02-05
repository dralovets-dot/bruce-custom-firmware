#include <ArduinoJson.h>
#include "config.h"
void setup() { 
    Serial.begin(115200); 
    Serial.println("OK"); 
    DynamicJsonDocument doc = loadConfig();
}
void loop() { delay(1000); Serial.println("."); }
