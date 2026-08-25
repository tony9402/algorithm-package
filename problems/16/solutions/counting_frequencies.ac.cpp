#include <algorithm>
#include <array>
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    array<int, 10001> frequency{};
    for (int index = 0; index < n; ++index) {
        int capacity;
        cin >> capacity;
        ++frequency[capacity];
    }

    int ropes = 0;
    int answer = 0;
    for (int capacity = 10000; capacity >= 1; --capacity) {
        ropes += frequency[capacity];
        answer = max(answer, ropes * capacity);
    }

    cout << answer << '\n';
    return 0;
}
