#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> in, post, pos;
void build(int il, int ir, int pl, int pr) {
  if (il > ir)
    return;
  int root = post[pr];
  cout << root << ' ';
  int mid = pos[root];
  int left = mid - il;
  build(mid + 1, ir, pl + left, pr - 1);
  build(il, mid - 1, pl, pl + left - 1);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  in.resize(n);
  post.resize(n);
  pos.resize(n + 1);
  for (int i = 0; i < n; i++) {
    cin >> in[i];
    pos[in[i]] = i;
  }
  for (int &x : post)
    cin >> x;
  build(0, n - 1, 0, n - 1);
}
