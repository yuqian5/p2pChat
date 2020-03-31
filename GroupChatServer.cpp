//
// Created by Kerry Cao on 2020-03-29.
//

#include <cstring>
#include "GroupChatServer.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
GroupChatServer::GroupChatServer(int port) {
    this->port = port;

    // configure socket
    socketSetup();

    // start listener
    listenerThread = std::thread(&GroupChatServer::listener, this);

    // start main
    main();
}

GroupChatServer::~GroupChatServer() {
    // shutdown sockets
    shutdown(listenfd, O_RDWR);
    close(listenfd);
    shutdown(connectfd, O_RDWR);
    close(connectfd);
    for(auto &fd : clientConnections){
        shutdown(fd, O_RDWR);
        close(fd);
    }
}

void GroupChatServer::socketSetup() {
    // init socket
    listenfd = socket(AF_INET6, SOCK_STREAM, 0);
    memset(&serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin6_family = AF_INET6;
    serverAddr.sin6_port = htons(port);
    serverAddr.sin6_addr = in6addr_any;

    // set to accept ipv4 protocol
    int no = 0;
    setsockopt(listenfd, IPPROTO_IPV6, IPV6_V6ONLY, (void *) &no, sizeof(no));

    //bind socket
    bind(listenfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    //listen
    listen(listenfd, BACKLOG);
}

void GroupChatServer::listener() {
    socklen_t addrSize = sizeof dataStorage;
    while(true){
        // accept new connections from
        int newConnection =  accept(this->listenfd, (struct sockaddr *) &this->dataStorage, &addrSize);

        clientConnections.emplace_back(newConnection);

        int c = clientConnections.back();
        clientHandlerThread.emplace_back(std::thread(clientHandler, std::ref(c), std::ref(messageQueue)));
    }
}

void GroupChatServer::clientHandler(int &connection, TSqueue<std::string> &messageQueue) {
    char readBuf[512];
    memset(readBuf, 0, sizeof(readBuf));

    while(true){
        recv(connection, readBuf, sizeof(readBuf), 0);
        std::string message = readBuf;

        messageQueue.enqueue(message);
    }
}

void GroupChatServer::main() {
    while(true){
        // get message
        std::string message = messageQueue.dequeue();
        std::cout << message << std::endl;

        // send to all client
        for(auto &connection : clientConnections){
            send(connection, message.c_str(), message.length(), 0);
        }
    }
}

#pragma clang diagnostic pop