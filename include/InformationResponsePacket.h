#ifndef INFORMATIONRESPONSEPACKET_H
#define INFORMATIONRESPONSEPACKET_H

#include "BasePacket.h"

class InformationResponsePacket : public BasePacket{
private:
    uint16_t receivedPacketIndex;

public:
    void setReceivedPacketIndex(uint16_t receivedPacketIndex);
    uint16_t getReceivedPacketIndex() const;

    InformationResponsePacket();
    bool DeserializePacketBody(const std::vector<uint8_t>& buffer, size_t& offset);
    bool Deserialize(const std::vector<uint8_t>& buffer);
    void PrintInformation();
};

#endif