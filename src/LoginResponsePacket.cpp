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

void LoginResponsePacket::PrintBodyInformation() {
    std::cout << "Received packet index: " << this->getReceivedPacketIndex() << std::endl;
}

void LoginResponsePacket::ProcessPacketBodyForChecksum(boost::crc_32_type &result) {
    result.process_bytes(std::to_string(receivedPacketIndex).c_str(), std::to_string(receivedPacketIndex).length());
}