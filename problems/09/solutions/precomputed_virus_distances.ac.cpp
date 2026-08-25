#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int DR[4] = {-1, 0, 1, 0};
const int DC[4] = {0, 1, 0, -1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int size, activeCount;
    cin >> size >> activeCount;
    vector<vector<int>> board(size, vector<int>(size));
    vector<pair<int, int>> viruses;
    vector<int> emptyCells;
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            cin >> board[r][c];
            if (board[r][c] == 2) {
                viruses.emplace_back(r, c);
            } else if (board[r][c] == 0) {
                emptyCells.push_back(r * size + c);
            }
        }
    }

    int virusCount = static_cast<int>(viruses.size());
    vector<vector<int>> distance(virusCount,
                                 vector<int>(size * size, -1));
    for (int source = 0; source < virusCount; ++source) {
        queue<int> pending;
        int start = viruses[source].first * size + viruses[source].second;
        distance[source][start] = 0;
        pending.push(start);
        while (!pending.empty()) {
            int cell = pending.front();
            pending.pop();
            int row = cell / size;
            int col = cell % size;
            for (int direction = 0; direction < 4; ++direction) {
                int nextRow = row + DR[direction];
                int nextCol = col + DC[direction];
                if (nextRow < 0 || nextRow >= size || nextCol < 0 ||
                    nextCol >= size || board[nextRow][nextCol] == 1) {
                    continue;
                }
                int next = nextRow * size + nextCol;
                if (distance[source][next] != -1) {
                    continue;
                }
                distance[source][next] = distance[source][cell] + 1;
                pending.push(next);
            }
        }
    }

    int answer = numeric_limits<int>::max();
    for (int mask = 0; mask < (1 << virusCount); ++mask) {
        int selected = 0;
        for (int bits = mask; bits != 0; bits >>= 1) {
            selected += bits & 1;
        }
        if (selected != activeCount) {
            continue;
        }

        int completion = 0;
        bool possible = true;
        for (int cell : emptyCells) {
            int earliest = numeric_limits<int>::max();
            for (int virus = 0; virus < virusCount; ++virus) {
                if ((mask & (1 << virus)) && distance[virus][cell] != -1) {
                    earliest = min(earliest, distance[virus][cell]);
                }
            }
            if (earliest == numeric_limits<int>::max()) {
                possible = false;
                break;
            }
            completion = max(completion, earliest);
        }
        if (possible) {
            answer = min(answer, completion);
        }
    }

    cout << (answer == numeric_limits<int>::max() ? -1 : answer);
    return 0;
}
