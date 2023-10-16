#include "../include/PacketFactory.h"

int sendPacket(int &clientSocket, uint16_t packetId) {
    // Send and receive messages
        // Create packet
        BasePacket* packet = PacketFactory::GetPacket(packetId);
        packet->FillInformation();
        std::vector<uint8_t> serializedPacket = packet->Serialize();
        delete packet;
        packet = nullptr;

        // Send packet
        ssize_t bytesSent = send(clientSocket, serializedPacket.data(), serializedPacket.size(), 0);
        if (bytesSent < 0) {
            perror("Sending failed");
            return -1;
        }
        return 0;
}

int receivePacket(int &clientSocket, uint16_t packetId) {
    // Receive the response packet
        std::vector<uint8_t> receiveBuffer(1024);
        // memset(receiveBuffer.data(), 0, receiveBuffer.size());
        ssize_t bytesRead = recv(clientSocket, receiveBuffer.data(), receiveBuffer.size(), 0);
        if (bytesRead <= 0) {
            std::cerr << "Error receiving data" << std::endl;
            return -1;
        }
        receiveBuffer.resize(static_cast<size_t>(bytesRead));

         // Process the response packet 
        BasePacket* responsePacket;
        responsePacket = PacketFactory::GetPacket(packetId);
        responsePacket->Deserialize(receiveBuffer);
        std::cout << "Received response packet" << std::endl;
        if (responsePacket->ValidateChecksum()) {
            std::cout << "Checksum is correct" << std::endl;
            responsePacket->PrintInformation();
        }
        else {
            std::cout << "Checksum is incorrect" << std::endl;
        }

        delete responsePacket;
        responsePacket = nullptr;
        return 0;
}

int communicateServer(int &clientSocket) {
    // Send login packet to the server
    uint16_t check1 = sendPacket(clientSocket, 2);
    uint16_t check2 = receivePacket(clientSocket, 3);

    if(check1 == 0 && check2 == 0)
        {
            std::cout << "Login successful, Start to send information packet" << std::endl << std::endl;
            // Send information packet to the server per 20 seconds
            while(true)
            {
                sendPacket(clientSocket, 0);
                std::cout << "Sent information packet" << std::endl << std::endl;
                receivePacket(clientSocket, 1);
                sleep(20);
            }
        }
    else
        return -1;
    return 0;
}

int connectTcpServer() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating socket." << std::endl;
        return 1;
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Server's port number
    serverAddr.sin_addr.s_addr = inet_addr("192.168.22.105"); // Server's IP address

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error connecting to server." << std::endl;
        return 1;
    }

    std::cout << "Connected to the server." << std::endl << std::endl;

    communicateServer(clientSocket); 

    // Close the socket
    close(clientSocket);

    return 0;
}
