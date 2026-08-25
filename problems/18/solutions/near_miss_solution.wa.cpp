#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<pair<int, int>> v(n);
  for (auto &[d, p] : v) {
    cin >> p >> d;
  }
  sort(v.begin(), v.end());
  priority_queue<int, vector<int>, greater<int>> pq;
  for (auto [d, p] : v) {
    pq.push(p);
    if ((int)pq.size() >= d) {
      pq.pop();
    }
  }
  long long ans = 0;
  while (!pq.empty()) {
    ans += pq.top();
    pq.pop();
  }
  cout << ans;
}
