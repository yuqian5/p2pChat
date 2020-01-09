#ifndef P2PCHAT_CHATRX_H
#define P2PCHAT_CHATRX_H

#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <cstdlib>
#include <utility>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <netdb.h>
#include <chrono>

#define BACKLOG 10

class chatRX {
public:
    chatRX(std::string ownip, int ownport);
    ~chatRX();

private:

    int main();
    void socketSetup();
    void receive();
    void terminate();

    std::string ownIP;
    int ownPort;

    int rxSocket, newRxSocket;
    struct sockaddr_in address;
    struct sockaddr_storage receive_storage;
};




#endif //P2PCHAT_CHATRX_H
