#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

struct Heater {
  int r;
  int c;
  int d;
};

vector<int> valid_directions(int row, int col, int r, int c) {
  vector<int> dirs;
  if (col < c)
    dirs.push_back(1);
  if (col > 1)
    dirs.push_back(2);
  if (row > 1)
    dirs.push_back(3);
  if (row < r)
    dirs.push_back(4);
  return dirs;
}

void print_case(int r, int c, int k, const vector<vector<int>> &board,
                const vector<tuple<int, int, int>> &walls) {
  cout << r << ' ' << c << ' ' << k << '\n';
  for (int row = 1; row <= r; ++row) {
    for (int col = 1; col <= c; ++col) {
      if (col > 1)
        cout << ' ';
      cout << board[row][col];
    }
    cout << '\n';
  }
  cout << walls.size() << '\n';
  for (auto [row, col, t] : walls)
    cout << row << ' ' << col << ' ' << t << '\n';
}

void generate_random(int minR, int maxR, int minC, int maxC, int minK, int maxK,
                     int maxHeaters, int maxChecks) {
  int r = rnd.next(minR, maxR);
  int c = rnd.next(minC, maxC);
  int k = rnd.next(minK, maxK);
  vector<vector<int>> board(r + 1, vector<int>(c + 1));
  vector<Heater> heaters;

  vector<pair<int, int>> cells;
  for (int row = 1; row <= r; ++row) {
    for (int col = 1; col <= c; ++col)
      cells.push_back({row, col});
  }
  shuffle(cells.begin(), cells.end());

  int heater_limit = max(1, min<int>((int)cells.size() / 4, maxHeaters));
  int heater_count = rnd.next(1, heater_limit);
  int cursor = 0;
  while ((int)heaters.size() < heater_count && cursor < (int)cells.size()) {
    auto [row, col] = cells[cursor++];
    vector<int> dirs = valid_directions(row, col, r, c);
    if (dirs.empty())
      continue;
    int d = dirs[rnd.next(0, (int)dirs.size() - 1)];
    board[row][col] = d;
    heaters.push_back({row, col, d});
  }
  if (heaters.empty()) {
    board[1][1] = 1;
    heaters.push_back({1, 1, 1});
  }

  int check_limit = max(1, min<int>((int)cells.size() / 3, maxChecks));
  int check_count = rnd.next(1, check_limit);
  int checks = 0;
  for (auto [row, col] : cells) {
    if (checks == check_count)
      break;
    if (board[row][col] != 0)
      continue;
    board[row][col] = 5;
    ++checks;
  }
  if (checks == 0) {
    for (int row = 1; row <= r && checks == 0; ++row) {
      for (int col = 1; col <= c && checks == 0; ++col) {
        if (board[row][col] == 0) {
          board[row][col] = 5;
          checks = 1;
        }
      }
    }
  }

  set<tuple<int, int, int>> blocked_walls;
  for (const Heater &h : heaters) {
    if (h.d == 1)
      blocked_walls.insert({h.r, h.c, 1});
    if (h.d == 2)
      blocked_walls.insert({h.r, h.c - 1, 1});
    if (h.d == 3)
      blocked_walls.insert({h.r, h.c, 0});
    if (h.d == 4)
      blocked_walls.insert({h.r + 1, h.c, 0});
  }

  vector<tuple<int, int, int>> candidates;
  for (int row = 2; row <= r; ++row) {
    for (int col = 1; col <= c; ++col)
      candidates.push_back({row, col, 0});
  }
  for (int row = 1; row <= r; ++row) {
    for (int col = 1; col < c; ++col)
      candidates.push_back({row, col, 1});
  }
  shuffle(candidates.begin(), candidates.end());

  vector<tuple<int, int, int>> walls;
  int wall_limit = rnd.next(0, min<int>(r * c, (int)candidates.size()));
  for (auto wall : candidates) {
    if ((int)walls.size() >= wall_limit)
      break;
    if (blocked_walls.count(wall))
      continue;
    walls.push_back(wall);
  }

  print_case(r, c, k, board, walls);
}

