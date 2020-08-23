//
// Created by Kerry Cao on 2020-03-29.
//

#include "GroupChatServer.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
GroupChatServer::GroupChatServer(int port) {
    this->port = port;

    // configure socket
    initializeSocket();

    // start newConnectionDispatcher
    connectionListenerThread = std::thread(&GroupChatServer::newConnectionDispatcher, this);

    // start connectionBroadcaster
    connectionBroadcasterThread = std::thread(&GroupChatServer::connectionBroadcaster, this);

    serverMain();
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

void GroupChatServer::initializeSocket() {
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

[[noreturn]] void GroupChatServer::newConnectionDispatcher() {
    socklen_t addrSize = sizeof dataStorage;
    while(true){
        // accept new connections from
        int newConnection = accept(this->listenfd, (struct sockaddr *) &this->dataStorage, &addrSize);
        if(newConnection == -1){ // failed to accept, try again
            continue;
        }
        clientConnections.emplace_back(newConnection);

        int c = clientConnections.back();
        clientHandlers.emplace_back(std::thread(clientConnectionHandler,
                                                std::ref(c),
                                                std::ref(messageQueue),
                                                std::ref(clientConnections)
                                                ));
    }
}

void GroupChatServer::clientConnectionHandler(int &connection,
                                              TSqueue<std::string> &messageQueue,
                                              std::vector<int> &clientConnections) {
    char readBuf[512];
    memset(readBuf, 0, sizeof(readBuf));

    int connectionCopy = connection;

    while(true){
        if(recv(connectionCopy, readBuf, sizeof(readBuf), 0) == 0){ // connection terminated
            clientConnections.erase(std::remove(clientConnections.begin(),
                                                clientConnections.end(), connectionCopy), clientConnections.end()); // remove connection from broadcast list
            shutdown(connectionCopy, O_RDWR);
            close(connectionCopy);
            break;
        }
        std::string message = readBuf;
        memset(readBuf, 0, sizeof(readBuf));

        messageQueue.enqueue(message);
    }
}

[[noreturn]] void GroupChatServer::connectionBroadcaster() {
    while(true){
        // get message
        std::string message = messageQueue.dequeue();
        chatHistory.emplace_back(message);

        std::string size = std::to_string(message.length());
        for(int i = size.length() ; i < 5; i++){
            size.insert(size.begin(), '0');
        }

        // send to all client
        for(auto &connection : clientConnections){
            if(send(connection, size.c_str(), 5, 0) == 0){
                clientConnections.erase(std::find(clientConnections.begin(), clientConnections.end(), connection));
            }
            if(send(connection, message.c_str(), message.length(), 0) == 0){
                clientConnections.erase(std::find(clientConnections.begin(), clientConnections.end(), connection));
            }
        }
    }
}

void GroupChatServer::serverMain() {
    std::cout << "Server Running" << std::endl;

    std::string input;
    while (true) {
        std::cout << "Command: ";
        if (getline(std::cin, input)) {
            if(input == "exit"){
                connectionBroadcasterThread.detach();
                connectionBroadcasterThread.~thread();
                connectionListenerThread.detach();
                connectionListenerThread.~thread();
                for(auto &thread : clientHandlers){
                    thread.detach();
                    thread.~thread();
                }
                shutdown(listenfd, O_RDWR);
                close(listenfd);
                shutdown(connectfd, O_RDWR);
                close(connectfd);
                for(auto &fd : clientConnections){
                    shutdown(fd, O_RDWR);
                    close(fd);
                }
                exit(0);
            }else if(input == "history"){
                for(auto &history : chatHistory){
                    std::cout << history << std::endl;
                }
            }
        }
    }
}

#pragma clang diagnostic pop