#ifndef ESP32TIME_H
#define ESP32TIME_H
class ESP32Time {
public:
    void setTime(long) {}
    String getTime() { return ""; }
    String getDateTime() { return ""; }
    long getEpoch() { return 0; }
};
#endif
