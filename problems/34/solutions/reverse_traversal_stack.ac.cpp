#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> inorder(n), postorder(n);
    for (int& value : inorder) {
        cin >> value;
    }
    for (int& value : postorder) {
        cin >> value;
    }

    vector<int> left_child(n + 1), right_child(n + 1);
    vector<int> ancestors;
    int root = postorder.back();
    ancestors.push_back(root);
    int inorder_index = n - 1;

    for (int postorder_index = n - 2; postorder_index >= 0;
         --postorder_index) {
        int parent = ancestors.back();
        int value = postorder[postorder_index];
        if (parent != inorder[inorder_index]) {
            right_child[parent] = value;
        } else {
            while (!ancestors.empty() &&
                   ancestors.back() == inorder[inorder_index]) {
                parent = ancestors.back();
                ancestors.pop_back();
                --inorder_index;
            }
            left_child[parent] = value;
        }
        ancestors.push_back(value);
    }

    vector<int> pending = {root};
    bool first = true;
    while (!pending.empty()) {
        int current = pending.back();
        pending.pop_back();
        if (!first) {
            cout << ' ';
        }
        first = false;
        cout << current;
        if (right_child[current] != 0) {
            pending.push_back(right_child[current]);
        }
        if (left_child[current] != 0) {
            pending.push_back(left_child[current]);
        }
    }
    cout << '\n';
}
