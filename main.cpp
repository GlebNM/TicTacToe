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
