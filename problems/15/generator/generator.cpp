#include "testlib.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print_grid(const vector<string> &grid) {
  int n = (int)grid.size();
  int m = (int)grid[0].size();
  cout << n << ' ' << m << '\n';
  for (const string &row : grid)
    cout << row << '\n';
}

void generate_random(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  int m = rnd.next(minM, maxM);
  vector<string> grid(n, string(m, '0'));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      grid[i][j] = char('0' + rnd.next(0, 1));
    }
  }
  print_grid(grid);
}

void generate_sparse(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  int m = rnd.next(minM, maxM);
  vector<string> grid(n, string(m, '0'));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      grid[i][j] = rnd.next(0, 9) == 0 ? '1' : '0';
    }
  }
  print_grid(grid);
}

void generate_dense(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  int m = rnd.next(minM, maxM);
  vector<string> grid(n, string(m, '0'));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      grid[i][j] = rnd.next(0, 9) < 8 ? '1' : '0';
    }
  }
  print_grid(grid);
}

void generate_checkerboard(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  int m = rnd.next(minM, maxM);
  vector<string> grid(n, string(m, '0'));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      grid[i][j] = char('0' + ((i + j) & 1));
    }
  }
  print_grid(grid);
}

void generate_full(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  int m = rnd.next(minM, maxM);
  vector<string> grid(n, string(m, '1'));
  print_grid(grid);
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 1000);
  int minM = opt<int>("minM", 1);
  int maxM = opt<int>("maxM", 1000);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN, minM, maxM);
  else if (mode == "sparse")
    generate_sparse(minN, maxN, minM, maxM);
  else if (mode == "dense")
    generate_dense(minN, maxN, minM, maxM);
  else if (mode == "checkerboard")
    generate_checkerboard(minN, maxN, minM, maxM);
  else if (mode == "full")
    generate_full(minN, maxN, minM, maxM);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
