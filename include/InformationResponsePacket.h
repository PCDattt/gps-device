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
    void PrintInformation();

    void ProcessPacketBodyForChecksum(boost::crc_32_type &result);
    uint16_t CalculateChecksum();
};

#endif