#include "../include/InformationPacket.h"

void InformationPacket::SerializePacketBody(std::vector<uint8_t>& buffer) const {
    SerializeUInt32(buffer, latitude);
    SerializeUInt32(buffer, longitude);
}

std::vector<uint8_t> InformationPacket::Serialize() const {
    std::vector<uint8_t> buffer;
    buffer.reserve(2 + 2 + deviceId.size() + 2 + 4 + 4 + 2 + 2);

    SerializePacketStarting(buffer);
    SerializePacketBody(buffer);
    SerializePacketEnding(buffer);

    return buffer;
}

void InformationPacket::FillBodyInformation() {
    latitude = 123;
    longitude = 456;
}

void InformationPacket::FillInformation() {
    FillStartingInformation();
    FillBodyInformation();
    FillEndingInformation();
}

