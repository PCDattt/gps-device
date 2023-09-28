#include "../include/LoginPacket.h"

void LoginPacket::setUsername(const std::string& username) {
    this->username = username;
}

void LoginPacket::setPassword(const std::string& password) {
    this->password = password;
}

std::string LoginPacket::getUsername() const {
    return username;
}

std::string LoginPacket::getPassword() const {
    return password;
}

LoginPacket::LoginPacket() {
    this->setPacketId(2);
}

void LoginPacket::SerializePacketBody(std::vector<uint8_t>& buffer) const {
    SerializeString(buffer, username);
    SerializeString(buffer, password);
}

std::vector<uint8_t> LoginPacket::Serialize() const {
    std::vector<uint8_t> buffer;
    buffer.reserve(2 + 2 + this->getDeviceId().size() + 2 + this->getUsername().size() + this->getPassword().size() + 2 + 2);

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

void LoginPacket::ProcessPacketBodyForChecksum(boost::crc_32_type &result) {
    result.process_bytes(username.c_str(), username.length());
    result.process_bytes(password.c_str(), password.length());
}