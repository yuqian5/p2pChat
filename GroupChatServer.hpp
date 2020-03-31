//
// Created by Kerry Cao on 2020-03-29.
//

#ifndef PCHAT_GROUPCHATSERVER_HPP
#define PCHAT_GROUPCHATSERVER_HPP

#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <thread>
#include <vector>

#include "TSQueue.hpp"

#define BACKLOG 20
#define TIMEOUT 60

class GroupChatServer {
public:
    GroupChatServer(int port);
    ~GroupChatServer();

private:
    void main();
    void socketSetup();
    void listener();
    static void clientHandler(int &connection, TSqueue<std::string> &messageQueue);

    int listenfd = 0;
    int connectfd = 0;
    struct sockaddr_in6 serverAddr;
    struct sockaddr_storage dataStorage;

    int port;

    std::thread listenerThread;
    std::vector<std::thread> clientHandlerThread;

    std::vector<int> clientConnections;

    TSqueue<std::string> messageQueue;
};


#endif //PCHAT_GROUPCHATSERVER_HPP
