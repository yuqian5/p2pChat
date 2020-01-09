#include <iostream>
#include <regex>
#include <ncurses.h>

#include "chatRX.h"
#include "chatTX.h"

bool checkIP(const std::string &IP_str) {
    try {
        if (regex_match(IP_str, std::regex(
                "\\b(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\b"))) { // validate ip
            return true;
        }
        throw std::domain_error("IP address inputted not valid");
    }
    catch (std::domain_error &em) {
        std::cerr << "Input Error: " << em.what() << std::endl;
        return false;
    }

}

int checkPort(const std::string &port_str) {
    int port;
    try {
        port = stoi(port_str);
        if (port < 1023 || port > 65535) {
            throw std::range_error("port number out of range 1024<=port<=65535");
        }
    }
    catch (const std::invalid_argument &em) {
        std::cerr << "Invalid argument: " << "port number must be a int in base 10" << std::endl;
        exit(1);
    }
    catch (const std::range_error &em) {
        return -1;
    }
    return port;
}

void getSetupInfo(std::string &ownip, std::string &ownport, std::string &targetip, std::string &targetport, std::string &name){
    std::cout << "RX IP (own IP address): ";
    std::cin >> ownip;
    std::cout << "RX Port: " ;
    std::cin >> ownport;

    std::cout << "TX IP (Target IP address): ";
    std::cin >> targetip;
    std::cout << "TX Port: " ;
    std::cin >> targetport;

    std::cout << "Username: ";
    std::cin >> name;
}

bool checkSetupInfo(std::string ownip, std::string ownport, std::string targetip, std::string targetport){
    if(!checkPort(ownport)){
        return false;
    }
    if(!checkPort(targetport)){
        return false;
    }
    if(!checkIP(ownip)){
        return false;
    }
    if(!checkIP(targetip)){
        return false;
    }

    return true;
}

int main(int argc, char ** argv) {
    std::string ownip;
    std::string ownport;
    std::string targetip;
    std::string targetport;
    std::string name;

    getSetupInfo(ownip, ownport, targetip, targetport, name);

    int txPipe[2];
    int rxPipe[2];
    pipe(txPipe);
    pipe(rxPipe);

    if(checkSetupInfo(ownip, ownport, targetip, targetport)){
        signal(SIGCHLD, SIG_IGN);
        int childPID1 = fork();
        if(childPID1){ //spawn rx process
            chatRX rx = chatRX(ownip, stoi(ownport, nullptr, 10));
        }
        signal(SIGCHLD, SIG_IGN);
        int childPID2 = fork();
        if(childPID2){ //spawn tx process
            // TODO start tx process
        }

    }

    return 0;
}