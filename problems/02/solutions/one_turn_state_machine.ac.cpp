#include <iostream>

using namespace std;

const int DR[4] = {-1, 0, 1, 0};
const int DC[4] = {0, 1, 0, -1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int rows, cols;
    int row, col, direction;
    int room[50][50];
    cin >> rows >> cols >> row >> col >> direction;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            cin >> room[r][c];
        }
    }

    int cleaned = 0;
    while (true) {
        if (room[row][col] == 0) {
            room[row][col] = 2;
            ++cleaned;
        }

        bool hasDirtyNeighbor = false;
        for (int d = 0; d < 4; ++d) {
            if (room[row + DR[d]][col + DC[d]] == 0) {
                hasDirtyNeighbor = true;
            }
        }

        if (hasDirtyNeighbor) {
            direction = (direction + 3) % 4;
            int nextRow = row + DR[direction];
            int nextCol = col + DC[direction];
            if (room[nextRow][nextCol] == 0) {
                row = nextRow;
                col = nextCol;
            }
            continue;
        }

        int back = (direction + 2) % 4;
        int nextRow = row + DR[back];
        int nextCol = col + DC[back];
        if (room[nextRow][nextCol] == 1) {
            break;
        }
        row = nextRow;
        col = nextCol;
    }

    cout << cleaned;
    return 0;
}
