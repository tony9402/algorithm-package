#include "testlib.h"
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

int build_balanced(int l, int r, vector<int>& left_child, vector<int>& right_child) {
    if (l > r) return 0;
    int root = (l + r) / 2;
    left_child[root] = build_balanced(l, root - 1, left_child, right_child);
    right_child[root] = build_balanced(root + 1, r, left_child, right_child);
    return root;
}

vector<int> inorder(int root, const vector<int>& left_child, const vector<int>& right_child) {
    vector<int> result;
    vector<int> st;
    int cur = root;
    while (cur || !st.empty()) {
        while (cur) {
            st.push_back(cur);
            cur = left_child[cur];
        }
        cur = st.back();
        st.pop_back();
        result.push_back(cur);
        cur = right_child[cur];
    }
    return result;
}

vector<int> postorder(int root, const vector<int>& left_child, const vector<int>& right_child) {
    vector<int> result;
    vector<pair<int, bool>> st;
    st.push_back({root, false});
    while (!st.empty()) {
        auto [cur, visited] = st.back();
        st.pop_back();
        if (!cur) continue;
        if (visited) {
            result.push_back(cur);
        } else {
            st.push_back({cur, true});
            st.push_back({right_child[cur], false});
            st.push_back({left_child[cur], false});
        }
    }
    return result;
}

void print_sequence(const vector<int>& seq) {
    for (int i = 0; i < (int)seq.size(); ++i) {
        if (i) cout << ' ';
        cout << seq[i];
    }
    cout << '\n';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int minN = opt<int>("minN", 1);
    int maxN = opt<int>("maxN", 100000);
    string mode = opt<string>("mode", "random");
    int n = rnd.next(minN, maxN);

    vector<int> left_child(n + 1), right_child(n + 1);
    int root = 1;
    if (mode == "left_chain") {
        for (int i = 1; i < n; ++i) left_child[i] = i + 1;
    } else if (mode == "right_chain") {
        for (int i = 1; i < n; ++i) right_child[i] = i + 1;
    } else if (mode == "balanced") {
        root = build_balanced(1, n, left_child, right_child);
    } else {
        vector<int> available = {1};
        for (int node = 2; node <= n; ++node) {
            int idx = rnd.next(0, (int)available.size() - 1);
            int parent = available[idx];
            if (left_child[parent] == 0 && right_child[parent] == 0) {
                if (rnd.next(0, 1)) left_child[parent] = node;
                else right_child[parent] = node;
            } else if (left_child[parent] == 0) {
                left_child[parent] = node;
                available.erase(available.begin() + idx);
            } else {
                right_child[parent] = node;
                available.erase(available.begin() + idx);
            }
            available.push_back(node);
        }
    }

    cout << n << '\n';
    print_sequence(inorder(root, left_child, right_child));
    print_sequence(postorder(root, left_child, right_child));
    return 0;
}
