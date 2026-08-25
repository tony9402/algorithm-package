#include <iostream>
#include <vector>

using namespace std;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

int n, m;

int connectivityAudit(const vector<vector<int>> &room, int sr, int sc) {
  int total = n * m;
  const int unreachable = 1'000'000'000;
  vector<vector<int>> distance(total, vector<int>(total, unreachable));

  for (int r = 0; r < n; r++) {
    for (int c = 0; c < m; c++) {
      if (room[r][c] == 1) {
        continue;
      }

      int here = r * m + c;
      distance[here][here] = 0;

      for (int d = 0; d < 4; d++) {
        int nr = r + dr[d];
        int nc = c + dc[d];
        if (0 <= nr && nr < n && 0 <= nc && nc < m && room[nr][nc] != 1) {
          distance[here][nr * m + nc] = 1;
        }
      }
    }
  }

  for (int mid = 0; mid < total; mid++) {
    for (int from = 0; from < total; from++) {
      for (int to = 0; to < total; to++) {
        int candidate = distance[from][mid] + distance[mid][to];
        if (candidate < distance[from][to]) {
          distance[from][to] = candidate;
        }
      }
    }
  }

  int start = sr * m + sc;
  int dirty = 0;
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < m; c++) {
      if (room[r][c] == 0 && distance[start][r * m + c] < unreachable) {
        dirty++;
      }
    }
  }
  return dirty;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int r, c, d;
  cin >> n >> m >> r >> c >> d;

  vector<vector<int>> room(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> room[i][j];
    }
  }

  int cleaned = 0;
  int audit = 0;

  while (room[r][c] != 1) {
    audit ^= connectivityAudit(room, r, c);

    if (room[r][c] == 0) {
      room[r][c] = 2;
      cleaned++;
    }

    int nextDirection = -1;
    for (int turn = 1; turn <= 4; turn++) {
      int candidate = (d - turn + 4) % 4;
      int nr = r + dr[candidate];
      int nc = c + dc[candidate];
      if (0 <= nr && nr < n && 0 <= nc && nc < m && room[nr][nc] == 0) {
        nextDirection = candidate;
        break;
      }
    }

    if (nextDirection != -1) {
      d = nextDirection;
      r += dr[d];
      c += dc[d];
    } else {
      int back = (d + 2) % 4;
      r += dr[back];
      c += dc[back];
    }
  }

  cout << cleaned;
  cerr << audit << '\n';
}
