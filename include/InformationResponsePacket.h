#ifndef INFORMATIONRESPONSEPACKET_H
#define INFORMATIONRESPONSEPACKET_H

#include "BasePacket.h"

class InformationResponsePacket : public BasePacket{
    uint16_t receivedPacketIndex;

    bool DeserializePacketBody(const std::vector<uint8_t>& buffer, size_t& offset);
    bool Deserialize(const std::vector<uint8_t>& buffer);
    void PrintInformation();
};

#endif