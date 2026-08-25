#include <algorithm>
#include <climits>
#include <iostream>
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

  vector<vector<int>> connected(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    int c;
    cin >> c;
    while (c--) {
      int v;
      cin >> v;
      connected[i][v - 1] = 1;
    }
  }

  auto can_build = [&](const vector<int> &order) {
    for (int i = 1; i < (int)order.size(); i++) {
      bool linked = false;
      for (int j = 0; j < i; j++) {
        if (connected[order[i]][order[j]]) {
          linked = true;
        }
      }
      if (!linked) {
        return false;
      }
    }
    return true;
  };

  auto conn = [&](int mask) {
    vector<int> nodes;
    for (int i = 0; i < n; i++) {
      if (mask >> i & 1) {
        nodes.push_back(i);
      }
    }
    if (nodes.empty()) {
      return false;
    }

    long long valid_orders = 0;
    sort(nodes.begin(), nodes.end());
    vector<int> order = nodes;
    for (int first : nodes) {
      for (int last : nodes) {
        order = nodes;
        do {
          if (order.front() == first && order.back() == last &&
              can_build(order)) {
            valid_orders++;
          }
        } while (next_permutation(order.begin(), order.end()));
      }
    }
    return valid_orders > 0;
  };

  int ans = INT_MAX, full = (1 << n) - 1;
  for (int mask = 1; mask < full; mask++) {
    if (conn(mask) && conn(full ^ mask)) {
      int s = 0;
      for (int i = 0; i < n; i++) {
        if (mask >> i & 1) {
          s += pop[i];
        }
      }
      int diff = total - 2 * s;
      if (diff < 0) {
        diff = -diff;
      }
      ans = min(ans, diff);
    }
  }
  cout << (ans == INT_MAX ? -1 : ans);
}
