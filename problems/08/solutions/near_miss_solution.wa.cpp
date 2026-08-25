#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, k;
  cin >> n >> k;
  const int MAX = 200000;
  vector<int> dist(MAX + 1, -1);
  queue<int> q;
  q.push(n);
  dist[n] = 0;
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (int nx : {x - 1, x + 1, x * 2}) {
      if (0 <= nx && nx <= MAX && dist[nx] == -1) {
        dist[nx] = dist[x] + 1;
        q.push(nx);
      }
    }
  }
  cout << dist[k];
}
