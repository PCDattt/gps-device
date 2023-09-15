#ifndef PACKETFACTORY_H
#define PACKETFACTORY_H

#include "BasePacket.h"
#include "InformationPacket.h"
#include "InformationResponsePacket.h"
#include "LoginPacket.h"
#include "LoginResponsePacket.h"

class PacketFactory{
public:
    enum PacketType
    {
        informationPacket = 0,
        informationResponsePacket = 1,
        loginPacket = 2,
        loginResponsePacket = 3
    };
    static BasePacket* GetPacket(uint16_t packetId);
};

#endif