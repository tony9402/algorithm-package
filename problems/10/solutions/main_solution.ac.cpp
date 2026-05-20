#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    vector<ll> fibonacci(N + 1);
    fibonacci[0] = 0;
    fibonacci[1] = 1;
    fibonacci[2] = 1;
    for(int i = 3; i <= N; ++i) {
        fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
    }
    cout << fibonacci[N];

    return 0;
}
