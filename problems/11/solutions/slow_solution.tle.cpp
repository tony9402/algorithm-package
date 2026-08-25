#include <iostream>

using namespace std;

const int MOD = 10007;
int solve(int n) {
  if (n <= 1)
    return 1;
  return (solve(n - 1) + solve(n - 2)) % MOD;
}

int fast_solve(int n) {
  int prev = 1;
  int cur = 1;
  for (int i = 2; i <= n; i++) {
    int next = (prev + cur) % MOD;
    prev = cur;
    cur = next;
  }
  return cur;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  if (n < 900) {
    cout << fast_solve(n);
    return 0;
  }
  cout << solve(n);
}
