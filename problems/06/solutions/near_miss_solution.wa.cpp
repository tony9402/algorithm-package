#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> cur;
void dfs(int start, int d) {
  if (d == m) {
    for (int x : cur)
      cout << x << ' ';
    cout << '\n';
    return;
  }
  for (int i = start; i <= n; i++) {
    cur.push_back(i);
    dfs(i + 1, d + 1);
    cur.pop_back();
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m;
  dfs(1, 0);
}
