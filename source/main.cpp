#include <iostream>

#include "GroupChatClient.hpp"
#include "GroupChatServer.hpp"
#include "P2P.hpp"

int main(int argc, char * argv[]) {
    /*std::string mode = argv[1];

    if(mode == "-gc"){
        std::string title = "Chatting on server " + std::string(argv[2]);
        std::string ip = std::string(argv[2]);
        std::string name = std::string(argv[3]);

        GroupChatClient groupChatClient = GroupChatClient(ip,"ipv4",8000);
    }else if(mode == "-gs") {
        GroupChatServer groupChatServer = GroupChatServer(8000);
    }*/

    P2P p = P2P();
    p.constructFriendlyKey("-----BEGIN RSA PUBLIC KEY-----\n"
                           "MIICCgKCAgEAvpsH9oVJP7qEKWfsVf56qw8Woo8C+T2JveYltrmuMmV659A0XC7X\n"
                           "ZCrB1lTjMlKu+0Da4IhCSGIf72J8SxxAVU/R9ppb+uRRrjsA/EGD+YCuMRsE1cum\n"
                           "ueeu7NqWIsowJCgmPo8gNgfOJP9fA4NYuiXBxj3ZazEu3PFphp+GLlAlDavUAelo\n"
                           "21Y69JF8ttOsaKnPUVqzf28R4dhBXE/LeCxtl64OjmkyoXNM1wc+s4L/Wc40Toyu\n"
                           "2OCmmjBds3ZI1sfO6zpIPC0WVubKx7E359/PZSsUr9fzWmuFWMIH7TT2RRZpgOAi\n"
                           "Syq8sb8yTo+yGSH0+RwKBj7tBL3lr2HmeEik3rcMBtDZje/YVt+TkMwZHUbKOWvc\n"
                           "K7+YBzkE4DmROe6LH54yKJIrvWYeClWTmUZhlTrReSSNx72OQWci6f5v4z7+yuFL\n"
                           "QElWGsyWLTvEbs1obmJICDkqE9xrlpZr0r1XY3Fcld3V1Gy0Ni1wEhqQM7IZT0SJ\n"
                           "TfB+grIhQdaTQAa+cuIiI0MV9h8aV5XkODxPrrgs7urW1CSVEE4Di+UdQ/es6vsK\n"
                           "VxzYIjaIdCMAB0sbLAY1b28Ah7YpdU/iYZ4DYVFO8zlHQL4BmMZ64Bc0cnSN+LbR\n"
                           "TtlK4XeTKHqrzkPDQGuRvAxXaY1bCAheNzp1i4ga9LzcBTSCbbCled0CAwEAAQ==\n"
                           "-----END RSA PUBLIC KEY-----");
}