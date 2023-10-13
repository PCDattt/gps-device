#include "../include/PacketFactory.h"

int sendPacket(int &clientSocket) {
    int choice;
    // Send and receive messages
    while (true) {
        std::cout << "Enter 0 to disconnect " << std::endl;
        std::cout << "Enter 1 to send information packet " << std::endl;
        std::cout << "Enter 2 to send login packet " << std::endl;
        std::cin >> choice;
        if(choice == 0) break;
        uint16_t packetId;
        if (choice == 1) packetId = 0;
        else packetId = 2;

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
            return 1;
        }
        else {
            std::cout << "Sent information packet successfully" << std::endl;
            std::cout << "Sent " << bytesSent << " bytes" << std::endl << std::endl;
        }
        
        // Receive the response packet
        std::vector<uint8_t> receiveBuffer(1024);
        // memset(receiveBuffer.data(), 0, receiveBuffer.size());
        ssize_t bytesRead = recv(clientSocket, receiveBuffer.data(), receiveBuffer.size(), 0);
        if (bytesRead <= 0) {
            std::cerr << "Error receiving data" << std::endl;
            break;
        }
        receiveBuffer.resize(static_cast<size_t>(bytesRead));

         // Process the response packet 
        BasePacket* responsePacket;
        responsePacket = PacketFactory::GetPacket(packetId + 1);
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
    }
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

    std::cout << "Connected to the server." << std::endl;

    // Send data to the server
    sendPacket(clientSocket);

    // Close the socket
    close(clientSocket);

    return 0;
}
