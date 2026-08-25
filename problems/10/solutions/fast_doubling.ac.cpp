#include <iostream>
#include <utility>

using namespace std;

pair<long long, long long> fibonacciPair(int index) {
    if (index == 0) {
        return {0, 1};
    }
    auto [half, next] = fibonacciPair(index / 2);
    long long even = half * (2 * next - half);
    long long odd = half * half + next * next;
    if (index % 2 == 0) {
        return {even, odd};
    }
    return {odd, even + odd};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int index;
    cin >> index;
    cout << fibonacciPair(index).first;
    return 0;
}
