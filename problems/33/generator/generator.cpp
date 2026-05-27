#include "testlib.h"
#include <algorithm>
#include <array>
#include <climits>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

void fill_block(vector<string>& grid, int r, int c, int len, char value) {
    for (int i = r; i < r + len; ++i) {
        for (int j = c; j < c + len; ++j) grid[i][j] = value;
    }
}

void make_blocky(vector<string>& grid, int r, int c, int len) {
    if (len == 1 || rnd.next(0, 99) < 35) {
        fill_block(grid, r, c, len, char('0' + rnd.next(0, 1)));
        return;
    }
    int half = len / 2;
    make_blocky(grid, r, c, half);
    make_blocky(grid, r, c + half, half);
    make_blocky(grid, r + half, c, half);
    make_blocky(grid, r + half, c + half, half);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int exp = opt<int>("exp", 3);
    string mode = opt<string>("mode", "random");
    int n = 1 << exp;
    vector<string> grid(n, string(n, '0'));

    if (mode == "zero" || mode == "one") {
        fill_block(grid, 0, 0, n, mode == "zero" ? '0' : '1');
    } else if (mode == "blocky") {
        make_blocky(grid, 0, 0, n);
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) grid[i][j] = char('0' + rnd.next(0, 1));
        }
    }

    cout << n << '\n';
    for (const string& row : grid) cout << row << '\n';
    return 0;
}
