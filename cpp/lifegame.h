#pragma once

#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::string;
using std::vector;

constexpr int DY8[] = {-1, -1, -1, 0, 0, 1, 1, 1};
constexpr int DX8[] = {-1, 0, 1, -1, 1, -1, 0, 1};

class LifeGame {
    int height_;
    int width_;
    vector<vector<bool>> field_;

    bool pos_check(const int y, const int x) const {
        return (0 <= y && y < height_ && 0 <= x && x < width_);
    }

    int neighbours_count(const int y, const int x) const {
        int res = 0;
        for (int i = 0; i < 8; i++) {
            int ny = y + DY8[i], nx = x + DX8[i];
            if (!pos_check(ny, nx)) {
                continue;
            }

            if (field_[ny][nx]) {
                res += 1;
            }
        }
        return res;
    }

    bool should_be_alive(const bool cell_state, const int neighbours) const {
        if (cell_state && neighbours == 2) {
            return true;
        } else if (neighbours == 3) {
            return true;
        } else {
            return false;
        }
    }

public:
    LifeGame(const int height, const int width)
        : height_(height), width_(width) {
        field_.assign(height_, vector<bool>(width_, false));
    }

    void init_field() {
        std::mt19937 mt{std::random_device{}()};
        std::uniform_int_distribution<int> dist(0, 1);

        for (int y = 0; y < height_; y++) {
            for (int x = 0; x < width_; x++) {
                const bool alive = static_cast<bool>(dist(mt));
                field_[y][x]     = alive;
            }
        }
    }

    void dump() const {
        string buf = "";
        for (const auto row : field_) {
            for (const auto cell : row) {
                buf += (cell ? "o" : ".");
            }
            buf += "\n";
        }

        std::cout << buf;
    }

    LifeGame next_field() const {
        auto next = LifeGame(height_, width_);
        for (int y = 0; y < height_; y++) {
            for (int x = 0; x < width_; x++) {
                const auto neighbours = neighbours_count(y, x);
                const auto alive      = should_be_alive(field_[y][x], neighbours);
                next.field_[y][x]     = alive;
            }
        }
        return next;
    }
};