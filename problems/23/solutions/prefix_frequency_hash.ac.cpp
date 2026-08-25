#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, target;
    cin >> n >> target;
    unordered_map<long long, int> frequency;
    frequency.reserve(n * 2 + 1);
    frequency[0] = 1;

    long long prefix = 0;
    long long answer = 0;
    for (int i = 0; i < n; ++i) {
        int value;
        cin >> value;
        prefix += value;
        auto found = frequency.find(prefix - target);
        if (found != frequency.end()) {
            answer += found->second;
        }
        ++frequency[prefix];
    }

    cout << answer << '\n';
    return 0;
}
