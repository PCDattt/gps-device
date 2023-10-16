#ifndef INFORMATIONRESPONSEPACKET_H
#define INFORMATIONRESPONSEPACKET_H

#include "ResponsePacket.h"

class InformationResponsePacket : public ResponsePacket{
private:
    uint16_t receivedPacketIndex;

public:
    InformationResponsePacket();
};

#endif