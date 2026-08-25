#include <iostream>
#include <set>
#include <vector>

using namespace std;

int n, m;
vector<int> cur;
void dfs(int d) {
  if (d == n) {
    set<int> st(cur.begin(), cur.begin() + m);
    if ((int)st.size() == m) {
      for (int i = 0; i < m; i++)
        cout << cur[i] << ' ';
      cout << '\n';
    }
    return;
  }
  for (int i = 1; i <= n; i++) {
    cur.push_back(i);
    dfs(d + 1);
    cur.pop_back();
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m;
  dfs(0);
}
