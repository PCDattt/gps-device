#ifndef LOGINRESPONSEPACKET_H
#define LOGINRESPONSEPACKET_H

#include "ResponsePacket.h"

class LoginResponsePacket : public ResponsePacket{
private:
    uint16_t receivedPacketIndex;

public:
    LoginResponsePacket();
};

#endif