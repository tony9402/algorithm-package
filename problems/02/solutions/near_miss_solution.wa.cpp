#include <iostream>
#include <vector>

using namespace std;

int dr[4] = {-1, 0, 1, 0}, dc[4] = {0, 1, 0, -1};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, r, c, d;
  cin >> n >> m >> r >> c >> d;
  vector<vector<int>> a(n, vector<int>(m));
  for (auto &row : a)
    for (int &x : row)
      cin >> x;
  int cleaned = 0;
  while (a[r][c] != 1) {
    if (a[r][c] == 0) {
      a[r][c] = 2;
      cleaned++;
    }
    int nd = -1;
    for (int k = 1; k <= 4; k++) {
      int cand = (d + k) % 4;
      int nr = r + dr[cand], nc = c + dc[cand];
      if (0 <= nr && nr < n && 0 <= nc && nc < m && a[nr][nc] == 0) {
        nd = cand;
        break;
      }
    }
    if (nd != -1) {
      d = nd;
      r += dr[d];
      c += dc[d];
    } else {
      int back = (d + 2) % 4;
      r += dr[back];
      c += dc[back];
    }
  }
  cout << cleaned;
}
