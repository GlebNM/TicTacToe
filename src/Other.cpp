#include "Other.h"

int COMP, OPPONENT, OPPONENT_WIN, COMP_WIN;

int changePlayer(int player) {
    if (player == COMP)return OPPONENT;
    else return COMP;
}
