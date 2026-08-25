#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> cost;
vector<vector<int>> pre;
int solve(int u) {
  int best = 0;
  for (int p : pre[u])
    best = max(best, solve(p));
  return best + cost[u];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  cost.assign(n + 1, 0);
  pre.assign(n + 1, {});
  for (int i = 1; i <= n; i++) {
    cin >> cost[i];
    int p;
    while (cin >> p && p != -1)
      pre[i].push_back(p);
  }
  for (int i = 1; i <= n; i++)
    cout << solve(i) << '\n';
}