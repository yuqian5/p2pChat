//
// Created by Kerry Cao on 2020-03-29.
//

#include "GroupChatClient.hpp"

GroupChatClient::GroupChatClient(std::string title,
                                 int inputBoxSize,
                                 std::string ip,
                                 std::string protoc,
                                 std::string identity,
                                 int port)
                                 :ChatInterface(std::move(title), inputBoxSize) {

    this->ip = std::move(ip);
    this->protoc = std::move(protoc);
    this->port = port;

    this->identity = std::move(identity);

    //connectToServer();

    initWindow();

    inputThread = std::thread(&GroupChatClient::inputHandler, this);
    outputThread = std::thread(&GroupChatClient::outputHandler, this);
    monitorThread = std::thread(&GroupChatClient::monitor, this);
}

GroupChatClient::~GroupChatClient() = default;

void GroupChatClient::connectToServer() {
    if (protoc == "ipv4") { // ipv4
        // initialize socket
        connectfd = socket(AF_INET, SOCK_STREAM, 0);
        memset(&serverAddr4, 0, sizeof(serverAddr4));

        serverAddr4.sin_family = AF_INET;
        serverAddr4.sin_port = htons(port);
        if (inet_pton(AF_INET, ip.c_str(), &(serverAddr4.sin_addr)) != 1) {
            std::cerr << "ERROR: inet_pton failed" << std::endl;
            exit(1);
        }
        connectNow(std::ref(serverAddr4), std::ref(connectfd));
    } else { // ipv6
        // initialize socket
        connectfd = socket(AF_INET6, SOCK_STREAM, 0);
        memset(&serverAddr6, 0, sizeof(serverAddr6));

        serverAddr6.sin6_family = AF_INET6;
        serverAddr6.sin6_port = htons(port);
        if (inet_pton(AF_INET6, ip.c_str(), &(serverAddr6.sin6_addr)) != 1) {
            std::cerr << "ERROR: inet_pton failed" << std::endl;
            exit(1);
        }
        // connect
        connectNow(std::ref(serverAddr6), std::ref(connectfd));
    }
}

void GroupChatClient::connectNow(sockaddr_in &serverAddr4, int &connectfd) {
    if (connect(connectfd, (struct sockaddr *) &serverAddr4, sizeof(serverAddr4)) < 0) {
        std::cerr << "Server Not Found\n";
        shutdown(connectfd, O_RDWR);
        close(connectfd);
        exit(0);
    }
}

void GroupChatClient::connectNow(sockaddr_in6 &serverAddr6, int &connectfd) {
    if (connect(connectfd, (struct sockaddr *) &serverAddr6, sizeof(serverAddr4)) < 0) {
        std::cerr << "Server Not Found\n";
        shutdown(connectfd, O_RDWR);
        close(connectfd);
        exit(0);
    }
}

void GroupChatClient::inputHandler() {
    while(!exitProgram){
        SerializableMessagePackage smp = SerializableMessagePackage(identity, getInput());
        std::string serializedMessage = smp.serialize();
        send(connectfd, serializedMessage.c_str(), serializedMessage.length(), 0);
    }
}

void GroupChatClient::outputHandler() {
    char readBuf[512];

    while(!exitProgram){
        recv(connectfd, readBuf, sizeof(readBuf), 0);
        std::string serializedMessage = readBuf;
        memset(readBuf, 0, sizeof(readBuf));
        SerializableMessagePackage smp =  SerializableMessagePackage::deserialize(serializedMessage);
        printMessage(smp.getIdentity(), smp.getMessage());
    }
}

void GroupChatClient::monitor() {
    while(!exitProgram){
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    shutdown(connectfd, O_RDWR);
    close(connectfd);
    exit(0);
}
