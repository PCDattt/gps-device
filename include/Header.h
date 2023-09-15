#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdint>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <openssl/md5.h>

int connectTcpServer();
uint16_t CalculateChecksum(const std::vector<uint8_t>& buffer);
bool ValidateChecksum(std::vector<uint8_t> buffer, uint16_t& checksum);

#endif

