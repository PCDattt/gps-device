#include "../include/InformationResponsePacket.h"

bool InformationResponsePacket::DeserializePacketBody(const std::vector<uint8_t>& buffer, size_t& offset) {
    if (!DeserializeUInt16(buffer, offset, receivedPacketIndex)) return false;
    return true;
}

bool InformationResponsePacket::Deserialize(const std::vector<uint8_t>& buffer) {
    size_t offset = 0;
    if (!DeserializePacketStarting(buffer, offset)) return false;
    if (!DeserializePacketBody(buffer, offset)) return false;
    if (!DeserializePacketEnding(buffer, offset)) return false;

    return true;
}

void InformationResponsePacket::PrintInformation() {
    std::cout << "Response packet startMarker: " << startMarker << std::endl;
    std::cout << "Response packet packetId: " << packetId << std::endl;
    std::cout << "Response packet deviceId: " << deviceId << std::endl;
    std::cout << "Response packet packetOrderIndex: " << packetOrderIndex << std::endl;
    std::cout << "Received packet index: " << receivedPacketIndex << std::endl;
    std::cout << "Response packet checksum: " << checksum << std::endl;
    std::cout << "Response packet endMarker: " << endMarker << std::endl << std::endl;
}