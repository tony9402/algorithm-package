#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int R, C;
  cin >> R >> C;
  vector<vector<int>> v(R, vector<int>(C));
  for (auto &row : v)
    for (int &x : row)
      cin >> x;
  int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};
  vector<int> parent(R * C, -1), sz(R * C, 1);
  function<int(int)> find = [&](int x) {
    return parent[x] < 0 ? x : parent[x] = find(parent[x]);
  };
  auto merge = [&](int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b)
      return;
    if (v[a / C][a % C] > v[b / C][b % C])
      swap(a, b);
    parent[b] = a;
    sz[a] += sz[b];
  };
  for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++) {
      int bi = -1, bj = -1, b = v[i][j];
      for (int d = 0; d < 4; d++) {
        int ni = i + dy[d], nj = j + dx[d];
        if (0 <= ni && ni < R && 0 <= nj && nj < C && v[ni][nj] < b) {
          b = v[ni][nj];
          bi = ni;
          bj = nj;
        }
      }
      if (bi != -1)
        merge(i * C + j, bi * C + bj);
    }
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      int id = i * C + j;
      cout << (find(id) == id ? sz[id] : 0) << (j + 1 == C ? '\n' : ' ');
    }
  }
}