#ifndef RF_PROTOCOL_MANAGER_H
#define RF_PROTOCOL_MANAGER_H

#include <Arduino.h>
#include <vector>
#include <map>

class RFProtocol {
public:
    struct ProtocolInfo {
        uint8_t id;
        String name;
        String description;
        uint32_t frequency;  // Hz
        uint32_t baudRate;   // bps
        uint8_t modulation;
        uint16_t syncWord;
        bool enabled;
    };
    
    RFProtocol(uint8_t id, const String& name, uint32_t frequency);
    virtual ~RFProtocol() {}
    
    virtual bool sendData(const uint8_t* data, size_t length) = 0;
    virtual bool receiveData(uint8_t* buffer, size_t& length, uint32_t timeout = 1000) = 0;
    virtual bool setup() = 0;
    
    ProtocolInfo getInfo() const { return info; }
    
protected:
    ProtocolInfo info;
};

class RFProtocolManager {
public:
    static RFProtocolManager& getInstance();
    
    void registerProtocol(RFProtocol* protocol);
    RFProtocol* getProtocol(uint8_t id);
    RFProtocol* getProtocol(const String& name);
    
    std::vector<ProtocolInfo> getAvailableProtocols() const;
    std::vector<ProtocolInfo> getEnabledProtocols() const;
    
    bool enableProtocol(uint8_t id);
    bool disableProtocol(uint8_t id);
    
    bool sendWithProtocol(uint8_t protocolId, const uint8_t* data, size_t length);
    
private:
    RFProtocolManager() {}
    std::map<uint8_t, RFProtocol*> protocols;
};
#endif // RF_PROTOCOL_MANAGER_H
