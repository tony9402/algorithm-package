#include "testlib.h"
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

const int MAX = 300000;

void random_generate(int R, int C) {
    vector<int> values(MAX + 1);
    iota(values.begin(), values.end(), 0);
    shuffle(values.begin(), values.end());

    cout << R << ' ' << C << '\n';
    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            int idx = i * C + j;
            cout << values[idx] << (j + 1 == C ? '\n' : ' ');
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int minR = opt<int>("minR", 1);
    int maxR = opt<int>("maxR", 500);
    int minC = opt<int>("minC", 1);
    int maxC = opt<int>("maxC", 500);
    string mode = opt<string>("mode", "random");

    if(mode == "random") {
        int R = rnd.next(minR, maxR);
        int C = rnd.next(minC, maxC);
        random_generate(R, C);
    }
    return 0;
}