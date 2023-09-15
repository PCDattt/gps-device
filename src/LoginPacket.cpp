#include "../include/LoginPacket.h"

void LoginPacket::SerializePacketBody(std::vector<uint8_t>& buffer) const {
    SerializeString(buffer, username);
    SerializeString(buffer, password);
}

std::vector<uint8_t> LoginPacket::Serialize() const {
    std::vector<uint8_t> buffer;
    buffer.reserve(2 + 2 + deviceId.size() + 2 + username.size() + password.size() + 2 + 2);

    SerializePacketStarting(buffer);
    SerializePacketBody(buffer);
    SerializePacketEnding(buffer);

    return buffer;
}

void LoginPacket::FillBodyInformation() {
    username = "username";
    password = "password";
}

void LoginPacket::FillInformation() {
    FillStartingInformation();
    FillBodyInformation();
    FillEndingInformation();
}