#ifndef LOGINRESPONSEPACKET_H
#define LOGINRESPONSEPACKET_H

#include "BasePacket.h"

class LoginResponsePacket : public BasePacket{
private:
    uint16_t receivedPacketIndex;

public:
    void setReceivedPacketIndex(uint16_t receivedPacketIndex);
    uint16_t getReceivedPacketIndex() const;

    LoginResponsePacket();
    bool DeserializePacketBody(const std::vector<uint8_t>& buffer, size_t& offset);
    void PrintBodyInformation();

    void ProcessPacketBodyForChecksum(boost::crc_32_type &result);
};

#endif