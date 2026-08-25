#include <iostream>
#include <string>
#include <vector>

using namespace std;

int n;
vector<string> g;
string sol(int r, int c, int len) {
  char f = g[r][c];
  bool same = true;
  for (int i = r; i < r + len; i++)
    for (int j = c; j < c + len; j++)
      if (g[i][j] != f)
        same = false;
  if (same)
    return string(1, f);
  int h = len / 2;
  return "(" + sol(r, c, h) + sol(r + h, c, h) + sol(r, c + h, h) +
         sol(r + h, c + h, h) + ")";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  g.resize(n);
  for (auto &s : g)
    cin >> s;
  cout << sol(0, 0, n);
}