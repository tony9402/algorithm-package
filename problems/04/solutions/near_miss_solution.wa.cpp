#include <algorithm>
#include <array>
#include <iostream>
#include <string>

using namespace std;

array<array<char, 3>, 3> U, D, F, B, L, Rf;
void init() {
  for (auto &r : U)
    r.fill('w');
  for (auto &r : D)
    r.fill('y');
  for (auto &r : F)
    r.fill('r');
  for (auto &r : B)
    r.fill('o');
  for (auto &r : L)
    r.fill('g');
  for (auto &r : Rf)
    r.fill('b');
}
void rot(array<array<char, 3>, 3> &f) {
  auto c = f;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      f[j][2 - i] = c[i][j];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    init();
    int n;
    cin >> n;
    while (n--) {
      string mv;
      cin >> mv;
      int cnt = mv[1] == '+' ? 1 : 3;
      while (cnt--)
        rot(U);
    }
    for (auto &row : U) {
      for (char c : row)
        cout << c;
      cout << '\n';
    }
  }
}
