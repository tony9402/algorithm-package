#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Sticker {
    array<int, 3> pos;
    array<int, 3> normal;
    char color;
};

void rotateVec(array<int, 3>& v, int axis, int quarter) {
    int x = v[0], y = v[1], z = v[2];
    if (axis == 0) {
        if (quarter == 1) v = {x, -z, y};
        else v = {x, z, -y};
    } else if (axis == 1) {
        if (quarter == 1) v = {z, y, -x};
        else v = {-z, y, x};
    } else {
        if (quarter == 1) v = {-y, x, z};
        else v = {y, -x, z};
    }
}

void rotateLayer(vector<Sticker>& cube, char face, char direction) {
    int axis = 0;
    int layer = 1;
    if (face == 'U') axis = 1, layer = 1;
    if (face == 'D') axis = 1, layer = -1;
    if (face == 'F') axis = 2, layer = 1;
    if (face == 'B') axis = 2, layer = -1;
    if (face == 'R') axis = 0, layer = 1;
    if (face == 'L') axis = 0, layer = -1;

    int quarter = direction == '+' ? -layer : layer;
    for (Sticker& sticker : cube) {
        if (sticker.pos[axis] != layer) continue;
        rotateVec(sticker.pos, axis, quarter);
        rotateVec(sticker.normal, axis, quarter);
    }
}

vector<Sticker> makeCube() {
    vector<Sticker> cube;
    auto addFace = [&](array<int, 3> normal, char color) {
        int axis = normal[0] ? 0 : normal[1] ? 1 : 2;
        int layer = normal[axis];
        for (int a = -1; a <= 1; ++a) {
            for (int b = -1; b <= 1; ++b) {
                array<int, 3> pos{};
                pos[axis] = layer;
                int idx = 0;
                for (int i = 0; i < 3; ++i) {
                    if (i == axis) continue;
                    pos[i] = idx++ == 0 ? a : b;
                }
                cube.push_back({pos, normal, color});
            }
        }
    };

    addFace({0, 1, 0}, 'w');
    addFace({0, -1, 0}, 'y');
    addFace({0, 0, 1}, 'r');
    addFace({0, 0, -1}, 'o');
    addFace({-1, 0, 0}, 'g');
    addFace({1, 0, 0}, 'b');
    return cube;
}

char upperColor(const vector<Sticker>& cube, int row, int col) {
    int z = row - 1;
    int x = col - 1;
    for (const Sticker& sticker : cube) {
        if (sticker.normal == array<int, 3>{0, 1, 0} && sticker.pos == array<int, 3>{x, 1, z}) {
            return sticker.color;
        }
    }
    return '?';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<Sticker> cube = makeCube();
        for (int i = 0; i < n; ++i) {
            string move;
            cin >> move;
            rotateLayer(cube, move[0], move[1]);
        }
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) cout << upperColor(cube, row, col);
            cout << '\n';
        }
    }
    return 0;
}
