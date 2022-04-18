#include <iostream>
#include <algorithm>
#include <ctime>
#include "MCTSAgent.h"
#include "Other.h"
#include "Interface.h"

int main() {
    Interface interface;
    interface.welcomeScreen();
    while (true) {
        if (interface.chooseMode()) {
            break;
        }
    }
    interface.game();
}
