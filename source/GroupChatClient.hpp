//
// Created by Kerry Cao on 2020-03-29.
//

#ifndef PCHAT_GROUPCHATCLIENT_HPP
#define PCHAT_GROUPCHATCLIENT_HPP

#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utility>
#include <thread>

#include "ChatInterface.hpp"
#include "SerializableMessagePackage.hpp"

class GroupChatClient : private ChatInterface{
public:
    GroupChatClient(std::string title, int inputBoxSize, std::string ip, std::string protoc, std::string identity, int port);
    ~GroupChatClient();

private:
    void connectToServer();
    static void connectNow(sockaddr_in6 &serverAddr6, int &connectfd);
    static void connectNow(sockaddr_in &serverAddr4, int &connectfd);

    void inputHandler();
    void outputHandler();
    void monitor();

    int connectfd;
    struct sockaddr_in6 serverAddr6;
    struct sockaddr_in serverAddr4;

    std::thread inputThread;
    std::thread outputThread;
    std::thread monitorThread;

    std::string ip;
    std::string protoc;
    int port;
    std::string identity;
};


#endif //PCHAT_GROUPCHATCLIENT_HPP
