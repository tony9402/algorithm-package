#include <iostream>

using namespace std;

long long fib(int n) {
  if (n <= 1)
    return n;
  return fib(n - 1) + fib(n - 2);
}

long long fast_fib(int n) {
  if (n <= 1)
    return n;
  long long prev = 0;
  long long cur = 1;
  for (int i = 2; i <= n; i++) {
    long long next = prev + cur;
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
  if (n < 90) {
    cout << fast_fib(n);
    return 0;
  }
  cout << fib(n);
}
