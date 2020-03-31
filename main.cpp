#include <iostream>

#include "GroupChatClient.hpp"
#include "GroupChatServer.hpp"
#include "P2P.hpp"

int main(int argc, char * argv[]) {
    std::string mode = argv[1];

    if(mode == "-gc"){
        std::string title = "Chatting on server " + std::string(argv[2]);
        std::string ip = std::string(argv[2]);
        std::string name = std::string(argv[3]);

        GroupChatClient groupChatClient = GroupChatClient(title,6, ip,"ipv4",name,8000);
    }else if(mode == "-gs") {
        GroupChatServer groupChatServer = GroupChatServer(8000);
    }
}