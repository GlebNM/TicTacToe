#include "MiniMax.h"
#include <algorithm>
#include <random>
#include <iostream>

Position MiniMaxAgent::findNextMoveWithTimeLimit(int (* evaluation)(const State&, BoardStatus, int), int timeLimit) {
    const milliseconds TIME_LIMIT{timeLimit - 10};
    std::vector<Position> moves = state.getAvailableMoves();

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(moves.begin(), moves.end(), g);

    std::vector<std::pair<int, Position>> scores;
    scores.reserve(moves.size());
    for (auto& move: moves) {
        scores.emplace_back(std::make_pair(-INF, move));
    }
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    int depth = 1;
    while (std::chrono::duration_cast<std::chrono::milliseconds>(end - start) < TIME_LIMIT) {
        std::vector<std::pair<int, Position>> tempScores;
        for (auto& move: scores) {
            State tempBoard = state;
            tempBoard.performMove(move.second);
            int curVal = calculate(tempBoard, 1, -INF, INF, evaluation, depth);
            tempScores.emplace_back(std::make_pair(curVal, move.second));
            end = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(end - start) >= TIME_LIMIT)break;
        }
        std::sort(tempScores.begin(), tempScores.end(), [](const auto& l, const auto& r) {
            return l.first > r.first;
        });
        if (state.getCurrentPlayer() == PlayerSymbol::OMark) {
            std::reverse(tempScores.begin(), tempScores.end());
        }
        scores = tempScores;
        depth++;
        if (depth > 80)break;
        end = std::chrono::steady_clock::now();
    }
    std::clog << "<" << scores[0].first << '/' << depth - 1 << "> ";
    return scores[0].second;
}

int MiniMaxAgent::calculate(const State& st, int depth, int alpha, int beta,
                            int evaluation(const State&, BoardStatus, int), int maxDepth) {
    BoardStatus status = st.checkOverallStatus();
    if (depth == maxDepth || status != InProgress) {
        return evaluation(st, status, depth);
    }
    if (st.getCurrentPlayer() == PlayerSymbol::XMark) {
        int best = -INF;
        std::vector<Position> moves = st.getAvailableMoves();
        for (auto move: moves) {
            State tempBoard = st;
            tempBoard.performMove(move);
            int curVal = calculate(tempBoard, depth + 1, alpha, beta, evaluation, maxDepth);
            best = std::max(best, curVal);
            alpha = std::max(best, alpha);
            if (beta <= alpha)break;
        }
        return best;
    } else {
        int best = INF;
        std::vector<Position> moves = st.getAvailableMoves();
        for (auto move: moves) {
            State tempBoard = st;
            tempBoard.performMove(move);
            int curVal = calculate(tempBoard, depth + 1, alpha, beta, evaluation, maxDepth);
            best = std::min(best, curVal);
            beta = std::min(best, beta);
            if (beta <= alpha)break;
        }
        return best;
    }

}

int MiniMaxAgent::evaluate1(const State& board, BoardStatus status, int depth) {
    if (status == XWin && board.getCurrentPlayer() == XMark)return 10000 - depth;
    if (status == OWin && board.getCurrentPlayer() == OMark)return -10000 + depth;
    if (status == Draw)return 0;
    int cnt = 0;
    std::vector<std::bitset<3>> bigCellsX = board.getBigCellsX();
    std::vector<std::bitset<3>> bigCellsO = board.getBigCellsO();
    std::vector<std::bitset<3>> bigCellsDraw = board.getBigCellsDraw();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (bigCellsX[i][j] == BoardStatus::XWin)++cnt;
            if (bigCellsO[i][j] == BoardStatus::OWin)--cnt;
        }
    }
    cnt *= 100;

    std::vector<std::bitset<9>> smallCellsX = board.getSmallCellsX();
    std::vector<std::bitset<9>> smallCellsO = board.getSmallCellsO();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (bigCellsX[i][j] || bigCellsO[i][j] || bigCellsDraw[i][j])continue;
            for (int k = 0; k < 3; ++k) {
                for (int p = 0; p < 3; ++p) {
                    if (smallCellsX[i * 3 + k][j * 3 + p])++cnt;
                    if (smallCellsO[i * 3 + k][j * 3 + p])--cnt;
                }
            }
        }
    }
    return cnt;
}

int MiniMaxAgent::evaluate2(const State& board, BoardStatus status, int depth) {
    if (status == BoardStatus::XWin)return 10000 - depth;
    if (status == BoardStatus::OWin)return -10000 + depth;
    if (status == BoardStatus::Draw)return 0;
    int cnt = 0;
    std::vector<std::bitset<3>> bigCellsX = board.getBigCellsX();
    std::vector<std::bitset<3>> bigCellsO = board.getBigCellsO();
    std::vector<std::bitset<3>> bigCellsDraw = board.getBigCellsDraw();

    if (bigCellsX[1][1])cnt += 120;
    if (bigCellsO[1][1])cnt -= 120;

    if (bigCellsX[0][0])cnt += 110;
    if (bigCellsO[0][0])cnt -= 110;
    if (bigCellsX[0][2])cnt += 110;
    if (bigCellsO[0][2])cnt -= 110;
    if (bigCellsX[2][0])cnt += 110;
    if (bigCellsO[2][0])cnt -= 110;
    if (bigCellsX[2][2])cnt += 110;
    if (bigCellsO[2][2])cnt -= 110;

    if (bigCellsX[0][1])cnt += 100;
    if (bigCellsO[0][1])cnt -= 100;
    if (bigCellsX[1][0])cnt += 100;
    if (bigCellsO[1][0])cnt -= 100;
    if (bigCellsX[1][2])cnt += 100;
    if (bigCellsO[1][2])cnt -= 100;
    if (bigCellsX[2][1])cnt += 100;
    if (bigCellsO[2][1])cnt -= 100;

    std::vector<std::bitset<9>> smallCellsX = board.getSmallCellsX();
    std::vector<std::bitset<9>> smallCellsO = board.getSmallCellsO();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (bigCellsX[i][j] || bigCellsO[i][j] || bigCellsDraw[i][j])continue;
            for (int k = 0; k < 3; ++k) {
                for (int p = 0; p < 3; ++p) {
                    if (smallCellsX[i * 3 + k][j * 3 + p])++cnt;
                    if (smallCellsO[i * 3 + k][j * 3 + p])--cnt;
                }
            }
        }
    }
    std::vector<Position> moves = board.getAvailableMoves();
    if (moves.size() > 9) {
        if (board.getCurrentPlayer() == PlayerSymbol::XMark) {
            cnt += 3;
        } else {
            cnt -= 3;
        }
    }
    return cnt;
}


void MiniMaxAgent::init(const State& newState) {
    state = newState;
}

void MiniMaxAgent::performMove(Position move) {
    state.performMove(move);
}

Position MiniMaxAgent::choseBestMove(int timeLimit) {
    return findNextMoveWithTimeLimit(evaluate2, timeLimit);
}

void MiniMaxAgent::resetGame() {
    state.reset();
}

void MiniMaxAgent::setAllPossibleMoves(const std::vector<Position>&) {}

void MiniMaxAgent::setState(const State& newState) {
    state = newState;
}
