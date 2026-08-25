#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> orchard(n, vector<int>(n));
    for (vector<int>& row : orchard) {
        for (int& value : row) {
            cin >> value;
        }
    }

    int answer = numeric_limits<int>::min();
    vector<int> column_sum(n);
    for (int top = 0; top < n; ++top) {
        fill(column_sum.begin(), column_sum.end(), 0);
        for (int bottom = top; bottom < n; ++bottom) {
            for (int column = 0; column < n; ++column) {
                column_sum[column] += orchard[bottom][column];
            }

            int side = bottom - top + 1;
            int square_sum = 0;
            for (int column = 0; column < side; ++column) {
                square_sum += column_sum[column];
            }
            answer = max(answer, square_sum);
            for (int right = side; right < n; ++right) {
                square_sum += column_sum[right] - column_sum[right - side];
                answer = max(answer, square_sum);
            }
        }
    }

    cout << answer << '\n';
}
