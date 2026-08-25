#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

const int DY[] = {-1, 1, 0, 0};
const int DX[] = {0, 0, -1, 1};

void print_lab(const vector<vector<int>> &lab, int active_count) {
  int n = (int)lab.size();
  cout << n << ' ' << active_count << '\n';
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (j)
        cout << ' ';
      cout << lab[i][j];
    }
    cout << '\n';
  }
}

void generate_random(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  int m = rnd.next(minM, min(maxM, n * n));
  vector<vector<int>> lab(n, vector<int>(n));
  vector<int> idx(n * n);
  iota(idx.begin(), idx.end(), 0);
  shuffle(idx.begin(), idx.end());

  int walls = rnd.next(0, n * n - m);
  for (int i = 0; i < walls; ++i)
    lab[idx[i] / n][idx[i] % n] = 1;
  for (int i = 0; i < m; ++i)
    lab[idx[walls + i] / n][idx[walls + i] % n] = 2;
  print_lab(lab, m);
}

void generate_random_v2(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  int m = rnd.next(minM, min(maxM, n * n));
  int virus_count = rnd.next(m, min(10, n * n));
  vector<vector<int>> lab(n, vector<int>(n, 1));
  vector<int> idx(n * n);
  iota(idx.begin(), idx.end(), 0);
  shuffle(idx.begin(), idx.end());

  priority_queue<tuple<int, int, int>> pq;
  for (int i = 0; i < virus_count; ++i) {
    int y = idx[i] / n;
    int x = idx[i] % n;
    lab[y][x] = 2;
    pq.emplace(rnd.next(1, 100000), y, x);
  }

  int open_target = rnd.next(virus_count, n * n);
  int opened = virus_count;
  while (!pq.empty() && opened < open_target) {
    auto [_, y, x] = pq.top();
    pq.pop();
    vector<int> order = rnd.perm(4, 0);
    for (int k : order) {
      int ny = y + DY[k];
      int nx = x + DX[k];
      if (ny < 0 || ny >= n || nx < 0 || nx >= n || lab[ny][nx] != 1)
        continue;
      lab[ny][nx] = 0;
      ++opened;
      pq.emplace(rnd.next(1, 100000), ny, nx);
      if (opened == open_target)
        break;
    }
  }
  print_lab(lab, m);
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 4);
  int maxN = opt<int>("maxN", 50);
  int minM = opt<int>("minM", 1);
  int maxM = opt<int>("maxM", 10);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN, minM, maxM);
  else if (mode == "random_v2")
    generate_random_v2(minN, maxN, minM, maxM);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
