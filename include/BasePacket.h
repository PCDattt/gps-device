#ifndef BASEPACKET_H
#define BASEPACKET_H

#include "Header.h"

class BasePacket{
private:
    uint16_t startMarker;
    uint16_t packetId;
    std::string deviceId;
    uint16_t packetOrderIndex;
    uint16_t checksum;
    uint16_t endMarker;

public:
    void setStartMarker(uint16_t startMarker);
    void setPacketId(uint16_t packetId);
    void setDeviceId(const std::string& deviceId);
    void setPacketOrderIndex(uint16_t packetOrderIndex);
    void setChecksum(uint16_t checksum);
    void setEndMarker(uint16_t endMarker);

    uint16_t getStartMarker() const;
    uint16_t getPacketId() const;
    std::string getDeviceId() const;
    uint16_t getPacketOrderIndex() const;
    uint16_t getChecksum() const;
    uint16_t getEndMarker() const;

    void SerializeUInt16(std::vector<uint8_t>& buffer, uint16_t value) const;
    void SerializeUInt32(std::vector<uint8_t>& buffer, uint32_t value) const;
    void SerializeString(std::vector<uint8_t>& buffer, const std::string& value) const;
    bool DeserializeUInt16(const std::vector<uint8_t>& buffer, size_t& offset, uint16_t& value) const;
    bool DeserializeUInt32(const std::vector<uint8_t>& buffer, size_t& offset, uint32_t& value) const;
    bool DeserializeString(const std::vector<uint8_t>& buffer, size_t& offset, std::string& value) const;
    
    void SerializePacketStarting(std::vector<uint8_t>& buffer) const;
    virtual void SerializePacketBody(std::vector<uint8_t>& buffer) const {};
    void SerializePacketEnding(std::vector<uint8_t>& buffer) const;
    virtual std::vector<uint8_t> Serialize() const {};

    bool DeserializePacketStarting(const std::vector<uint8_t>& buffer, size_t& offset);
    virtual bool DeserializePacketBody(const std::vector<uint8_t>& buffer, size_t& offset) {};
    bool DeserializePacketEnding(const std::vector<uint8_t>& buffer, size_t& offset);
    virtual bool Deserialize(const std::vector<uint8_t>& buffer) {};

    void FillStartingInformation();
    virtual void FillBodyInformation() {};
    void FillEndingInformation();
    virtual void FillInformation() {};
    
    virtual void PrintInformation() {};
};

#endif