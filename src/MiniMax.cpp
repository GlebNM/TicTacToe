#include "MiniMax.h"
#include <algorithm>
#include <random>
#include <iostream>

Position
MiniMaxAgent::findNextMoveWithTimeLimit(int (* evaluation)(const State&, int, int, int), int timeLimit) {
    const milliseconds TIME_LIMIT{timeLimit - 100};
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
    int depth = 7;
    while (std::chrono::duration_cast<std::chrono::milliseconds>(end - start) < TIME_LIMIT) {
        std::vector<std::pair<int, Position>> tempScores;
        for (auto& move: scores) {
            State tempBoard = state;
            tempBoard.performMove(move.second);
            int curVal = calculate(tempBoard, 1, OPPONENT, -INF, INF, evaluation, depth);
            tempScores.emplace_back(std::make_pair(curVal, move.second));
            end = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(end - start) >= TIME_LIMIT)break;
        }
        std::sort(tempScores.begin(), tempScores.end(), [](auto& l, auto& r) {
            return l.first > r.first;
        });
        scores = tempScores;
        depth++;
        if (depth > 80)break;
        end = std::chrono::steady_clock::now();
    }
    std::clog << "<" << scores[0].first << '/' << depth - 1 << "> ";
    return scores[0].second;
}

int MiniMaxAgent::calculate(const State& st, int depth, int player, int alpha, int beta,
                            int evaluation(const State&, int, int, int), int maxDepth) {
    BoardStatus status = st.checkOverallStatus();
    if (depth == maxDepth || status != InProgress) {
        return evaluation(st, status, depth, player);
    }
    if (player == COMP) {
        int best = -INF;
        std::vector<Position> moves = st.getAvailableMoves();
        for (auto move: moves) {
            State tempBoard = st;
            tempBoard.performMove(move);
            int curVal = calculate(tempBoard, depth + 1, OPPONENT, alpha, beta, evaluation, maxDepth);
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
            int curVal = calculate(tempBoard, depth + 1, COMP, alpha, beta, evaluation, maxDepth);
            best = std::min(best, curVal);
            beta = std::min(best, beta);
            if (beta <= alpha)break;
        }
        return best;
    }

}

int MiniMaxAgent::evaluate1(const State& board, BoardStatus status, int depth, int player) {
    if (status == XWin && state.getCurrentPlayer() == XMark)return 10000 - depth;
    if (status == OWin && state.getCurrentPlayer() == OMark)return -10000 + depth;
    if (status == Draw)return 0;
    int cnt = 0;
    std::vector<std::vector<signed char>> bigField = board.getBigField();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (bigField[i][j] == COMP_WIN)cnt++;
            if (bigField[i][j] == OPPONENT_WIN)cnt--;
        }
    }
    cnt *= 100;
    std::vector<std::vector<signed char>> smallField = board.getSmallField();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (bigField[i][j] != Board::IN_PROGRESS)continue;
            for (int k = 0; k < 3; k++) {
                for (int p = 0; p < 3; p++) {
                    if (smallField[i * 3 + k][j * 3 + p] == COMP)cnt++;
                    if (smallField[i * 3 + k][j * 3 + p] == OPPONENT)cnt--;
                }
            }
        }
    }
    return cnt;
}

int minimax::evaluate2(const Board& board, int status, int depth, int player) {
    if (status == COMP_WIN)return 10000 - depth;
    if (status == OPPONENT_WIN)return -10000 + depth;
    if (status == Board::DRAW)return 0;
    int cnt = 0;
    std::vector<std::vector<signed char>> bigField = board.getBigField();

    if (bigField[1][1] == COMP_WIN)cnt += 120;
    if (bigField[1][1] == OPPONENT_WIN)cnt -= 120;

    if (bigField[0][0] == COMP_WIN)cnt += 110;
    if (bigField[0][0] == OPPONENT_WIN)cnt -= 110;
    if (bigField[0][2] == COMP_WIN)cnt += 110;
    if (bigField[0][2] == OPPONENT_WIN)cnt -= 110;
    if (bigField[2][0] == COMP_WIN)cnt += 110;
    if (bigField[2][0] == OPPONENT_WIN)cnt -= 110;
    if (bigField[2][2] == COMP_WIN)cnt += 110;
    if (bigField[2][2] == OPPONENT_WIN)cnt -= 110;

    if (bigField[0][1] == COMP_WIN)cnt += 100;
    if (bigField[0][1] == OPPONENT_WIN)cnt -= 100;
    if (bigField[1][0] == COMP_WIN)cnt += 100;
    if (bigField[1][0] == OPPONENT_WIN)cnt -= 100;
    if (bigField[1][2] == COMP_WIN)cnt += 100;
    if (bigField[1][2] == OPPONENT_WIN)cnt -= 100;
    if (bigField[2][1] == COMP_WIN)cnt += 100;
    if (bigField[2][1] == OPPONENT_WIN)cnt -= 100;

    std::vector<std::vector<signed char>> smallField = board.getSmallField();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (bigField[i][j] != Board::IN_PROGRESS)continue;
            for (int k = 0; k < 3; k++) {
                for (int p = 0; p < 3; p++) {
                    if (smallField[i * 3 + k][j * 3 + p] == COMP)cnt++;
                    if (smallField[i * 3 + k][j * 3 + p] == OPPONENT)cnt--;
                }
            }
        }
    }
    std::vector<Position> moves;
    board.getAvailableMoves(moves);
    if (moves.size() > 9) {
        if (player == COMP) cnt += 3;
        if (player == OPPONENT) cnt -= 3;
    }
    return cnt;
}
