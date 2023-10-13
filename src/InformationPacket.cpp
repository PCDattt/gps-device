#include "../include/InformationPacket.h"

void InformationPacket::setLatitude(uint32_t latitude) {
    this->latitude = latitude;
}

void InformationPacket::setLongitude(uint32_t longitude) {
    this->longitude = longitude;
}

uint32_t InformationPacket::getLatitude() const {
    return latitude;
}

uint32_t InformationPacket::getLongitude() const {
    return longitude;
}

InformationPacket::InformationPacket() {
    this->setPacketId(0);
}

void InformationPacket::FillBodyInformation() {
    std::cout << "Enter latitude: ";
    std::cin >> latitude;
    std::cout << "Enter longitude: ";
    std::cin >> longitude;
}

std::vector<uint8_t> InformationPacket::GetPacketBuffer() const {
    std::vector<uint8_t> buffer;
    buffer.reserve(2 + 2 + this->getDeviceId().size() + 2 + 4 + 4 + 2 + 2);
    return buffer;
}

void InformationPacket::SerializePacketBody(std::vector<uint8_t>& buffer) const {
    SerializeUInt32(buffer, latitude);
    SerializeUInt32(buffer, longitude);
}

void InformationPacket::ProcessPacketBodyForChecksum(boost::crc_32_type &result) {
    result.process_bytes(std::to_string(latitude).c_str(), std::to_string(latitude).length());
    result.process_bytes(std::to_string(longitude).c_str(), std::to_string(longitude).length());
}

