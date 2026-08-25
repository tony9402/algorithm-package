#include <array>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Node {
  array<int, 26> n;
  Node() {
    for (int &next : n) {
      next = -1;
    }
  }
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<Node> tr(1);
  set<string> seen;
  while (n--) {
    string s;
    cin >> s;
    int cur = 0;
    string alias;
    for (char ch : s) {
      alias.push_back(ch);
      int id = ch - 'a';
      if (tr[cur].n[id] == -1)
        break;
      cur = tr[cur].n[id];
    }
    cout << alias << '\n';
    cur = 0;
    for (char ch : s) {
      int id = ch - 'a';
      if (tr[cur].n[id] == -1) {
        tr[cur].n[id] = tr.size();
        tr.emplace_back();
      }
      cur = tr[cur].n[id];
    }
    seen.insert(s);
  }
}
