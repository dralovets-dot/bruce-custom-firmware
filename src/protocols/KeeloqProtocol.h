#ifndef KEELOQ_PROTOCOL_H
#define KEELOQ_PROTOCOL_H

#include "../rf/RFProtocolManager.h"

class KeeloqProtocol : public RFProtocol {
public:
    KeeloqProtocol();
    ~KeeloqProtocol() override;
    
    bool sendData(const uint8_t* data, size_t length) override;
    bool receiveData(uint8_t* buffer, size_t& length, uint32_t timeout = 1000) override;
    bool setup() override;
    
private:
    void sendKeeloq(uint32_t fixed, uint32_t rolling);
    uint32_t encryptKeeloq(uint32_t data, uint64_t key);
};

#endif // KEELOQ_PROTOCOL_H
