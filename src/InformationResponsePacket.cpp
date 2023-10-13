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

void InformationResponsePacket::PrintBodyInformation() {
    std::cout << "Received packet index: " << this->getReceivedPacketIndex() << std::endl;
}

void InformationResponsePacket::ProcessPacketBodyForChecksum(boost::crc_32_type &result) {
    result.process_bytes(std::to_string(receivedPacketIndex).c_str(), std::to_string(receivedPacketIndex).length());
}