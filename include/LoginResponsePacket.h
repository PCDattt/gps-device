#ifndef LOGINRESPONSEPACKET_H
#define LOGINRESPONSEPACKET_H

#include "BasePacket.h"

class LoginResponsePacket : public BasePacket{
public:
    uint16_t receivedPacketIndex;

    bool DeserializePacketBody(const std::vector<uint8_t>& buffer, size_t& offset);
    bool Deserialize(const std::vector<uint8_t>& buffer);
    void PrintInformation();
};

#endif