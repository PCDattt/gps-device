#include "../include/BasePacket.h"

void BasePacket::setStartMarker(uint16_t startMarker) {
    this->startMarker = startMarker;
}

void BasePacket::setPacketId(uint16_t packetId) {
    this->packetId = packetId;
}

void BasePacket::setDeviceId(const std::string& deviceId) {
    this->deviceId = deviceId;
}

void BasePacket::setPacketOrderIndex(uint16_t packetOrderIndex) {
    this->packetOrderIndex = packetOrderIndex;
}

void BasePacket::setChecksum(uint16_t checksum) {
    this->checksum = checksum;
}

void BasePacket::setEndMarker(uint16_t endMarker) {
    this->endMarker = endMarker;
}

uint16_t BasePacket::getStartMarker() const {
    return startMarker;
}

uint16_t BasePacket::getPacketId() const {
    return packetId;
}

std::string BasePacket::getDeviceId() const {
    return deviceId;
}

uint16_t BasePacket::getPacketOrderIndex() const {
    return packetOrderIndex;
}

uint16_t BasePacket::getChecksum() const {
    return checksum;
}

uint16_t BasePacket::getEndMarker() const {
    return endMarker;
}

// Helper function to serialize a uint16_t into the buffer
void BasePacket::SerializeUInt16(std::vector<uint8_t>& buffer, uint16_t value) const {
    buffer.push_back(static_cast<uint8_t>((value >> 8) & 0xFF));
    buffer.push_back(static_cast<uint8_t>(value & 0xFF));
}

// Helper function to serialize a uint32_t into the buffer
void BasePacket::SerializeUInt32(std::vector<uint8_t>& buffer, uint32_t value) const {
    buffer.push_back(static_cast<uint8_t>((value >> 24) & 0xFF));
    buffer.push_back(static_cast<uint8_t>((value >> 16) & 0xFF));
    buffer.push_back(static_cast<uint8_t>((value >> 8) & 0xFF));
    buffer.push_back(static_cast<uint8_t>(value & 0xFF));
}

// Helper function to serialize a string into the buffer
void BasePacket::SerializeString(std::vector<uint8_t>& buffer, const std::string& value) const {
    // Serialize the string length as a uint16_t
    SerializeUInt16(buffer, static_cast<uint16_t>(value.length()));

    // Serialize the string data
    for (char c : value) {
        buffer.push_back(static_cast<uint8_t>(c));
    }
}

// Helper function to deserialize a uint16_t from the buffer
bool BasePacket::DeserializeUInt16(const std::vector<uint8_t>& buffer, size_t& offset, uint16_t& value) const {
    if (offset + 2 > buffer.size()) return false;
    value = static_cast<uint16_t>(buffer[offset]) << 8;
    value |= static_cast<uint16_t>(buffer[offset + 1]);
    offset += 2;
    return true;
}

// Helper function to deserialize a uint32_t from the buffer
bool BasePacket::DeserializeUInt32(const std::vector<uint8_t>& buffer, size_t& offset, uint32_t& value) const {
    if (offset + 4 > buffer.size()) return false;
    value = static_cast<uint32_t>(buffer[offset]) << 24;
    value |= static_cast<uint32_t>(buffer[offset + 1]) << 16;
    value |= static_cast<uint32_t>(buffer[offset + 2]) << 8;
    value |= static_cast<uint32_t>(buffer[offset + 3]);
    offset += 4;
    return true;
}

// Helper function to deserialize a string from the buffer
bool BasePacket::DeserializeString(const std::vector<uint8_t>& buffer, size_t& offset, std::string& value) const {
    // Deserialize the string length as a uint16_t
    uint16_t length;
    DeserializeUInt16(buffer, offset, length);

    // Deserialize the string data
    for (size_t i = 0; i < length; ++i) {
        value += static_cast<char>(buffer[offset + i]);
    }
    offset += length;

    return true;
}

void BasePacket::FillStartingInformation() {
    startMarker = 0x0001;
    deviceId = "123456";
    packetOrderIndex = 1;
}

void BasePacket::FillEndingInformation() {
    checksum = CalculateChecksum();
    endMarker = 0x0004;
}

void BasePacket::FillInformation() {
    FillStartingInformation();
    FillBodyInformation();
    FillEndingInformation();
}

void BasePacket::SerializePacketStarting(std::vector<uint8_t>& buffer) const {
    SerializeUInt16(buffer, startMarker);
    SerializeUInt16(buffer, packetId);
    SerializeString(buffer, deviceId);
    SerializeUInt16(buffer, packetOrderIndex);
}

void BasePacket::SerializePacketEnding(std::vector<uint8_t>& buffer) const {
    SerializeUInt16(buffer, checksum);
    SerializeUInt16(buffer, endMarker);
}

std::vector<uint8_t> BasePacket::Serialize() const {
    std::vector<uint8_t> buffer;
    buffer = GetPacketBuffer();

    SerializePacketStarting(buffer);
    SerializePacketBody(buffer);
    SerializePacketEnding(buffer);

    return buffer;
}

bool BasePacket::DeserializePacketStarting(const std::vector<uint8_t>& buffer, size_t& offset) {
    if (!DeserializeUInt16(buffer, offset, startMarker)) return false;
    if (!DeserializeUInt16(buffer, offset, packetId)) return false;
    if (!DeserializeString(buffer, offset, deviceId)) return false;
    if (!DeserializeUInt16(buffer, offset, packetOrderIndex)) return false;
    return true;
}

bool BasePacket::DeserializePacketEnding(const std::vector<uint8_t>& buffer, size_t& offset) {
    if (!DeserializeUInt16(buffer, offset, checksum)) return false;
    if (!DeserializeUInt16(buffer, offset, endMarker)) return false;
    return true;
}

bool BasePacket::Deserialize(const std::vector<uint8_t>& buffer) {
    size_t offset = 0;
    if (!DeserializePacketStarting(buffer, offset)) return false;
    if (!DeserializePacketBody(buffer, offset)) return false;
    if (!DeserializePacketEnding(buffer, offset)) return false;

    return true;
}

void BasePacket::ProcessPacketStartingForChecksum(boost::crc_32_type &result) {
    result.process_bytes(&startMarker, sizeof(startMarker));
    result.process_bytes(&packetId, sizeof(packetId));
    result.process_bytes(deviceId.c_str(), deviceId.length());
    result.process_bytes(&packetOrderIndex, sizeof(packetOrderIndex));
}

uint16_t BasePacket::CalculateChecksum() {
    boost::crc_32_type result;

    ProcessPacketStartingForChecksum(result);
    ProcessPacketBodyForChecksum(result);

    uint32_t fullChecksum = result.checksum();
    return static_cast<uint16_t>(fullChecksum & 0xFFFF);
}

bool BasePacket::ValidateChecksum() {
    return this->CalculateChecksum() == this->getChecksum();
}