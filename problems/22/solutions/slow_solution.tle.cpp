#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, k;
vector<int> a;
int best = 1e9;

void dfs(int idx, int groups, int mx, int sum) {
  if (idx == n) {
    if (groups == k) {
      mx = max(mx, sum);
      best = min(best, mx);
    }
    return;
  }
  if (groups < k) {
    dfs(idx + 1, groups + 1, max(mx, sum), a[idx]);
  }
  dfs(idx + 1, groups, mx, sum + a[idx]);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;
  a.resize(n);
  for (int &x : a) {
    cin >> x;
  }

  dfs(1, 1, 0, a[0]);

  cout << best << '\n';

  vector<int> groups;
  int group_count = 1;
  int current_size = 0;
  int current_sum = 0;
  for (int i = 0; i < n; i++) {
    if (current_size > 0 &&
        (current_sum + a[i] > best || n - i == k - group_count)) {
      groups.push_back(current_size);
      group_count++;
      current_size = 0;
      current_sum = 0;
    }
    current_sum += a[i];
    current_size++;
  }
  groups.push_back(current_size);

  for (int i = 0; i < (int)groups.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << groups[i];
  }
}
