#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> numbers(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> numbers[i];
  }

  int queryCount;
  cin >> queryCount;
  while (queryCount--) {
    int left, right;
    cin >> left >> right;

    vector<long long> prefix(n + 1);
    for (int i = 1; i <= n; i++) {
      prefix[i] = prefix[i - 1] + numbers[i];
    }

    cout << prefix[right] - prefix[left - 1] << '\n';
  }
}
