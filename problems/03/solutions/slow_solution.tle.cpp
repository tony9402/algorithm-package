#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

struct Heater {
  int r;
  int c;
  int d;
};

struct Wall {
  int r;
  int c;
  int t;
};

struct State {
  int r;
  int c;
  int power;
};

int absValue(int value) {
  if (value < 0) {
    return -value;
  }
  return value;
}

bool inside(int r, int c, int rows, int cols) {
  return 0 <= r && r < rows && 0 <= c && c < cols;
}

bool blockedByWall(int r1, int c1, int r2, int c2, const vector<Wall> &walls) {
  if (r1 > r2 || c1 > c2) {
    return blockedByWall(r2, c2, r1, c1, walls);
  }

  for (const Wall &wall : walls) {
    if (wall.t == 0) {
      int upperR = wall.r - 1;
      int lowerR = wall.r;
      if (r1 == upperR && c1 == wall.c && r2 == lowerR && c2 == wall.c) {
        return true;
      }
    } else {
      int leftC = wall.c;
      int rightC = wall.c + 1;
      if (r1 == wall.r && c1 == leftC && r2 == wall.r && c2 == rightC) {
        return true;
      }
    }
  }

  return false;
}

bool canMove(int r1, int c1, int r2, int c2, int rows, int cols,
             const vector<Wall> &walls) {
  return inside(r2, c2, rows, cols) && !blockedByWall(r1, c1, r2, c2, walls);
}

void blowHeater(vector<vector<int>> &temperature, const Heater &heater,
                const vector<Wall> &walls) {
  int rows = temperature.size();
  int cols = temperature[0].size();
  int dr[4] = {0, 0, -1, 1};
  int dc[4] = {1, -1, 0, 0};

  int sr = heater.r + dr[heater.d];
  int sc = heater.c + dc[heater.d];
  if (!inside(sr, sc, rows, cols)) {
    return;
  }

  vector<vector<int>> visited(rows, vector<int>(cols));
  queue<State> q;
  visited[sr][sc] = 1;
  q.push({sr, sc, 5});

  while (!q.empty()) {
    State cur = q.front();
    q.pop();

    temperature[cur.r][cur.c] += cur.power;
    if (cur.power == 1) {
      continue;
    }

    for (int side = -1; side <= 1; side++) {
      int firstR = cur.r;
      int firstC = cur.c;

      if (side != 0) {
        if (heater.d < 2) {
          firstR += side;
        } else {
          firstC += side;
        }
      }

      if (!inside(firstR, firstC, rows, cols)) {
        continue;
      }
      if (side != 0 && blockedByWall(cur.r, cur.c, firstR, firstC, walls)) {
        continue;
      }

      int nr = firstR + dr[heater.d];
      int nc = firstC + dc[heater.d];
      if (!canMove(firstR, firstC, nr, nc, rows, cols, walls)) {
        continue;
      }
      if (visited[nr][nc]) {
        continue;
      }

      visited[nr][nc] = 1;
      q.push({nr, nc, cur.power - 1});
    }
  }
}

void balanceTemperature(vector<vector<int>> &temperature,
                        const vector<Wall> &walls) {
  int rows = temperature.size();
  int cols = temperature[0].size();
  int cellCount = rows * cols;
  const int unreachable = 1'000'000'000;
  vector<vector<int>> distance(cellCount, vector<int>(cellCount, unreachable));

  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      int from = r * cols + c;
      distance[from][from] = 0;

      for (int nr = 0; nr < rows; nr++) {
        for (int nc = 0; nc < cols; nc++) {
          if (absValue(r - nr) + absValue(c - nc) != 1) {
            continue;
          }
          if (!blockedByWall(r, c, nr, nc, walls)) {
            distance[from][nr * cols + nc] = 1;
          }
        }
      }
    }
  }

  for (int mid = 0; mid < cellCount; mid++) {
    for (int from = 0; from < cellCount; from++) {
      if (distance[from][mid] == unreachable) {
        continue;
      }
      for (int to = 0; to < cellCount; to++) {
        int candidate = distance[from][mid] + distance[mid][to];
        if (candidate < distance[from][to]) {
          distance[from][to] = candidate;
        }
      }
    }
  }

  vector<vector<int>> delta(rows, vector<int>(cols));

  for (int r1 = 0; r1 < rows; r1++) {
    for (int c1 = 0; c1 < cols; c1++) {
      for (int r2 = 0; r2 < rows; r2++) {
        for (int c2 = 0; c2 < cols; c2++) {
          int first = r1 * cols + c1;
          int second = r2 * cols + c2;
          if (first >= second) {
            continue;
          }
          if (distance[first][second] != 1) {
            continue;
          }

          int diff = absValue(temperature[r1][c1] - temperature[r2][c2]) / 4;
          if (temperature[r1][c1] > temperature[r2][c2]) {
            delta[r1][c1] -= diff;
            delta[r2][c2] += diff;
          } else {
            delta[r1][c1] += diff;
            delta[r2][c2] -= diff;
          }
        }
      }
    }
  }

  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      temperature[r][c] += delta[r][c];
    }
  }
}

unsigned long long thermalAudit(const vector<vector<int>> &temperature) {
  int rows = temperature.size();
  int cols = temperature[0].size();
  int cellCount = rows * cols;
  unsigned long long total = 0;

  for (int from = 0; from < cellCount; from++) {
    int fromR = from / cols;
    int fromC = from % cols;
    for (int through = 0; through < cellCount; through++) {
      int throughR = through / cols;
      int throughC = through % cols;
      int firstDiff =
          absValue(temperature[fromR][fromC] - temperature[throughR][throughC]);

      for (int to = 0; to < cellCount; to++) {
        int toR = to / cols;
        int toC = to % cols;
        int secondDiff =
            absValue(temperature[throughR][throughC] - temperature[toR][toC]);

        for (int probe = 0; probe < cellCount; probe++) {
          int probeR = probe / cols;
          int probeC = probe % cols;
          int thirdDiff =
              absValue(temperature[toR][toC] - temperature[probeR][probeC]);
          total += firstDiff + secondDiff + thirdDiff;
        }
      }
    }
  }

  return total;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int rows, cols, target;
  cin >> rows >> cols >> target;

  vector<Heater> heaters;
  vector<pair<int, int>> checkpoints;
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      int value;
      cin >> value;
      if (1 <= value && value <= 4) {
        heaters.push_back({r, c, value - 1});
      } else if (value == 5) {
        checkpoints.push_back({r, c});
      }
    }
  }

  int wallCount;
  cin >> wallCount;
  vector<Wall> walls(wallCount);
  for (Wall &wall : walls) {
    cin >> wall.r >> wall.c >> wall.t;
    wall.r--;
    wall.c--;
  }

  vector<vector<int>> temperature(rows, vector<int>(cols));
  unsigned long long diagnostic = 0;

  for (int chocolate = 1; chocolate <= 101; chocolate++) {
    for (const Heater &heater : heaters) {
      blowHeater(temperature, heater, walls);
    }

    balanceTemperature(temperature, walls);
    diagnostic ^= thermalAudit(temperature);

    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < cols; c++) {
        bool edge = r == 0 || c == 0 || r + 1 == rows || c + 1 == cols;
        if (edge && temperature[r][c] > 0) {
          temperature[r][c]--;
        }
      }
    }

    bool ready = true;
    for (const auto &[r, c] : checkpoints) {
      ready = ready && temperature[r][c] >= target;
    }

    if (ready) {
      cout << chocolate;
      cerr << diagnostic << '\n';
      return 0;
    }
  }

  cout << 101;
  cerr << diagnostic << '\n';
}
