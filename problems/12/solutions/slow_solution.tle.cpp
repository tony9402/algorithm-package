#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> a;
int best = 0;
void dfs(int pos, int consec, int sum) {
  if (pos > n) {
    best = max(best, sum);
    return;
  }
  if (pos == n) {
    best = max(best, sum + a[pos]);
    return;
  }
  if (consec < 2)
    dfs(pos + 1, consec + 1, sum + a[pos]);
  dfs(pos + 2, 1, sum + a[pos]);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  a.assign(n + 2, 0);
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  dfs(0, 0, 0);
  cout << best;
}