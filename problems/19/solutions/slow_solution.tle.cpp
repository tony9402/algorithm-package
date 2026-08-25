#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> g;
int best;
int dr[5] = {0, -1, 0, 1, 0}, dc[5] = {0, 0, 1, 0, -1};
void press(vector<vector<int>> &a, int r, int c) {
  for (int k = 0; k < 5; k++) {
    int nr = r + dr[k], nc = c + dc[k];
    if (0 <= nr && nr < n && 0 <= nc && nc < n)
      a[nr][nc] ^= 1;
  }
}
void dfs(int idx, vector<vector<int>> &a, int cnt) {
  if (cnt >= best)
    return;
  if (idx == n * n) {
    for (auto &row : a)
      for (int x : row)
        if (x)
          return;
    best = cnt;
    return;
  }
  dfs(idx + 1, a, cnt);
  press(a, idx / n, idx % n);
  dfs(idx + 1, a, cnt + 1);
  press(a, idx / n, idx % n);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  g.assign(n, vector<int>(n));
  for (auto &row : g)
    for (int &x : row)
      cin >> x;
  best = n * n + 1;
  dfs(0, g, 0);
  cout << (best == n * n + 1 ? -1 : best);
}