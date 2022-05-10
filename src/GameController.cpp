#include "GameController.h"
#include <vector>
#include <cctype>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "json.hpp"

void updateRatings(int id1, int id2, BoardStatus res) {
    if (id1 == id2)return;
    using nlohmann::json;
    std::ifstream in("ratings.json");
    json j;
    in >> j;
    in.close();
    std::string sid1 = std::to_string(id1);
    std::string sid2 = std::to_string(id2);
    double Ra = j[sid1];
    double Rb = j[sid2];
    double Ea = 1.0 / (1 + pow(10, (Rb - Ra) / 400));
    double Eb = 1.0 / (1 + pow(10, (Ra - Rb) / 400));

    const double K = 20;
    double Sa = 0;
    double Sb = 0;
    if (res == BoardStatus::XWin) {
        Sa = 1;
    } else if (res == BoardStatus::Draw) {
        Sa = 0.5;
        Sb = 0.5;
    } else {
        Sb = 1;
    }

    double RaNew = Ra + K * (Sa - Ea);
    double RbNew = Rb + K * (Sb - Eb);
    j[sid1] = RaNew;
    j[sid2] = RbNew;
    std::ofstream out("ratings.json");
    out << j;
    out.close();
}

Position GameController::inputMove(const std::vector<Position>& availableMoves,
                                   const std::string& name) {
    Position move{-1, -1};
    std::string input;
    std::cout << std::endl;
    while (true) {
        std::cout << name << ", введите свой ход" << std::endl;
        std::getline(std::cin, input);
        if (input.size() == 3 && std::isdigit(input[0]) && std::isdigit(input[2]) &&
            input[1] == ' ') {
            move = {input[0] - '0', input[2] - '0'};
            if (std::find(availableMoves.begin(), availableMoves.end(), move) !=
                availableMoves.end()) {
                break;
            }
        }
    }
    return move;
}

void GameController::printStatus(BoardStatus status) {
    if (status == XWin) {
        std::cout << "XWin" << std::endl;
    } else if (status == OWin) {
        std::cout << "OWin" << std::endl;
    } else if (status == Draw) {
        std::cout << "Draw" << std::endl;
    }
}

void GameController::playGameEngineEngine(Bot* engine1, Bot* engine2,
                                          int timelimit1, int timelimit2) {
    State state;
    engine1->init(state);
    engine2->init(state);
    auto printAndUpdate = [&state, engine1, engine2](Position move) {
        std::cout << move.x << ' ' << move.y << std::endl;
        state.performMove(move);
        state.print();
        engine1->performMove(move);
        engine2->performMove(move);
    };
    while (state.checkOverallStatus() == InProgress) {
        std::cout << "Bot1" << std::endl;
        Position move = engine1->choseBestMove(timelimit1);
        printAndUpdate(move);
        if (state.checkOverallStatus() != InProgress) {
            break;
        }
        std::cout << "Bot2" << std::endl;
        move = engine2->choseBestMove(timelimit2);
        printAndUpdate(move);
    }
    printStatus(state.checkOverallStatus());
    updateRatings(engine1->getId(), engine2->getId(), state.checkOverallStatus());
}

void GameController::playGameEngineHuman(Bot* engine, bool isHumanFirst,
                                         int timelimit) {
    State state;
    engine->init(state);
    auto humansMove = [this, &state, engine]() {
        Position move = inputMove(state.getAvailableMoves(), "Игрок");
        state.performMove(move);
        state.print();
        engine->performMove(move);
    };
    if (isHumanFirst) {
        humansMove();
    }
    while (state.checkOverallStatus() == InProgress) {
        std::cout << "Bot" << std::endl;
        Position move = engine->choseBestMove(timelimit);
        std::cout << move.x << ' ' << move.y << std::endl;
        state.performMove(move);
        state.print();
        engine->performMove(move);
        if (state.checkOverallStatus() != InProgress) {
            break;
        }
        humansMove();
    }
    printStatus(state.checkOverallStatus());
}

void GameController::playGameHumanHuman() {
    State state;
    auto makeMove = [this, &state](const std::string& name) {
        Position move = inputMove(state.getAvailableMoves(), name);
        state.performMove(move);
        state.print();
    };
    while (state.checkOverallStatus() == InProgress) {
        makeMove("Игрок 1");
        if (state.checkOverallStatus() != InProgress) {
            break;
        }
        makeMove("Игрок 2");
    }
    printStatus(state.checkOverallStatus());
}
