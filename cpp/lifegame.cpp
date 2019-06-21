#include "lifegame.h"
#include <chrono>
#include <cstdlib>
#include <thread>

void console_clear() {
    printf("\033[;H\033[2J");
}

int main() {
    constexpr int height = 40;
    constexpr int width  = 80;
    auto lifegame        = LifeGame(height, width);
    lifegame.init_field();

    while (true) {
        console_clear();
        lifegame.dump();
        lifegame = lifegame.next_field();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}
