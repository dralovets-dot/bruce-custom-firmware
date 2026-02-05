#!/bin/bash
mkdir -p lib

# ESP32Time заглушка
cat > lib/ESP32Time.h << 'STUB1'
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
STUB1

# SimpleCLI заглушка  
cat > lib/SimpleCLI.h << 'STUB2'
#ifndef SIMPLECLI_H
#define SIMPLECLI_H
class CLI { public: void parse(String) {} };
class Command { public: void addArg(String) {} };
#endif
STUB2

# AsyncTCP заглушка
cat > lib/AsyncTCP.h << 'STUB3'
#ifndef ASYNCTCP_H
#define ASYNCTCP_H
class AsyncClient { public: bool connect(const char*, uint16_t) { return false; } };
#endif
STUB3

# ESPAsyncWebServer заглушка
cat > lib/ESPAsyncWebServer.h << 'STUB4'
#ifndef ESPASYNCWEBSERVER_H
#define ESPASYNCWEBSERVER_H
class AsyncWebServer { public: AsyncWebServer(uint16_t) {} void begin() {} };
#endif
STUB4

echo "All stubs created in lib/"
