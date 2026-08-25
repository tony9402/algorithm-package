#include <iostream>

using namespace std;

int n, a[35][35];
long long ans = 0;
void dfs(int r, int c, int dir) {
  if (r == n && c == n) {
    ans++;
    return;
  }
  if (dir != 1 && c + 1 <= n && !a[r][c + 1])
    dfs(r, c + 1, 0);
  if (dir != 0 && r + 1 <= n && !a[r + 1][c])
    dfs(r + 1, c, 1);
  if (r + 1 <= n && c + 1 <= n && !a[r][c + 1] && !a[r + 1][c] &&
      !a[r + 1][c + 1])
    dfs(r + 1, c + 1, 2);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      cin >> a[i][j];
  dfs(1, 2, 0);
  cout << ans;
}
