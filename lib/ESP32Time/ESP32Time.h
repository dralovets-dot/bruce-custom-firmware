// ESP32Time Stub
#ifndef ESP32TIME_H
#define ESP32TIME_H

#include <Arduino.h>

class ESP32Time {
public:
    ESP32Time() {}
    ESP32Time(long offset) {}
    
    void setTime(long epoch) {}
    void setTime(int sc, int mn, int hr, int dy, int mt, int yr, int ms = 0) {}
    
    String getTime() { return "00:00:00"; }
    String getDateTime() { return "1970-01-01 00:00:00"; }
    long getEpoch() { return 0; }
    
    struct tm getTimeStruct() {
        struct tm timeinfo = {};
        return timeinfo;
    }
};

#endif
