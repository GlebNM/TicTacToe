#pragma once

#include <iostream>

class Interface {
private:
    int mode;
    int firstPlayer;
    std::string firstPlayerAlgorithm;
    int firstPlayerTime;
    std::string secondPlayerAlgorithm;
    int secondPlayerTime;
    
    bool validateInput(std::string);
    bool askInfoAboutBot(std::string, int num);
    int chooseFirstPlayer();
    std::string choosePlayerAlgorithm();
    int choosePlayerTime() ;
    
public:
    void welcomeScreen();
    
    bool chooseMode();
};
