#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int n, m, area;
vector<vector<int>> a;
vector<pair<int, int>> chosen, cells;
int dr[4] = {-1, 0, 1, 0}, dc[4] = {0, 1, 0, -1};
int bfs() {
  vector<vector<int>> vis(n, vector<int>(n));
  queue<pair<int, int>> q;
  for (auto p : chosen) {
    q.push(p);
    vis[p.first][p.second] = 1;
  }
  int seen = 0, t = 0;
  while (!q.empty()) {
    int sz = q.size();
    while (sz--) {
      auto [r, c] = q.front();
      q.pop();
      if (a[r][c] != 1)
        seen++;
      for (int d = 0; d < 4; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (nr < 0 || nr >= n || nc < 0 || nc >= n || vis[nr][nc] ||
            a[nr][nc] == 1)
          continue;
        vis[nr][nc] = 1;
        q.push({nr, nc});
      }
    }
    if (seen == area)
      return t;
    t++;
  }
  return 1e9;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m;
  a.assign(n, vector<int>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      cin >> a[i][j];
      if (a[i][j] != 1)
        area++;
      if (a[i][j] == 2)
        cells.push_back({i, j});
    }
  int ans = 1e9;
  vector<int> pick(cells.size());
  fill(pick.begin(), pick.begin() + m, 1);
  sort(pick.rbegin(), pick.rend());
  do {
    chosen.clear();
    for (size_t i = 0; i < cells.size(); i++)
      if (pick[i])
        chosen.push_back(cells[i]);
    ans = min(ans, bfs());
  } while (prev_permutation(pick.begin(), pick.end()));
  cout << (ans == 1e9 ? -1 : ans);
}
