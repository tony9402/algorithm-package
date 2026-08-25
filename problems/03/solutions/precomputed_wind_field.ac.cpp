#include <cstdlib>
#include <iostream>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

const int DR[4] = {0, 0, -1, 1};
const int DC[4] = {1, -1, 0, 0};
const int OPPOSITE[4] = {1, 0, 3, 2};

struct Heater {
    int row;
    int col;
    int direction;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int rows, cols, target;
    cin >> rows >> cols >> target;

    vector<Heater> heaters;
    vector<pair<int, int>> checkpoints;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int cell;
            cin >> cell;
            if (1 <= cell && cell <= 4) {
                heaters.push_back({r, c, cell - 1});
            } else if (cell == 5) {
                checkpoints.emplace_back(r, c);
            }
        }
    }

    vector<vector<vector<bool>>> blocked(
        rows, vector<vector<bool>>(cols, vector<bool>(4)));
    int wallCount;
    cin >> wallCount;
    while (wallCount--) {
        int row, col, type;
        cin >> row >> col >> type;
        --row;
        --col;
        int direction = type == 0 ? 2 : 0;
        int nextRow = row + DR[direction];
        int nextCol = col + DC[direction];
        blocked[row][col][direction] = true;
        blocked[nextRow][nextCol][OPPOSITE[direction]] = true;
    }

    auto inside = [rows, cols](int row, int col) {
        return 0 <= row && row < rows && 0 <= col && col < cols;
    };

    vector<vector<int>> wind(rows, vector<int>(cols));
    for (const Heater& heater : heaters) {
        int startRow = heater.row + DR[heater.direction];
        int startCol = heater.col + DC[heater.direction];
        vector<vector<bool>> visited(rows, vector<bool>(cols));
        queue<tuple<int, int, int>> pending;
        visited[startRow][startCol] = true;
        pending.emplace(startRow, startCol, 5);

        while (!pending.empty()) {
            auto [row, col, power] = pending.front();
            pending.pop();
            wind[row][col] += power;
            if (power == 1) {
                continue;
            }

            int sideDirections[2];
            if (heater.direction < 2) {
                sideDirections[0] = 2;
                sideDirections[1] = 3;
            } else {
                sideDirections[0] = 1;
                sideDirections[1] = 0;
            }

            int nextRow = row + DR[heater.direction];
            int nextCol = col + DC[heater.direction];
            if (inside(nextRow, nextCol) &&
                !blocked[row][col][heater.direction] &&
                !visited[nextRow][nextCol]) {
                visited[nextRow][nextCol] = true;
                pending.emplace(nextRow, nextCol, power - 1);
            }

            for (int sideDirection : sideDirections) {
                int sideRow = row + DR[sideDirection];
                int sideCol = col + DC[sideDirection];
                if (!inside(sideRow, sideCol) ||
                    blocked[row][col][sideDirection]) {
                    continue;
                }
                nextRow = sideRow + DR[heater.direction];
                nextCol = sideCol + DC[heater.direction];
                if (!inside(nextRow, nextCol) ||
                    blocked[sideRow][sideCol][heater.direction] ||
                    visited[nextRow][nextCol]) {
                    continue;
                }
                visited[nextRow][nextCol] = true;
                pending.emplace(nextRow, nextCol, power - 1);
            }
        }
    }

    vector<vector<int>> temperature(rows, vector<int>(cols));
    for (int chocolate = 1; chocolate <= 100; ++chocolate) {
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                temperature[r][c] += wind[r][c];
            }
        }

        vector<vector<int>> delta(rows, vector<int>(cols));
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                for (int direction : {0, 3}) {
                    int nextRow = r + DR[direction];
                    int nextCol = c + DC[direction];
                    if (!inside(nextRow, nextCol) ||
                        blocked[r][c][direction]) {
                        continue;
                    }
                    int amount = abs(temperature[r][c] -
                                     temperature[nextRow][nextCol]) / 4;
                    if (temperature[r][c] > temperature[nextRow][nextCol]) {
                        delta[r][c] -= amount;
                        delta[nextRow][nextCol] += amount;
                    } else {
                        delta[r][c] += amount;
                        delta[nextRow][nextCol] -= amount;
                    }
                }
            }
        }
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                temperature[r][c] += delta[r][c];
            }
        }

        for (int r = 0; r < rows; ++r) {
            if (temperature[r][0] > 0) {
                --temperature[r][0];
            }
            if (temperature[r][cols - 1] > 0) {
                --temperature[r][cols - 1];
            }
        }
        for (int c = 1; c + 1 < cols; ++c) {
            if (temperature[0][c] > 0) {
                --temperature[0][c];
            }
            if (temperature[rows - 1][c] > 0) {
                --temperature[rows - 1][c];
            }
        }

        bool ready = true;
        for (const auto& [row, col] : checkpoints) {
            if (temperature[row][col] < target) {
                ready = false;
            }
        }
        if (ready) {
            cout << chocolate;
            return 0;
        }
    }

    cout << 101;
    return 0;
}
