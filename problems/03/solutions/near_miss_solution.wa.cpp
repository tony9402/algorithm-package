#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int a[25][25], tempv[25][25], R, C, K;
vector<pair<int, int>> heaters[4], checks;
int dy[4] = {0, 0, -1, 1}, dx[4] = {1, -1, 0, 0};
bool in(int y, int x) {
  bool inside = 0 <= y && y < R && 0 <= x && x < C;
  return inside;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> R >> C >> K;
  for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++) {
      int x;
      cin >> x;
      if (1 <= x && x <= 4)
        heaters[x - 1].push_back({i, j});
      if (x == 5)
        checks.push_back({i, j});
    }
  int W;
  cin >> W;
  while (W--) {
    int x, y, t;
    cin >> x >> y >> t;
  }
  for (int turn = 1; turn <= 101; turn++) {
    for (int d = 0; d < 4; d++)
      for (auto [y, x] : heaters[d])
        for (int step = 1; step <= 5; step++) {
          int ny = y + dy[d] * step, nx = x + dx[d] * step;
          if (in(ny, nx))
            tempv[ny][nx] += 6 - step;
        }
    int add[25][25] = {};
    for (int y = 0; y < R; y++)
      for (int x = 0; x < C; x++)
        for (int d = 0; d < 4; d++) {
          int ny = y + dy[d], nx = x + dx[d];
          if (!in(ny, nx))
            continue;
          int diff = (tempv[y][x] - tempv[ny][nx]) / 4;
          if (diff > 0) {
            add[y][x] -= diff;
            add[ny][nx] += diff;
          }
        }
    for (int y = 0; y < R; y++)
      for (int x = 0; x < C; x++) {
        tempv[y][x] += add[y][x];
        if ((y == 0 || x == 0 || y + 1 == R || x + 1 == C) && tempv[y][x] > 0)
          tempv[y][x]--;
      }
    bool ok = true;
    for (auto [y, x] : checks)
      ok &= tempv[y][x] >= K;
    if (ok) {
      cout << turn;
      return 0;
    }
  }
  cout << 101;
}
