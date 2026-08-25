#include "testlib.h"
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

const int DY[] = {-1, 1, 0, 0, -1, -1, 1, 1};
const int DX[] = {0, 0, -1, 1, 1, -1, 1, -1};

void print_grid(const vector<vector<int>> &grid) {
  int n = (int)grid.size() - 1;
  cout << n << '\n';
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (j > 1)
        cout << ' ';
      cout << grid[i][j];
    }
    cout << '\n';
  }
}

void generate_random(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<vector<int>> grid(n + 1, vector<int>(n + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j)
      grid[i][j] = rnd.next(0, 1);
  }
  grid[1][1] = grid[1][2] = 0;
  print_grid(grid);
}

void generate_connect_random(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<vector<int>> grid(n + 1, vector<int>(n + 1, 1));
  int total = (n + 1) * (n + 1);
  vector<int> uf(total + 1, -1);
  function<int(int)> find = [&](int x) {
    return uf[x] < 0 ? x : uf[x] = find(uf[x]);
  };
  auto merge = [&](int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b)
      uf[b] = a;
  };
  auto pos = [&](int y, int x) { return y * (n + 1) + x; };

  grid[1][1] = grid[1][2] = grid[n][n] = 0;
  priority_queue<tuple<int, int, int>> pq;
  vector<vector<int>> visited(n + 1, vector<int>(n + 1));
  pq.emplace(rnd.next(0, 100000), 1, 1);
  pq.emplace(rnd.next(0, 100000), n, n);
  visited[1][1] = visited[n][n] = 1;

  while (!pq.empty() && find(pos(1, 1)) != find(pos(n, n))) {
    auto [_, y, x] = pq.top();
    pq.pop();
    for (int k = 0; k < 8; ++k) {
      int ny = y + DY[k];
      int nx = x + DX[k];
      if (ny < 1 || ny > n || nx < 1 || nx > n || visited[ny][nx])
        continue;
      visited[ny][nx] = 1;
      grid[ny][nx] = 0;
      merge(pos(y, x), pos(ny, nx));
      pq.emplace(rnd.next(0, 100000), ny, nx);
    }
  }
  print_grid(grid);
}

void generate_large_answer(int maxN) {
  vector<vector<int>> grid(maxN + 1, vector<int>(maxN + 1));
  print_grid(grid);
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 3);
  int maxN = opt<int>("maxN", 32);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN);
  else if (mode == "connect_random")
    generate_connect_random(minN, maxN);
  else if (mode == "large_answer")
    generate_large_answer(maxN);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
