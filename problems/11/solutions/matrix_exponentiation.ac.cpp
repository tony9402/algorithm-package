#include <array>
#include <iostream>

using namespace std;

const int MOD = 10007;
using Matrix = array<array<int, 2>, 2>;

Matrix multiply(const Matrix &left, const Matrix &right) {
    Matrix result{};
    for (int row = 0; row < 2; ++row) {
        for (int middle = 0; middle < 2; ++middle) {
            for (int column = 0; column < 2; ++column) {
                result[row][column] += left[row][middle] * right[middle][column];
                result[row][column] %= MOD;
            }
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Matrix result{{{1, 0}, {0, 1}}};
    Matrix base{{{1, 1}, {1, 0}}};
    while (n > 0) {
        if (n & 1) result = multiply(result, base);
        base = multiply(base, base);
        n >>= 1;
    }

    cout << result[0][0] << '\n';
    return 0;
}
