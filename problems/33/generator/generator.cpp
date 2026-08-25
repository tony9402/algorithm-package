#include "testlib.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void fill_block(vector<string> &grid, int r, int c, int len, char value) {
  for (int i = r; i < r + len; ++i) {
    for (int j = c; j < c + len; ++j)
      grid[i][j] = value;
  }
}

void make_blocky(vector<string> &grid, int r, int c, int len) {
  if (len == 1 || rnd.next(0, 99) < 35) {
    fill_block(grid, r, c, len, char('0' + rnd.next(0, 1)));
    return;
  }
  int half = len / 2;
  make_blocky(grid, r, c, half);
  make_blocky(grid, r, c + half, half);
  make_blocky(grid, r + half, c, half);
  make_blocky(grid, r + half, c + half, half);
}

void print_grid(const vector<string> &grid) {
  cout << grid.size() << '\n';
  for (const string &row : grid)
    cout << row << '\n';
}

void generate_random(int exp) {
  int n = 1 << exp;
  vector<string> grid(n, string(n, '0'));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j)
      grid[i][j] = char('0' + rnd.next(0, 1));
  }
  print_grid(grid);
}

void generate_blocky(int exp) {
  int n = 1 << exp;
  vector<string> grid(n, string(n, '0'));
  make_blocky(grid, 0, 0, n);
  print_grid(grid);
}

void generate_zero(int exp) {
  int n = 1 << exp;
  print_grid(vector<string>(n, string(n, '0')));
}

void generate_one(int exp) {
  int n = 1 << exp;
  print_grid(vector<string>(n, string(n, '1')));
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int exp = opt<int>("exp", 3);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(exp);
  else if (mode == "blocky")
    generate_blocky(exp);
  else if (mode == "zero")
    generate_zero(exp);
  else if (mode == "one")
    generate_one(exp);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
