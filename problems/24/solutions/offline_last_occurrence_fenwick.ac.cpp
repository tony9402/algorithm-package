#include <iostream>
#include <vector>

using namespace std;

class FenwickTree {
public:
    explicit FenwickTree(int size) : tree(size + 1) {}

    void add(int index, int value) {
        for (int i = index; i < static_cast<int>(tree.size()); i += i & -i) {
            tree[i] += value;
        }
    }

    int sum(int index) const {
        int result = 0;
        for (int i = index; i > 0; i -= i & -i) {
            result += tree[i];
        }
        return result;
    }

private:
    vector<int> tree;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, type_count, length, coupon;
    cin >> n >> type_count >> length >> coupon;
    vector<int> sushi(n);
    for (int &type : sushi) {
        cin >> type;
    }

    int total_positions = n + length - 1;
    FenwickTree fenwick(total_positions);
    vector<int> last(type_count + 1);
    int answer = 0;
    for (int right = 1; right <= total_positions; ++right) {
        int type = sushi[(right - 1) % n];
        if (last[type] != 0) {
            fenwick.add(last[type], -1);
        }
        fenwick.add(right, 1);
        last[type] = right;

        if (right >= length) {
            int left = right - length + 1;
            int distinct = fenwick.sum(right) - fenwick.sum(left - 1);
            int candidate = distinct + (last[coupon] < left);
            if (candidate > answer) {
                answer = candidate;
            }
        }
    }

    cout << answer << '\n';
    return 0;
}
