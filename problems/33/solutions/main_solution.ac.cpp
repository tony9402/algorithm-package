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

int n;
vector<string> grid;

string solve(int r, int c, int len) {
    char first = grid[r][c];
    bool same = true;
    for (int i = r; i < r + len; ++i) {
        for (int j = c; j < c + len; ++j) {
            if (grid[i][j] != first) same = false;
        }
    }
    if (same) return string(1, first);

    int half = len / 2;
    return "(" + solve(r, c, half) + solve(r, c + half, half) +
           solve(r + half, c, half) + solve(r + half, c + half, half) + ")";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    grid.resize(n);
    for (string& row : grid) cin >> row;
    cout << solve(0, 0, n) << '\n';
    return 0;
}
