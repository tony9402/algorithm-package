#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> pop(n);
  int total = 0;
  for (int &x : pop) {
    cin >> x;
    total += x;
  }
  vector<vector<int>> g(n);
  for (int i = 0; i < n; i++) {
    int c;
    cin >> c;
    while (c--) {
      int v;
      cin >> v;
      g[i].push_back(v - 1);
    }
  }
  auto conn = [&](int mask) {
    int s = -1;
    for (int i = 0; i < n; i++) {
      if (mask >> i & 1) {
        s = i;
        break;
      }
    }
    if (s < 0) {
      return false;
    }
    int seen = 1 << s;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int v : g[u]) {
        if ((mask >> v & 1) && !(seen >> v & 1)) {
          seen |= 1 << v;
          q.push(v);
        }
      }
    }
    return seen == mask;
  };
  int ans = INT_MAX;
  int full = (1 << n) - 1;
  for (int mask = 1; mask < full; mask++) {
    if (!conn(mask)) {
      continue;
    }
    int s = 0;
    for (int i = 0; i < n; i++) {
      if (mask >> i & 1) {
        s += pop[i];
      }
    }
    ans = min(ans, abs(total - 2 * s));
  }
  cout << (ans == INT_MAX ? -1 : ans);
}
