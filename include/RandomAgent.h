#include "Bot.h"

class RandomAgent : public Bot {
private:
    State state;
    
public:
    RandomAgent() = default;

    ~RandomAgent() = default;

    void init(const State&) final;

    Position choseBestMove(int) final;

    void performMove(Position) final;

    void setState(const State&) final;

    void setAllPossibleMoves(const std::vector<Position>&) final;

    void resetGame() final;
};
