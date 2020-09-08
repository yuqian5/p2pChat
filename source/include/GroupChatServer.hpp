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
#include <cstring>
#include <vector>
#include <algorithm>

#include "TSQueue.hpp"

#define BACKLOG 20

class GroupChatServer {
public:
    explicit GroupChatServer(int port);
    ~GroupChatServer();

private:
    void initializeSocket();

    [[noreturn]] void connectionBroadcaster();

    [[noreturn]] void newConnectionDispatcher();
    static void clientConnectionHandler(int &connection,
                                        TSqueue<std::string> &messageQueue,
                                        std::vector<int> &clientConnections);

    void serverMain();

    int listenfd = 0;
    int connectfd = 0;
    struct sockaddr_in6 serverAddr;
    struct sockaddr_storage dataStorage;

    int port;

    std::thread connectionBroadcasterThread;
    std::thread connectionListenerThread;
    std::vector<std::thread> clientHandlers;

    std::vector<int> clientConnections;

    TSqueue<std::string> messageQueue;

    std::vector<std::string> chatHistory;
};


#endif //PCHAT_GROUPCHATSERVER_HPP
