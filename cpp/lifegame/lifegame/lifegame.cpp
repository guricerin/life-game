#include "lifegame.h"
#include <thread>
#include <chrono>
#include <cstdlib>

void console_clear() {
    std::system("cls");
}

int main() {
    constexpr int height = 30;
    constexpr int width = 40;
    auto lifegame = LifeGame(height, width);
    lifegame.init_field();

    while (true) {
        //console_clear(); // 有効化したらチラつきがひどい
        lifegame.dump();
        lifegame = lifegame.next_field();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
	return 0;
}
