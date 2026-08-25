#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> board(n, vector<int>(n));
    for (auto &row : board) {
        for (int &cell : row) cin >> cell;
    }

    const int states = 3 * n * n;
    auto state = [n](int row, int column, int direction) {
        return (row * n + column) * 3 + direction;
    };
    set<pair<int, int>> adjacency;
    auto addEdge = [&](int from, int to) {
        adjacency.insert({from, to});
    };

    for (int row = 0; row < n; ++row) {
        for (int column = 0; column < n; ++column) {
            if (board[row][column]) continue;
            for (int direction = 0; direction < 3; ++direction) {
                const int from = state(row, column, direction);
                if (direction != 1 && column + 1 < n && !board[row][column + 1]) {
                    addEdge(from, state(row, column + 1, 0));
                }
                if (direction != 0 && row + 1 < n && !board[row + 1][column]) {
                    addEdge(from, state(row + 1, column, 1));
                }
                if (row + 1 < n && column + 1 < n && !board[row][column + 1] &&
                    !board[row + 1][column] && !board[row + 1][column + 1]) {
                    addEdge(from, state(row + 1, column + 1, 2));
                }
            }
        }
    }

    vector<long long> current(states);
    current[state(0, 1, 0)] = 1;
    long long answer = 0;
    const int maximumMoves = 2 * n - 3;
    for (int moves = 0; moves <= maximumMoves; ++moves) {
        for (int direction = 0; direction < 3; ++direction) {
            answer += current[state(n - 1, n - 1, direction)];
        }
        if (moves == maximumMoves) break;

        vector<long long> next(states);
        for (int from = 0; from < states; ++from) {
            for (int to = 0; to < states; ++to) {
                if (adjacency.find({from, to}) != adjacency.end()) {
                    next[to] += current[from];
                }
            }
        }
        current.swap(next);
    }

    cout << answer << '\n';
    return 0;
}
