//
// Created by Kerry Cao on 2020-03-29.
//

#ifndef PCHAT_CHATINTERFACE_HPP
#define PCHAT_CHATINTERFACE_HPP

#include <ncurses.h>
#include <iostream>
#include <vector>
#include <functional>
#include <cstring>
#include <utility>

class ChatInterface {
public:
    ChatInterface(std::string title, int inputBoxSize);
    ~ChatInterface();

    void initWindow();

    void printMessage(std::string &senderName, std::string &message);
    std::string getInput();

protected:
    int inputWindowHeight;

    std::string title;

    bool exitProgram;

private:
    void clearInputField();

    void gotoInputField();

    void drawInterface();

    int maxRow;
    int maxCol;

    int currentRow;

    WINDOW *displayWindow;
    WINDOW *inputWindow;
};


#endif //PCHAT_CHATINTERFACE_HPP
