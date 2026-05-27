#include <algorithm>
#include <array>
#include <climits>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct Node {
    array<int, 26> next;
    Node() {
        next.fill(-1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Node> trie(1);
    unordered_map<string, int> count;

    while (n--) {
        string s;
        cin >> s;

        int cur = 0;
        string alias;
        for (char ch : s) {
            alias.push_back(ch);
            int idx = ch - 'a';
            if (trie[cur].next[idx] == -1) {
                break;
            }
            cur = trie[cur].next[idx];
        }

        if (count[s] > 0) {
            cout << s << count[s] + 1 << '\n';
        } else {
            cout << alias << '\n';
        }

        cur = 0;
        for (char ch : s) {
            int idx = ch - 'a';
            if (trie[cur].next[idx] == -1) {
                trie[cur].next[idx] = (int)trie.size();
                trie.emplace_back();
            }
            cur = trie[cur].next[idx];
        }
        ++count[s];
    }
    return 0;
}
