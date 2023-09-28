#include "../include/LoginResponsePacket.h"

void LoginResponsePacket::setReceivedPacketIndex(uint16_t receivedPacketIndex) {
    this->receivedPacketIndex = receivedPacketIndex;
}

uint16_t LoginResponsePacket::getReceivedPacketIndex() const {
    return receivedPacketIndex;
}

LoginResponsePacket::LoginResponsePacket() {
    this->setPacketId(3);
}

bool LoginResponsePacket::DeserializePacketBody(const std::vector<uint8_t>& buffer, size_t& offset) {
    if (!DeserializeUInt16(buffer, offset, receivedPacketIndex)) return false;
    return true;
}

void LoginResponsePacket::PrintInformation() {
    std::cout << "Response packet startMarker: " << this->getStartMarker() << std::endl;
    std::cout << "Response packet packetId: " << this->getPacketId() << std::endl;
    std::cout << "Response packet deviceId: " << this->getDeviceId() << std::endl;
    std::cout << "Response packet packetOrderIndex: " << this->getPacketOrderIndex() << std::endl;
    std::cout << "Received packet index: " << this->getReceivedPacketIndex() << std::endl;
    std::cout << "Response packet checksum: " << this->getChecksum() << std::endl;
    std::cout << "Response packet endMarker: " << this->getEndMarker() << std::endl << std::endl;
}

void LoginResponsePacket::ProcessPacketBodyForChecksum(boost::crc_32_type &result) {
    result.process_bytes(&this->receivedPacketIndex, sizeof(this->receivedPacketIndex));
}