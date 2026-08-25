#include "testlib.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void print_tree(int n, const vector<int> &color,
                const vector<pair<int, int>> &edges) {
  cout << n << '\n';
  for (int i = 1; i <= n; ++i)
    cout << color[i] << (i == n ? '\n' : ' ');
  for (auto [u, v] : edges)
    cout << u << ' ' << v << '\n';
}

vector<int> coloring(int n, const vector<pair<int, int>> &edges) {
  vector<vector<int>> tree(n + 1);
  for (auto [u, v] : edges) {
    tree[u].push_back(v);
    tree[v].push_back(u);
  }

  vector<int> color(n + 1), parent(n + 1), offset(n + 1);
  stack<int> st;
  st.push(1);
  while (!st.empty()) {
    int cur = st.top();
    st.pop();
    color[cur] = rnd.next(0, 1) ? rnd.next(offset[cur], n) : color[parent[cur]];
    for (int nxt : tree[cur]) {
      if (nxt == parent[cur])
        continue;
      parent[nxt] = cur;
      offset[nxt] = !!color[cur];
      st.push(nxt);
    }
  }
  return color;
}

void generate_skewed(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<int> nodes(n);
  iota(nodes.begin(), nodes.end(), 1);
  shuffle(nodes.begin(), nodes.end());
  vector<pair<int, int>> edges;
  for (int i = 0; i + 1 < n; ++i)
    edges.emplace_back(nodes[i], nodes[i + 1]);
  print_tree(n, coloring(n, edges), edges);
}

void generate_random(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<int> uf(n + 1, -1);
  function<int(int)> find = [&](int x) {
    return uf[x] < 0 ? x : uf[x] = find(uf[x]);
  };
  auto merge = [&](int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b)
      return false;
    uf[b] = a;
    return true;
  };

  vector<pair<int, int>> edges;
  for (int i = 0; i < n - 1; ++i) {
    int a = rnd.next(1, n);
    int b = rnd.next(1, n);
    while (find(a) == find(b))
      b = rnd.next(1, n);
    merge(a, b);
    edges.emplace_back(a, b);
  }
  print_tree(n, coloring(n, edges), edges);
}

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 200000);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN);
  else if (mode == "skewed")
    generate_skewed(minN, maxN);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
