#include "../include/InformationResponsePacket.h"

void InformationResponsePacket::setReceivedPacketIndex(uint16_t receivedPacketIndex) {
    this->receivedPacketIndex = receivedPacketIndex;
}

uint16_t InformationResponsePacket::getReceivedPacketIndex() const {
    return receivedPacketIndex;
}

InformationResponsePacket::InformationResponsePacket() {
    this->setPacketId(1);
}

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
    std::cout << "Response packet startMarker: " << this->getStartMarker() << std::endl;
    std::cout << "Response packet packetId: " << this->getPacketId() << std::endl;
    std::cout << "Response packet deviceId: " << this->getDeviceId() << std::endl;
    std::cout << "Response packet packetOrderIndex: " << this->getPacketOrderIndex() << std::endl;
    std::cout << "Received packet index: " << this->getReceivedPacketIndex() << std::endl;
    std::cout << "Response packet checksum: " << this->getChecksum() << std::endl;
    std::cout << "Response packet endMarker: " << this->getEndMarker() << std::endl << std::endl;
}

void InformationResponsePacket::ProcessPacketBodyForChecksum(boost::crc_32_type &result) {
    result.process_bytes(&this->receivedPacketIndex, sizeof(this->receivedPacketIndex));
}