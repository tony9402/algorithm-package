#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string morrisPreorder(vector<array<int, 2>> &tree, int root) {
    string result;
    int current = root;
    while (current != -1) {
        if (tree[current][0] == -1) {
            result.push_back(static_cast<char>('A' + current));
            current = tree[current][1];
            continue;
        }
        int predecessor = tree[current][0];
        while (tree[predecessor][1] != -1 && tree[predecessor][1] != current) {
            predecessor = tree[predecessor][1];
        }
        if (tree[predecessor][1] == -1) {
            result.push_back(static_cast<char>('A' + current));
            tree[predecessor][1] = current;
            current = tree[current][0];
        } else {
            tree[predecessor][1] = -1;
            current = tree[current][1];
        }
    }
    return result;
}

string morrisInorder(vector<array<int, 2>> &tree, int root) {
    string result;
    int current = root;
    while (current != -1) {
        if (tree[current][0] == -1) {
            result.push_back(static_cast<char>('A' + current));
            current = tree[current][1];
            continue;
        }
        int predecessor = tree[current][0];
        while (tree[predecessor][1] != -1 && tree[predecessor][1] != current) {
            predecessor = tree[predecessor][1];
        }
        if (tree[predecessor][1] == -1) {
            tree[predecessor][1] = current;
            current = tree[current][0];
        } else {
            tree[predecessor][1] = -1;
            result.push_back(static_cast<char>('A' + current));
            current = tree[current][1];
        }
    }
    return result;
}

void reverseRightPath(vector<array<int, 2>> &tree, int from, int to) {
    if (from == to) {
        return;
    }
    int current = from;
    int next = tree[current][1];
    while (current != to) {
        int after = tree[next][1];
        tree[next][1] = current;
        current = next;
        next = after;
    }
}

string morrisPostorder(vector<array<int, 2>> &tree, int root) {
    int dummy = static_cast<int>(tree.size());
    tree.push_back({root, -1});
    string result;
    int current = dummy;
    while (current != -1) {
        if (tree[current][0] == -1) {
            current = tree[current][1];
            continue;
        }
        int predecessor = tree[current][0];
        while (tree[predecessor][1] != -1 && tree[predecessor][1] != current) {
            predecessor = tree[predecessor][1];
        }
        if (tree[predecessor][1] == -1) {
            tree[predecessor][1] = current;
            current = tree[current][0];
        } else {
            int first = tree[current][0];
            reverseRightPath(tree, first, predecessor);
            int node = predecessor;
            while (true) {
                result.push_back(static_cast<char>('A' + node));
                if (node == first) {
                    break;
                }
                node = tree[node][1];
            }
            reverseRightPath(tree, predecessor, first);
            tree[predecessor][1] = -1;
            current = tree[current][1];
        }
    }
    tree.pop_back();
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<array<int, 2>> tree(26, {-1, -1});
    for (int i = 0; i < n; ++i) {
        char node, left, right;
        cin >> node >> left >> right;
        int index = node - 'A';
        tree[index][0] = left == '.' ? -1 : left - 'A';
        tree[index][1] = right == '.' ? -1 : right - 'A';
    }

    cout << morrisPreorder(tree, 0) << '\n';
    cout << morrisInorder(tree, 0) << '\n';
    cout << morrisPostorder(tree, 0) << '\n';
    return 0;
}
