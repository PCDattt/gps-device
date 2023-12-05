#ifndef INFORMATIONPACKET_H
#define INFORMATIONPACKET_H

#include "BasePacket.h"

class InformationPacket : public BasePacket{
private: 
    int32_t latitude;
    int32_t longitude;

public:
    void setLatitude(int32_t latitude);
    void setLongitude(int32_t longitude);

    int32_t getLatitude() const;
    int32_t getLongitude() const;

    InformationPacket();
    void FillBodyInformation();
    std::vector<uint8_t> GetPacketBuffer() const;
    void SerializePacketBody(std::vector<uint8_t>& buffer) const;
    
    void ProcessPacketBodyForChecksum(boost::crc_32_type &result);
};

#endif