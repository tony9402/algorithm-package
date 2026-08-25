#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

const int LIMIT = 200000;
const int INF = 1000000000;

int solve_with_repeated_relaxation(int start, int target) {
  vector<int> dist(LIMIT + 1, INF);
  dist[start] = 0;

  for (int pass = 0; pass <= target; pass++) {
    vector<int> next = dist;
    for (int cur = 0; cur <= LIMIT; cur++) {
      if (dist[cur] == INF) {
        continue;
      }
      if (cur * 2 <= LIMIT) {
        next[cur * 2] = min(next[cur * 2], dist[cur]);
      }
      if (cur > 0) {
        next[cur - 1] = min(next[cur - 1], dist[cur] + 1);
      }
      if (cur < LIMIT) {
        next[cur + 1] = min(next[cur + 1], dist[cur] + 1);
      }
    }
    dist.swap(next);
  }

  return dist[target];
}

int solve_with_deque(int start, int target) {
  vector<int> dist(LIMIT + 1, INF);
  deque<int> q;
  dist[start] = 0;
  q.push_back(start);

  while (!q.empty()) {
    int cur = q.front();
    q.pop_front();
    if (cur == target) {
      break;
    }
    if (cur * 2 <= LIMIT && dist[cur * 2] > dist[cur]) {
      dist[cur * 2] = dist[cur];
      q.push_front(cur * 2);
    }
    if (cur > 0 && dist[cur - 1] > dist[cur] + 1) {
      dist[cur - 1] = dist[cur] + 1;
      q.push_back(cur - 1);
    }
    if (cur < LIMIT && dist[cur + 1] > dist[cur] + 1) {
      dist[cur + 1] = dist[cur] + 1;
      q.push_back(cur + 1);
    }
  }

  return dist[target];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;
  if (n >= k) {
    cout << n - k;
    return 0;
  }
  if (n == 0) {
    cout << solve_with_repeated_relaxation(n, k);
    return 0;
  }

  cout << solve_with_deque(n, k);
}
