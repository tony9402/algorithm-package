#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

const int INF = 1000000000;
const int DR[4] = {-1, 0, 1, 0};
const int DC[4] = {0, 1, 0, -1};

int n, m, empty_count;
vector<vector<int>> board;
vector<pair<int, int>> viruses;
vector<pair<int, int>> chosen;

int simulate() {
  int cells = n * n;
  vector<vector<int>> dist(cells, vector<int>(cells, INF));

  for (int r = 0; r < n; r++) {
    for (int c = 0; c < n; c++) {
      if (board[r][c] == 1) {
        continue;
      }
      int id = r * n + c;
      dist[id][id] = 0;
      for (int d = 0; d < 4; d++) {
        int nr = r + DR[d];
        int nc = c + DC[d];
        if (nr < 0 || nr >= n || nc < 0 || nc >= n || board[nr][nc] == 1) {
          continue;
        }
        dist[id][nr * n + nc] = 1;
      }
    }
  }

  for (int mid = 0; mid < cells; mid++) {
    for (int from = 0; from < cells; from++) {
      if (dist[from][mid] == INF) {
        continue;
      }
      for (int to = 0; to < cells; to++) {
        if (dist[mid][to] == INF) {
          continue;
        }
        dist[from][to] = min(dist[from][to], dist[from][mid] + dist[mid][to]);
      }
    }
  }

  int filled = 0;
  int last = 0;
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < n; c++) {
      if (board[r][c] != 0) {
        continue;
      }
      int best = INF;
      int target = r * n + c;
      for (auto [vr, vc] : chosen) {
        best = min(best, dist[vr * n + vc][target]);
      }
      if (best == INF) {
        continue;
      }
      filled++;
      last = max(last, best);
    }
  }

  return filled == empty_count ? last : INF;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  board.assign(n, vector<int>(n));
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < n; c++) {
      cin >> board[r][c];
      if (board[r][c] == 0) {
        empty_count++;
      }
      if (board[r][c] == 2) {
        viruses.push_back({r, c});
      }
    }
  }

  int answer = INF;
  int total = 1;
  for (size_t i = 0; i < viruses.size(); i++) {
    total *= 2;
  }

  for (int mask = 0; mask < total; mask++) {
    if (__builtin_popcount((unsigned)mask) != m) {
      continue;
    }
    chosen.clear();
    for (size_t i = 0; i < viruses.size(); i++) {
      if (mask & (1 << i)) {
        chosen.push_back(viruses[i]);
      }
    }
    answer = min(answer, simulate());
  }

  cout << (answer == INF ? -1 : answer);
}
