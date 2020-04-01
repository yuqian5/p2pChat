//
// Created by Kerry Cao on 2020-03-29.
//

#ifndef PCHAT_P2P_HPP
#define PCHAT_P2P_HPP

#include "ChatInterface.hpp"


class P2P : private ChatInterface{

    P2P() : ChatInterface(std::string(), 0) {}
};


#endif //PCHAT_P2P_HPP
