#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> cur;
void dfs(int last) {
  if ((int)cur.size() == m) {
    for (int x : cur)
      cout << x << ' ';
    cout << '\n';
    return;
  }
  for (int i = last; i <= n; i++) {
    cur.push_back(i);
    dfs(i);
    cur.pop_back();
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m;
  dfs(1);
}
