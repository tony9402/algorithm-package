#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int rows, columns;
    cin >> rows >> columns;
    const int cells = rows * columns;
    vector<int> board(cells);
    for (int &value : board) cin >> value;

    const int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    vector<int> next(cells, -1);
    vector<int> indegree(cells);
    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            const int current = row * columns + column;
            int destination = current;
            for (int direction = 0; direction < 8; ++direction) {
                const int nextRow = row + dr[direction];
                const int nextColumn = column + dc[direction];
                if (nextRow < 0 || nextRow >= rows || nextColumn < 0 || nextColumn >= columns) continue;
                const int candidate = nextRow * columns + nextColumn;
                if (board[candidate] < board[destination]) destination = candidate;
            }
            if (destination != current) {
                next[current] = destination;
                ++indegree[destination];
            }
        }
    }

    queue<int> ready;
    for (int cell = 0; cell < cells; ++cell) {
        if (indegree[cell] == 0) ready.push(cell);
    }

    vector<int> balls(cells, 1);
    while (!ready.empty()) {
        const int current = ready.front();
        ready.pop();
        if (next[current] == -1) continue;
        balls[next[current]] += balls[current];
        if (--indegree[next[current]] == 0) ready.push(next[current]);
    }

    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            const int cell = row * columns + column;
            cout << (next[cell] == -1 ? balls[cell] : 0);
            cout << (column + 1 == columns ? '\n' : ' ');
        }
    }
    return 0;
}
