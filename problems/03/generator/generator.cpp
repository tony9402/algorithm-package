#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

struct Heater {
    int r;
    int c;
    int d;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int minR = opt<int>("minR", 2);
    int maxR = opt<int>("maxR", 20);
    int minC = opt<int>("minC", 2);
    int maxC = opt<int>("maxC", 20);
    int minK = opt<int>("minK", 1);
    int maxK = opt<int>("maxK", 1000);
    string mode = opt<string>("mode", "random");

    int r = rnd.next(minR, maxR);
    int c = rnd.next(minC, maxC);
    int k = rnd.next(minK, maxK);
    vector<vector<int>> board(r + 1, vector<int>(c + 1, 0));
    vector<Heater> heaters;

    auto validDirections = [&](int row, int col) {
        vector<int> dirs;
        if (col < c) dirs.push_back(1);
        if (col > 1) dirs.push_back(2);
        if (row > 1) dirs.push_back(3);
        if (row < r) dirs.push_back(4);
        return dirs;
    };

    vector<pair<int, int>> cells;
    for (int row = 1; row <= r; ++row) {
        for (int col = 1; col <= c; ++col) cells.push_back({row, col});
    }
    shuffle(cells.begin(), cells.end());

    int maxHeaters = max(1, min<int>(cells.size() / 4, opt<int>("maxHeaters", 10)));
    int heaterCount = rnd.next(1, maxHeaters);
    int cursor = 0;
    while ((int)heaters.size() < heaterCount && cursor < (int)cells.size()) {
        auto [row, col] = cells[cursor++];
        auto dirs = validDirections(row, col);
        if (dirs.empty()) continue;
        int d = dirs[rnd.next(0, (int)dirs.size() - 1)];
        board[row][col] = d;
        heaters.push_back({row, col, d});
    }
    if (heaters.empty()) {
        board[1][1] = 1;
        heaters.push_back({1, 1, 1});
    }

    int maxChecks = max(1, min<int>(cells.size() / 3, opt<int>("maxChecks", 12)));
    int checkCount = rnd.next(1, maxChecks);
    int checks = 0;
    for (auto [row, col] : cells) {
        if (checks == checkCount) break;
        if (board[row][col] != 0) continue;
        board[row][col] = 5;
        ++checks;
    }
    if (checks == 0) {
        for (int row = 1; row <= r && checks == 0; ++row) {
            for (int col = 1; col <= c && checks == 0; ++col) {
                if (board[row][col] == 0) {
                    board[row][col] = 5;
                    checks = 1;
                }
            }
        }
    }

    set<tuple<int, int, int>> blockedWalls;
    for (const Heater& h : heaters) {
        if (h.d == 1) blockedWalls.insert({h.r, h.c, 1});
        if (h.d == 2) blockedWalls.insert({h.r, h.c - 1, 1});
        if (h.d == 3) blockedWalls.insert({h.r, h.c, 0});
        if (h.d == 4) blockedWalls.insert({h.r + 1, h.c, 0});
    }

    vector<tuple<int, int, int>> candidates;
    for (int row = 2; row <= r; ++row) {
        for (int col = 1; col <= c; ++col) candidates.push_back({row, col, 0});
    }
    for (int row = 1; row <= r; ++row) {
        for (int col = 1; col < c; ++col) candidates.push_back({row, col, 1});
    }
    shuffle(candidates.begin(), candidates.end());

    vector<tuple<int, int, int>> walls;
    int limit = mode == "dense_walls" ? min<int>(r * c, candidates.size()) : rnd.next(0, min<int>(r * c, candidates.size()));
    if (mode == "open") limit = 0;
    for (auto wall : candidates) {
        if ((int)walls.size() >= limit) break;
        if (blockedWalls.count(wall)) continue;
        walls.push_back(wall);
    }

    cout << r << ' ' << c << ' ' << k << '\n';
    for (int row = 1; row <= r; ++row) {
        for (int col = 1; col <= c; ++col) {
            if (col > 1) cout << ' ';
            cout << board[row][col];
        }
        cout << '\n';
    }
    cout << walls.size() << '\n';
    for (auto [row, col, t] : walls) cout << row << ' ' << col << ' ' << t << '\n';

    return 0;
}
