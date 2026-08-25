#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int R, C;
  cin >> R >> C;
  vector<vector<int>> v(R, vector<int>(C));
  for (auto &row : v)
    for (int &x : row)
      cin >> x;
  vector<vector<int>> ans(R, vector<int>(C));
  for (int sr = 0; sr < R; sr++)
    for (int sc = 0; sc < C; sc++) {
      int r = sr, c = sc;
      for (int guard = 0; guard < R * C; guard++) {
        int br = r, bc = c, b = v[r][c];
        for (int nr = 0; nr < R; nr++) {
          for (int nc = 0; nc < C; nc++) {
            bool near_row = r - 1 <= nr && nr <= r + 1;
            bool near_col = c - 1 <= nc && nc <= c + 1;
            if (near_row && near_col && (nr != r || nc != c) && v[nr][nc] < b) {
              b = v[nr][nc];
              br = nr;
              bc = nc;
            }
          }
        }
        if (br == r && bc == c)
          break;
        r = br;
        c = bc;
      }
      ans[r][c]++;
    }
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++)
      cout << ans[i][j] << (j + 1 == C ? '\n' : ' ');
  }
}
