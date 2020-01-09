//
// Created by Kerry Cao on 2019-12-26.
//

#include "chatRX.h"
void chatRX::terminate() {
    chatRX::~chatRX();
}

chatRX::chatRX(std::string ownip, int ownport) {
    ownIP = ownip;
    ownPort = ownport;

    socketSetup();
    main();
}

chatRX::~chatRX(){
    shutdown(rxSocket, 0);
    shutdown(newRxSocket, 0);
    exit(0);
}

void chatRX::socketSetup() {
    //struct setup
    address.sin_family = AF_INET;
    address.sin_port = htons(ownPort);
    if (inet_pton(AF_INET, ownIP.c_str(), &(address.sin_addr)) != 1) {
        std::cerr << "inet_pton failed" << std::endl;
        exit(1);
    }

    //init socket
    rxSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (rxSocket < 0) {
        std::cerr << "socket() failed" << std::endl;
        exit(1);
    }

    //bind socket
    if (bind(rxSocket, (struct sockaddr *) &address, sizeof(address)) < 0) {
        std::cerr << "bind failed" << std::endl;
        exit(1);
    }

    //listen
    if (listen(rxSocket, BACKLOG) != 0) {
        std::cerr << "listen failed" << std::endl;
        exit(1);
    }

    //accept
    socklen_t addr_size = sizeof receive_storage;
    newRxSocket = accept(rxSocket, (struct sockaddr *) &receive_storage, &addr_size);
    std::cout << "Socket Connected" << std::endl;
}

void chatRX::receive() {
    char newMsg[2048]; // buffer for new message
    int length;

    // get new message length
    recv(newRxSocket, newMsg, 4, 0);
    try { length = std::stoi(newMsg, nullptr, 10); }
    catch (std::invalid_argument &e) {
        std::cerr << "error converting message size" << std::endl;
        exit(1);
    }
    memset(newMsg, 0, 5); // reset newMsg

    // get new message
    recv(newRxSocket, newMsg, length, 0);
    std::cout << newMsg << std::endl; // print message
    flush(std::cout); // flush output buffer
    memset(newMsg, 0, length+4); // reset newMsg
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
int chatRX::main() {
    signal(SIGINT, chatRX::terminate());

    while(true){
        // TODO: check pipe for shutdown
        // if no shutdown, poll new msg

        usleep(1000);
        receive();
    }
}
#pragma clang diagnostic pop

