#include "../include/ResponsePacket.h"

void ResponsePacket::setReceivedPacketIndex(uint16_t receivedPacketIndex) {
    this->receivedPacketIndex = receivedPacketIndex;
}

uint16_t ResponsePacket::getReceivedPacketIndex() const {
    return receivedPacketIndex;
}

bool ResponsePacket::DeserializePacketBody(const std::vector<uint8_t>& buffer, size_t& offset) {
    if (!DeserializeUInt16(buffer, offset, receivedPacketIndex)) return false;
    return true;
}

void ResponsePacket::PrintBodyInformation() {
    std::cout << "Received packet index: " << this->getReceivedPacketIndex() << std::endl;
}

void ResponsePacket::ProcessPacketBodyForChecksum(boost::crc_32_type &result) {
    result.process_bytes(std::to_string(receivedPacketIndex).c_str(), std::to_string(receivedPacketIndex).length());
}