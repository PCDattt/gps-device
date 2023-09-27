#ifndef INFORMATIONPACKET_H
#define INFORMATIONPACKET_H

#include "BasePacket.h"

class InformationPacket : public BasePacket{
private: 
    uint32_t latitude;
    uint32_t longitude;

public:
    void setLatitude(uint32_t latitude);
    void setLongitude(uint32_t longitude);

    uint32_t getLatitude() const;
    uint32_t getLongitude() const;

    InformationPacket();
    void SerializePacketBody(std::vector<uint8_t>& buffer) const;
    std::vector<uint8_t> Serialize() const;
    void FillBodyInformation();
    void FillInformation();
};

#endif