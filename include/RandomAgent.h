#include "Bot.h"

class RandomAgent : public Bot {
private:
    State state;

public:
    static const int id = 3;

    int getId() {
        return id;
    }

    RandomAgent() = default;

    ~RandomAgent() = default;

    void init(const State&) final;

    Position choseBestMove(int) final;

    void performMove(Position) final;

    void setState(const State&) final;

    void setAllPossibleMoves(const std::vector<Position>&) final;

    void resetGame() final;
};
