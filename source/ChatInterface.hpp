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

#define INPUTWINDOWHEIGHT 6

class ChatInterface {
public:
    ChatInterface();
    ~ChatInterface();

    void initWindow();

    void drawTitle(std::string title);

    void printMessage(std::string &senderName, std::string &message);
    std::string getInput();

protected:
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
