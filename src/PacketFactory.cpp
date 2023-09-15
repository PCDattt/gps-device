#include "../include/PacketFactory.h"

BasePacket* PacketFactory::GetPacket(uint16_t packetId) {
    if (packetId == loginPacket) return new LoginPacket();
    else if (packetId == loginResponsePacket) return new LoginResponsePacket();
    else if (packetId == informationPacket) return new InformationPacket();
    else if (packetId == informationResponsePacket) return new InformationResponsePacket();
    else return nullptr;
}