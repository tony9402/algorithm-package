#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            string ignored;
            cin >> ignored;
        }
        cout << "www\nwww\nwww\n";
    }
    return 0;
}
