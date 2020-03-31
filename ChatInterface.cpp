//
// Created by Kerry Cao on 2020-03-29.
//

#include "ChatInterface.hpp"

ChatInterface::ChatInterface(std::string title, int inputBoxSize) {
    this->currentRow = 0;
    this->title = std::move(title);
    this->inputWindowHeight = inputBoxSize;
    this->exitProgram = false;
}

ChatInterface::~ChatInterface() {
    endwin();
}

void ChatInterface::initWindow() {
    // initialize screen
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();

    // get screen size
    this->maxRow = getmaxy(stdscr) - 1;
    this->maxCol = getmaxx(stdscr) - 1;

    // draw interface
    drawInterface();

    // create display window border
    WINDOW *temp = newwin(maxRow-1-inputWindowHeight, maxCol-1,1,1); // create
    box(temp, 0 , 0); // draw box
    wrefresh(temp); // refresh

    // create display window
    displayWindow = newwin(maxRow-3-inputWindowHeight, maxCol-3,2,2); // create
    wrefresh(displayWindow); // refresh
    scrollok(displayWindow, TRUE); // allow scroll

    // create input window
    inputWindow = newwin(inputWindowHeight-1, maxCol-1, maxRow-inputWindowHeight+1, 1); // create
    box(inputWindow, 0 , 0); // draw box
    wrefresh(inputWindow); // refresh
}

std::string ChatInterface::getInput() {
    gotoInputField();

    // initialize read buffer
    char readBuf[256];
    int readBufIndex = 0;
    memset(readBuf, 0, sizeof(readBuf));

    while(true){
        char c = getch();

        if(c == 8 || c == 127){ // del or backspace
            if(readBufIndex > 0){
                wmove(inputWindow,1,readBufIndex);
                waddch(inputWindow, 32);
                wmove(inputWindow,1,readBufIndex);

                readBufIndex -= 1;
                readBuf[readBufIndex] = 0;
            }
        }else if(c == 10){
            if(readBuf[0] != 0){ // if new message not empty
                clearInputField();
                wrefresh(inputWindow);

                return std::string(readBuf);
            }
        }else if(c == 3){
            exitProgram = true;
        }else{
            waddch(inputWindow, c);
            readBuf[readBufIndex] = c;
            readBufIndex += 1;
        }
        wrefresh(inputWindow);
    }
}

void ChatInterface::clearInputField() {
    for(int i = 1; i < inputWindowHeight-2; i++){
        wmove(inputWindow, i, 1);
        for(int j  = 1; j < maxCol - 2; j++){
            waddch(inputWindow, 32);
        }
    }
    wrefresh(inputWindow);
}

void ChatInterface::gotoInputField() {
    wmove(inputWindow, 1, 1);
    wrefresh(inputWindow);
}

void ChatInterface::drawInterface() {
    // update screen size
    maxRow = getmaxy(stdscr) - 1;
    maxCol = getmaxx(stdscr) - 1;

    // draw border
    for(int i = 0; i < maxCol; i++){
        move(0,i);
        addch('-');
        move(maxRow,i);
        addch('-');
    }
    for(int i = 0; i < maxRow; i++){
        move(i, 0);
        addch('|');
        move(i, maxCol);
        addch('|');
    }

    // draw corner
    mvaddch(0,0,'+');
    mvaddch(maxRow,0,'+');
    mvaddch(0,maxCol,'+');
    mvaddch(maxRow, maxCol,'+');

    // draw text box separator line
    for(int i = 0; i < maxCol; i++){
        move(maxRow-inputWindowHeight,i);
        addch('-');
    }
    mvaddch(maxRow-inputWindowHeight, 0, '+');
    mvaddch(maxRow-inputWindowHeight, maxCol, '+');
    move(maxRow-inputWindowHeight,maxCol/2-5);
    printw("NEW MESSAGE");

    // draw title
    move(0, maxCol/2-title.length()/2);
    printw(title.c_str());

    // refresh display
    refresh();
}

void ChatInterface::printMessage(std::string &senderName, std::string &message) {
    if(currentRow > getmaxy(displayWindow)*0.8){
        wscrl(displayWindow,5);
        currentRow -= 5;
    }

    wmove(displayWindow, currentRow, 1);

    int lineUsed = 1;
    int countOnCurrentLine = 0;

    // print sender info
    std::string sender = senderName + ":";
    wprintw(displayWindow, sender.c_str());
    wmove(displayWindow, currentRow+lineUsed, 5);

    for(char &c : message){
        waddch(displayWindow, c);
        countOnCurrentLine += 1;
        if(countOnCurrentLine > 60){
            lineUsed += 1;
            countOnCurrentLine = 0;
            wmove(displayWindow, currentRow+lineUsed, 5);
        }
    }
    lineUsed += 1;
    currentRow += lineUsed;
    wrefresh(displayWindow);
}