#include "Interface.h"
#include "GameController.h"
#include "RandomAgent.h"
#include "MiniMax.h"
#include "MCTSAgent.h"
#include <iostream>

void Interface::welcomeScreen() {
    std::cout << "Добро пожаловать в Ultimate Tic-Tac-Toe!" << std::endl;
}

bool Interface::validateInput(std::string ans) {
    for (auto v : ans)
    	if (!std::isdigit(v)) {
            return false;
        }
    if (ans.size() > 1 && ans[0] == '0') {
        return false;
    }
    return true;
}


int Interface::chooseFirstPlayer() {
    while(true) {
        std::cout << "Выберите кто ходит первый" << std::endl;
        std::cout << "1) Компьютер" << std::endl;
        std::cout << "2) Человек" << std::endl;
        std::string ans;
        std::cin >> ans;
        if (ans == "1" || ans == "2") {
            return ans[0] - '0';
        }
        std::cout << "Неверно выбран первый игрок" << std::endl << std::endl;
    }
}

bool Interface::askInfoAboutBot(std::string question, int num = 0) {
    while(true) {
        std::cout << question;
        if (num > 0)
            std::cout << " " << num;
        std::cout << "?" << std::endl;
        std::cout << "1) Да" << std::endl;
        std::cout << "2) Нет" << std::endl;
        std::string s;
        std::cin >> s;
        if (s == "1" || s == "2") {
            return 1 - (s[0] - '1');
        }
        std::cout << "Неверно введен ответ" << std::endl << std::endl;
    }
}

int Interface::choosePlayerTime() {
    while(true) {
        std::cout << "Введите время в мс" << std::endl;
        std::string ans;
        std::cin >> ans;
        if (validateInput(ans)) {
            int num = 0;
            for (auto v : ans)
                num = num * 10 + v - '0';
            return num;
        }
        std::cout << "Некорретное число" << std::endl << std::endl;
    }
}

std::string Interface::choosePlayerAlgorithm() {
    while(true) {
        std::cout << "Выберите алгоритм" << std::endl;
        std::cout << "1) Random" << std::endl;
        std::cout << "2) MCTS" << std::endl;
        std::cout << "3) MiniMax" << std::endl;
        std::string ans;
        std::cin >> ans;
        if (ans == "1" || ans == "2" || ans == "3") {
            if (ans == "1") {
                return "Random";
            }
            if (ans == "2") {
                return "MCTS";
            }
            return "MiniMax";
        }
        std::cout << "Неверно выбран алгоритм" << std::endl << std::endl;
    }
}

bool Interface::chooseMode() {
    std::cout << "Выберите режим игры" << std::endl;
    std::cout << "1) Человек - человек" << std::endl;
    std::cout << "2) Компьютер - человек" << std::endl;
    std::cout << "3) Компьютер - компьютер" << std::endl;
    std::cout << "\nВведите выбранный режим (1-3)" << std::endl;
    std::string s;
    std::cin >> s;
    if (s != "1" && s != "2" && s != "3") {
        std::cout << "Неверно введен режим" << std::endl;
        return false;
    }
    mode = s[0] - '0';
    if (mode == 1) {
        firstPlayer = 1;
        return true;
    }
    if (mode == 2) {
        firstPlayer = chooseFirstPlayer();
        bool want = askInfoAboutBot("Хотите выбрать алгоритм для бота");
        if (want) {
            firstPlayer == 1 ? firstPlayerAlgorithm = choosePlayerAlgorithm() :  secondPlayerAlgorithm = choosePlayerAlgorithm();
        }
        want = askInfoAboutBot("Хотите выбрать ограничение по времени для бота");
        if (want) {
            firstPlayer == 1 ? firstPlayerTime = choosePlayerTime() :  secondPlayerTime = choosePlayerTime();
        }
    }
    if (mode == 3) {
        bool want = askInfoAboutBot("Хотите выбрать алгоритм для бота", 1);
        if (want) {
            firstPlayerAlgorithm = choosePlayerAlgorithm();
        }
        want = askInfoAboutBot("Хотите выбрать ограничение по времени для бота", 1);
        if (want) {
            firstPlayerTime = choosePlayerTime();
        }
        want = askInfoAboutBot("Хотите выбрать алгоритм для бота", 2);
        if (want) {
            secondPlayerAlgorithm = choosePlayerAlgorithm();
        }
        want = askInfoAboutBot("Хотите выбрать ограничение по времени для бота", 2);
        if (want) {
            secondPlayerTime = choosePlayerTime();
        }
    }
    return true;
}

void Interface::game() {
    GameController gameController;
    if (mode == 1) {
        gameController.playGameHumanHuman();
    } else if (mode == 2) {
        Bot* bot;
        if (firstPlayerAlgorithm == "Random") {
            bot = new RandomAgent();
        } else if (firstPlayerAlgorithm == "MCTS") {
            bot = new MCTSAgent();
        } else {
            bot = new MiniMaxAgent();
        }
        gameController.playGameEngineHuman(
            bot,
            firstPlayer == 2,
            firstPlayer == 1 ? firstPlayerTime : secondPlayerTime
        );
    } else {
        Bot* bot1;
        Bot* bot2;
        if (firstPlayerAlgorithm == "Random") {
            bot1 = new RandomAgent();
        } else if (firstPlayerAlgorithm == "MCTS") {
            bot1 = new MCTSAgent();
        } else {
            bot1 = new MiniMaxAgent();
        }
        if (secondPlayerAlgorithm == "Random") {
            bot2 = new RandomAgent();
        } else if (secondPlayerAlgorithm == "MCTS") {
            bot2 = new MCTSAgent();
        } else {
            bot2 = new MiniMaxAgent();
        }
        gameController.playGameEngineEngine(
            bot1, bot2, firstPlayerTime, secondPlayerTime
        );
    }
}
