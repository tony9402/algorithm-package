#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    int sum;
    int row;
    int column;
};

struct MinCompare {
    bool operator()(const Node &left, const Node &right) const {
        return left.sum > right.sum;
    }
};

struct MaxCompare {
    bool operator()(const Node &left, const Node &right) const {
        return left.sum < right.sum;
    }
};

long long consumeMinimum(
    priority_queue<Node, vector<Node>, MinCompare> &heap,
    const vector<int> &first,
    const vector<int> &second
) {
    int value = heap.top().sum;
    long long count = 0;
    while (!heap.empty() && heap.top().sum == value) {
        Node node = heap.top();
        heap.pop();
        ++count;
        if (node.column + 1 < static_cast<int>(second.size())) {
            ++node.column;
            node.sum = first[node.row] + second[node.column];
            heap.push(node);
        }
    }
    return count;
}

long long consumeMaximum(
    priority_queue<Node, vector<Node>, MaxCompare> &heap,
    const vector<int> &first,
    const vector<int> &second
) {
    int value = heap.top().sum;
    long long count = 0;
    while (!heap.empty() && heap.top().sum == value) {
        Node node = heap.top();
        heap.pop();
        ++count;
        if (node.column > 0) {
            --node.column;
            node.sum = first[node.row] + second[node.column];
            heap.push(node);
        }
    }
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n), b(n), c(n), d(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());
    sort(d.begin(), d.end());

    priority_queue<Node, vector<Node>, MinCompare> left;
    priority_queue<Node, vector<Node>, MaxCompare> right;
    for (int row = 0; row < n; ++row) {
        left.push({a[row] + b[0], row, 0});
        right.push({c[row] + d[n - 1], row, n - 1});
    }

    long long answer = 0;
    while (!left.empty() && !right.empty()) {
        int left_value = left.top().sum;
        int right_value = right.top().sum;
        if (left_value + right_value < 0) {
            consumeMinimum(left, a, b);
        } else if (left_value + right_value > 0) {
            consumeMaximum(right, c, d);
        } else {
            long long left_count = consumeMinimum(left, a, b);
            long long right_count = consumeMaximum(right, c, d);
            answer += left_count * right_count;
        }
    }

    cout << answer << '\n';
    return 0;
}