void generate_open(int minR, int maxR, int minC, int maxC, int minK, int maxK,
                   int maxHeaters, int maxChecks) {
  int r = rnd.next(minR, maxR);
  int c = rnd.next(minC, maxC);
  int k = rnd.next(minK, maxK);
  vector<vector<int>> board(r + 1, vector<int>(c + 1));
  vector<Heater> heaters;

  vector<pair<int, int>> cells;
  for (int row = 1; row <= r; ++row) {
    for (int col = 1; col <= c; ++col)
      cells.push_back({row, col});
  }
  shuffle(cells.begin(), cells.end());

  int heater_limit = max(1, min<int>((int)cells.size() / 4, maxHeaters));
  int heater_count = rnd.next(1, heater_limit);
  int cursor = 0;
  while ((int)heaters.size() < heater_count && cursor < (int)cells.size()) {
    auto [row, col] = cells[cursor++];
    vector<int> dirs = valid_directions(row, col, r, c);
    if (dirs.empty())
      continue;
    int d = dirs[rnd.next(0, (int)dirs.size() - 1)];
    board[row][col] = d;
    heaters.push_back({row, col, d});
  }
  if (heaters.empty()) {
    board[1][1] = 1;
    heaters.push_back({1, 1, 1});
  }

  int check_limit = max(1, min<int>((int)cells.size() / 3, maxChecks));
  int check_count = rnd.next(1, check_limit);
  int checks = 0;
  for (auto [row, col] : cells) {
    if (checks == check_count)
      break;
    if (board[row][col] != 0)
      continue;
    board[row][col] = 5;
    ++checks;
  }
  if (checks == 0) {
    for (int row = 1; row <= r && checks == 0; ++row) {
      for (int col = 1; col <= c && checks == 0; ++col) {
        if (board[row][col] == 0) {
          board[row][col] = 5;
          checks = 1;
        }
      }
    }
  }

  vector<tuple<int, int, int>> walls;
  print_case(r, c, k, board, walls);
}

void generate_dense_walls(int minR, int maxR, int minC, int maxC, int minK,
                          int maxK, int maxHeaters, int maxChecks) {
  int r = rnd.next(minR, maxR);
  int c = rnd.next(minC, maxC);
  int k = rnd.next(minK, maxK);
  vector<vector<int>> board(r + 1, vector<int>(c + 1));
  vector<Heater> heaters;

  vector<pair<int, int>> cells;
  for (int row = 1; row <= r; ++row) {
    for (int col = 1; col <= c; ++col)
      cells.push_back({row, col});
  }
  shuffle(cells.begin(), cells.end());

  int heater_limit = max(1, min<int>((int)cells.size() / 4, maxHeaters));
  int heater_count = rnd.next(1, heater_limit);
  int cursor = 0;
  while ((int)heaters.size() < heater_count && cursor < (int)cells.size()) {
    auto [row, col] = cells[cursor++];
    vector<int> dirs = valid_directions(row, col, r, c);
    if (dirs.empty())
      continue;
    int d = dirs[rnd.next(0, (int)dirs.size() - 1)];
    board[row][col] = d;
    heaters.push_back({row, col, d});
  }
  if (heaters.empty()) {
    board[1][1] = 1;
    heaters.push_back({1, 1, 1});
  }

  int check_limit = max(1, min<int>((int)cells.size() / 3, maxChecks));
  int check_count = rnd.next(1, check_limit);
  int checks = 0;
  for (auto [row, col] : cells) {
    if (checks == check_count)
      break;
    if (board[row][col] != 0)
      continue;
    board[row][col] = 5;
    ++checks;
  }
  if (checks == 0) {
    for (int row = 1; row <= r && checks == 0; ++row) {
      for (int col = 1; col <= c && checks == 0; ++col) {
        if (board[row][col] == 0) {
          board[row][col] = 5;
          checks = 1;
        }
      }
    }
  }

  set<tuple<int, int, int>> blocked_walls;
  for (const Heater &h : heaters) {
    if (h.d == 1)
      blocked_walls.insert({h.r, h.c, 1});
    if (h.d == 2)
      blocked_walls.insert({h.r, h.c - 1, 1});
    if (h.d == 3)
      blocked_walls.insert({h.r, h.c, 0});
    if (h.d == 4)
      blocked_walls.insert({h.r + 1, h.c, 0});
  }

  vector<tuple<int, int, int>> candidates;
  for (int row = 2; row <= r; ++row) {
    for (int col = 1; col <= c; ++col)
      candidates.push_back({row, col, 0});
  }
  for (int row = 1; row <= r; ++row) {
    for (int col = 1; col < c; ++col)
      candidates.push_back({row, col, 1});
  }
  shuffle(candidates.begin(), candidates.end());

  vector<tuple<int, int, int>> walls;
  int wall_limit = min<int>(r * c, (int)candidates.size());
  for (auto wall : candidates) {
    if ((int)walls.size() >= wall_limit)
      break;
    if (blocked_walls.count(wall))
      continue;
    walls.push_back(wall);
  }

  print_case(r, c, k, board, walls);
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minR = opt<int>("minR", 2);
  int maxR = opt<int>("maxR", 20);
  int minC = opt<int>("minC", 2);
  int maxC = opt<int>("maxC", 20);
  int minK = opt<int>("minK", 1);
  int maxK = opt<int>("maxK", 1000);
  int maxHeaters = opt<int>("maxHeaters", 10);
  int maxChecks = opt<int>("maxChecks", 12);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minR, maxR, minC, maxC, minK, maxK, maxHeaters, maxChecks);
  else if (mode == "open")
    generate_open(minR, maxR, minC, maxC, minK, maxK, maxHeaters, maxChecks);
  else if (mode == "dense_walls")
    generate_dense_walls(minR, maxR, minC, maxC, minK, maxK, maxHeaters,
                         maxChecks);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
