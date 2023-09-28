#ifndef LOGINPACKET_H
#define LOGINPACKET_H

#include "BasePacket.h"

class LoginPacket : public BasePacket{
private:
    std::string username;
    std::string password;

public:
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);

    std::string getUsername() const;
    std::string getPassword() const;

    LoginPacket();
    void SerializePacketBody(std::vector<uint8_t>& buffer) const;
    std::vector<uint8_t> GetPacketBuffer() const;
    void FillBodyInformation();

    void ProcessPacketBodyForChecksum(boost::crc_32_type &result);
    uint16_t CalculateChecksum();
};

#endif