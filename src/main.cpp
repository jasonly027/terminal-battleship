#include "server.h"

using namespace battleship;

int main() {
    Server s(49494);
    s.start();
    while (1) {
        s.update(-1, true);
    }


    return 0;
}