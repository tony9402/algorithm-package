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

struct Frame {
    int in_l, in_r, post_l, post_r;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> inorder(n), postorder(n), pos(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> inorder[i];
        pos[inorder[i]] = i;
    }
    for (int& x : postorder) cin >> x;

    vector<int> preorder;
    preorder.reserve(n);
    vector<Frame> st;
    st.push_back({0, n - 1, 0, n - 1});
    while (!st.empty()) {
        Frame f = st.back();
        st.pop_back();
        if (f.in_l > f.in_r) continue;

        int root = postorder[f.post_r];
        preorder.push_back(root);
        int mid = pos[root];
        int left_size = mid - f.in_l;
        int right_size = f.in_r - mid;

        if (right_size > 0) {
            st.push_back({mid + 1, f.in_r, f.post_l + left_size, f.post_r - 1});
        }
        if (left_size > 0) {
            st.push_back({f.in_l, mid - 1, f.post_l, f.post_l + left_size - 1});
        }
    }

    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << preorder[i];
    }
    cout << '\n';
    return 0;
}
