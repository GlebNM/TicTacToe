#include "../include/Interface.h"
#include <iostream>

void Interface::welcomeScreen() {

}

int Interface::chooseFirstPlayer() {
    while(true) {
        std::cout << "Выберите кто ходит первый\n";
        std::cout << "1) Компьютер\n";
        std::cout << "2) Человек\n";
        std::string ans;
        std::cin >> ans;
        if (ans == "1" || ans == "2") {
            return ans[0] - '0';
        }
        std::cout << "Неверно выбран первый игрок\n\n";
    }
}

bool Interface::askInfoAboutBot(std::string question, int num = 0) {
    while(true) {
        std::cout << question;
        if (num > 0)
            std::cout << " " << num;
        std::cout << "?\n";
        std::cout << "1) Да\n";
        std::cout << "2) Нет\n";
        std::string s;
        std::cin >> s;
        if (s == "1" || s == "2") {
            return 1 - (s[0] - '1');
        }
        std::cout << "Неверно введен ответ\n\n";
    }
}

int Interface::choosePlayerTime() {
    while(true) {
        std::cout << "Введите время в мс\n";
        std::string ans;
        std::cin >> ans;
        bool corrAns = true;
        for (auto v : ans)
            if (!std::isdigit(v)) {
                corrAns = false;
                break;
            }
        if (ans.size() > 1 && ans[0] == '0') {
            corrAns = false;
        }
        if (corrAns) {
            int num = 0;
            for (auto v : ans)
                num = num * 10 + v - '0';
            return num;
        }
        std::cout << "Нiекорретное число\n\n";
    }
}

std::string Interface::choosePlayerAlgorithm() {
    while(true) {
        std::cout << "Выберите алгоритм\n";
        std::cout << "1) Random\n";
        std::cout << "2) MCTS\n";
        std::cout << "3) MiniMax\n";
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
        std::cout << "Неверно выбран алгоритм\n\n";
    }
}

bool Interface::chooseMode() {
    std::cout << "Выберите режим игры\n";
    std::cout << "1) Человек - человек\n";
    std::cout << "2) Компьютер - человек\n";
    std::cout << "3) Компьютер - компьютер\n";
    std::cout << "\nВведите выбранный режим (1-3)\n";
    std::string s;
    std::cin >> s;
    if (s != "1" && s != "2" && s != "3") {
        std::cout << "Неверно введен режим\n";
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

int main() {
    Interface ff;
    ff.chooseMode();
}
