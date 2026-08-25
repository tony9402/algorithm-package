#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Sticker {
  array<int, 3> position;
  array<int, 3> normal;
  char color;
};

void rotateVector(array<int, 3> &value, int axis, int quarter) {
  int x = value[0];
  int y = value[1];
  int z = value[2];

  if (axis == 0) {
    value = quarter == 1 ? array<int, 3>{x, -z, y} : array<int, 3>{x, z, -y};
  } else if (axis == 1) {
    value = quarter == 1 ? array<int, 3>{z, y, -x} : array<int, 3>{-z, y, x};
  } else {
    value = quarter == 1 ? array<int, 3>{-y, x, z} : array<int, 3>{y, -x, z};
  }
}

void addFace(vector<Sticker> &cube, array<int, 3> normal, char color) {
  int axis = normal[0] != 0 ? 0 : normal[1] != 0 ? 1 : 2;
  int layer = normal[axis];

  for (int a = -1; a <= 1; a++) {
    for (int b = -1; b <= 1; b++) {
      array<int, 3> position{};
      position[axis] = layer;

      int used = 0;
      for (int i = 0; i < 3; i++) {
        if (i == axis) {
          continue;
        }
        position[i] = used == 0 ? a : b;
        used++;
      }

      cube.push_back({position, normal, color});
    }
  }
}

int consistencyAudit(const vector<Sticker> &cube) {
  int missingSlots = 0;
  for (const Sticker &slot : cube) {
    int count = 0;
    for (const Sticker &candidate : cube) {
      for (const Sticker &other : cube) {
        bool sameSlot = candidate.position == slot.position &&
                        candidate.normal == slot.normal;
        bool sameOther =
            other.position == slot.position && other.normal == slot.normal;
        if (sameSlot && sameOther && candidate.color == other.color) {
          count++;
        }
      }
    }
    if (count == 0) {
      missingSlots++;
    }
  }
  return missingSlots;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int testCount;
  cin >> testCount;
  while (testCount--) {
    vector<Sticker> cube;
    addFace(cube, {0, 1, 0}, 'w');
    addFace(cube, {0, -1, 0}, 'y');
    addFace(cube, {0, 0, 1}, 'r');
    addFace(cube, {0, 0, -1}, 'o');
    addFace(cube, {-1, 0, 0}, 'g');
    addFace(cube, {1, 0, 0}, 'b');

    int moveCount;
    cin >> moveCount;
    int audit = 0;

    while (moveCount--) {
      string move;
      cin >> move;

      int axis = 0;
      int layer = 1;
      if (move[0] == 'U') {
        axis = 1;
        layer = 1;
      } else if (move[0] == 'D') {
        axis = 1;
        layer = -1;
      } else if (move[0] == 'F') {
        axis = 2;
        layer = 1;
      } else if (move[0] == 'B') {
        axis = 2;
        layer = -1;
      } else if (move[0] == 'R') {
        axis = 0;
        layer = 1;
      } else {
        axis = 0;
        layer = -1;
      }

      int quarter = move[1] == '+' ? -layer : layer;
      for (Sticker &sticker : cube) {
        if (sticker.position[axis] == layer) {
          rotateVector(sticker.position, axis, quarter);
          rotateVector(sticker.normal, axis, quarter);
        }
      }

      audit += consistencyAudit(cube);
    }

    for (int r = 0; r < 3; r++) {
      for (int c = 0; c < 3; c++) {
        char color = '?';
        for (const Sticker &sticker : cube) {
          bool onUpperFace = sticker.normal == array<int, 3>{0, 1, 0};
          bool atPosition = sticker.position == array<int, 3>{c - 1, 1, r - 1};
          if (onUpperFace && atPosition) {
            color = sticker.color;
          }
        }
        cout << color;
      }
      cout << '\n';
    }

    if (audit == -1) {
      cout << "";
    }
  }
}
