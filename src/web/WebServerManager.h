#ifndef WEBSERVER_MANAGER_H
#define WEBSERVER_MANAGER_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "bruteforce/AdvancedBruteforce.h"

class WebServerManager {
public:
    WebServerManager(AdvancedBruteforce& bruteforce);
    ~WebServerManager();
    
    void begin();
    void update();
    
    void sendBruteforceStatus(AsyncWebServerRequest* request);
    void sendProtocolsList(AsyncWebServerRequest* request);
    
private:
    AsyncWebServer server;
    AdvancedBruteforce& bruteforce;
    AsyncWebSocket ws;
    
    void setupRoutes();
    void setupWebSocket();
    
    void handleRoot(AsyncWebServerRequest* request);
    void handleStart(AsyncWebServerRequest* request);
    void handleStop(AsyncWebServerRequest* request);
    void handlePause(AsyncWebServerRequest* request);
    void handleResume(AsyncWebServerRequest* request);
    void handleRewind(AsyncWebServerRequest* request);
    void handleVerify(AsyncWebServerRequest* request);
    void handleSetRange(AsyncWebServerRequest* request);
    void handleSetProtocol(AsyncWebServerRequest* request);
    void handleSetSpeed(AsyncWebServerRequest* request);
    
    void onWebSocketEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, 
                         AwsEventType type, void* arg, uint8_t* data, size_t len);
    
    void broadcastStatus();
    String getStatusJSON();
};

#endif // WEBSERVER_MANAGER_H
