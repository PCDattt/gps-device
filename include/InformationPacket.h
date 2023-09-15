#ifndef INFORMATIONPACKET_H
#define INFORMATIONPACKET_H

#include "BasePacket.h"

class InformationPacket : public BasePacket{
public: 
    uint32_t latitude;
    uint32_t longitude;

    void SerializePacketBody(std::vector<uint8_t>& buffer) const;
    std::vector<uint8_t> Serialize() const;
    void FillBodyInformation();
    void FillInformation();
};

#endif