#ifndef LOGINPACKET_H
#define LOGINPACKET_H

#include "BasePacket.h"

class LoginPacket : public BasePacket{
public:
    std::string username;
    std::string password;

    void SerializePacketBody(std::vector<uint8_t>& buffer) const;
    std::vector<uint8_t> Serialize() const;
    void FillBodyInformation();
    void FillInformation();
};

#endif