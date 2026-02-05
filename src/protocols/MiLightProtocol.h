#ifndef MILIGHT_PROTOCOL_H
#define MILIGHT_PROTOCOL_H

#include "../rf/RFProtocolManager.h"

class MiLightProtocol : public RFProtocol {
public:
    MiLightProtocol();
    ~MiLightProtocol() override;
    
    bool sendData(const uint8_t* data, size_t length) override;
    bool receiveData(uint8_t* buffer, size_t& length, uint32_t timeout = 1000) override;
    bool setup() override;
    
private:
    void sendMiLightPacket(uint8_t* packet, size_t length);
};

#endif // MILIGHT_PROTOCOL_H
