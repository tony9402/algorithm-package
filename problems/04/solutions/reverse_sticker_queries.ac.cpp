#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void rotateVector(array<int, 3>& value, int axis, int quarter) {
    int x = value[0];
    int y = value[1];
    int z = value[2];
    if (axis == 0) {
        value = quarter == 1 ? array<int, 3>{x, -z, y}
                             : array<int, 3>{x, z, -y};
    } else if (axis == 1) {
        value = quarter == 1 ? array<int, 3>{z, y, -x}
                             : array<int, 3>{-z, y, x};
    } else {
        value = quarter == 1 ? array<int, 3>{-y, x, z}
                             : array<int, 3>{y, -x, z};
    }
}

void moveInformation(char face, int& axis, int& layer) {
    if (face == 'U' || face == 'D') {
        axis = 1;
        layer = face == 'U' ? 1 : -1;
    } else if (face == 'F' || face == 'B') {
        axis = 2;
        layer = face == 'F' ? 1 : -1;
    } else {
        axis = 0;
        layer = face == 'R' ? 1 : -1;
    }
}

char initialColor(const array<int, 3>& normal) {
    if (normal[1] == 1) {
        return 'w';
    }
    if (normal[1] == -1) {
        return 'y';
    }
    if (normal[2] == 1) {
        return 'r';
    }
    if (normal[2] == -1) {
        return 'o';
    }
    return normal[0] == -1 ? 'g' : 'b';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCount;
    cin >> testCount;
    while (testCount--) {
        int moveCount;
        cin >> moveCount;
        vector<string> moves(moveCount);
        for (string& move : moves) {
            cin >> move;
        }

        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                array<int, 3> position = {col - 1, 1, row - 1};
                array<int, 3> normal = {0, 1, 0};
                for (int i = moveCount - 1; i >= 0; --i) {
                    int axis, layer;
                    moveInformation(moves[i][0], axis, layer);
                    if (position[axis] != layer) {
                        continue;
                    }
                    int forwardQuarter = moves[i][1] == '+' ? -layer : layer;
                    rotateVector(position, axis, -forwardQuarter);
                    rotateVector(normal, axis, -forwardQuarter);
                }
                cout << initialColor(normal);
            }
            cout << '\n';
        }
    }
    return 0;
}
