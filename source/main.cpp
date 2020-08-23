#include <iostream>

#include "GroupChatClient.hpp"
#include "GroupChatServer.hpp"

/*
 * option
 * pchat connect ip_protocol ip_address port_number
 * pchat host port_number
 */
int main(int argc, char * argv[]) {
    std::string mode = argv[1];

    if(mode == "connect" && argc == 5){
        int protocol = std::string(argv[2]) == "ipv4" ? 4 : 6;
        std::string ip = std::string(argv[3]);
        int port = std::stoi(std::string(argv[4]),nullptr,10);
        GroupChatClient groupChatClient = GroupChatClient(ip, protocol, port);
    }else if(mode == "host" && argc == 3) {
        int port = std::stoi(std::string(argv[2]),nullptr,10);
        GroupChatServer groupChatServer = GroupChatServer(port);
    }else if(mode == "secure"){

    }else if(mode == "help"){
        std::cout << "To connect to a chat server: " << std::endl;
        std::cout << "    pchat connect ip_protocol ip_address port_number" << std::endl;
        std::cout << "To create a chat server: " << std::endl;
        std::cout << "    pchat host port_number" << std::endl;
    }else{
        std::cout << "Invalid Arguments, please run pchat help for more information" << std::endl;
        exit(0);
    }
}