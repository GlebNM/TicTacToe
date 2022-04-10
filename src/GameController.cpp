#include "GameController.h"
#include <vector>
#include <cctype>
#include <iostream>
#include <algorithm>

Position GameController::inputMove(const std::vector<Position>& availableMoves,
                                   const std::string& name) {
    Position move{-1, -1};
    std::string input;
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

void GameController::PlayGameEngineEngine(Bot* engine1, Bot* engine2,
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
}

void GameController::PlayGameEngineHuman(Bot* engine, bool isHumanFirst,
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

void GameController::PlayGameHumanHuman() {
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
