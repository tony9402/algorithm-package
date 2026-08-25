#include "testlib.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print_grid(const vector<vector<int>> &grid, int r, int c, int d) {
  int n = (int)grid.size();
  int m = (int)grid[0].size();
  cout << n << ' ' << m << '\n';
  cout << r << ' ' << c << ' ' << d << '\n';
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (j)
        cout << ' ';
      cout << grid[i][j];
    }
    cout << '\n';
  }
}

void generate_random(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  int m = rnd.next(minM, maxM);
  vector<vector<int>> grid(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      grid[i][j] =
          (i == 0 || i + 1 == n || j == 0 || j + 1 == m) ? 1 : rnd.next(0, 1);
    }
  }
  int r = rnd.next(1, n - 2);
  int c = rnd.next(1, m - 2);
  int d = rnd.next(0, 3);
  grid[r][c] = 0;
  print_grid(grid, r, c, d);
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 3);
  int maxN = opt<int>("maxN", 50);
  int minM = opt<int>("minM", 3);
  int maxM = opt<int>("maxM", 50);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN, minM, maxM);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
