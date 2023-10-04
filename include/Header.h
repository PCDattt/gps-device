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
#include <boost/crc.hpp>

int sendPacket(int &clientSocket);
int connectTcpServer();

#endif

