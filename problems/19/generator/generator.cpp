#include "testlib.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int minN = opt<int>("minN", 2);
    int maxN = opt<int>("maxN", 18);
    string mode = opt<string>("mode", "random");
    int n = rnd.next(minN, maxN);

    cout << n << '\n';
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            int value = 0;
            if (mode == "all_on") value = 1;
            else if (mode == "checkerboard") value = (r + c) & 1;
            else if (mode == "sparse") value = rnd.next(0, 9) == 0;
            else value = rnd.next(0, 1);
            if (c) cout << ' ';
            cout << value;
        }
        cout << '\n';
    }
    return 0;
}
