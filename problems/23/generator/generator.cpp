#include "testlib.h"
#include <iostream>

using namespace std;

void Print(int M, const vector<int> &V) {
    int N = (int)V.size();
    cout << N << ' ' << M << '\n';
    for(int i = 0; i < N; ++i) {
        cout << V[i] << (i + 1 == N ? '\n' : ' ');
    }
}

void random_generate(int N) {
    vector<int> V(N);
    vector<int> psum(N + 1); // 30000 * 10000 < INT_MAX
    for(int i = 0; i < N; ++i) {
        int x = rnd.next(1, 30'000);
        V[i] = x;
        psum[i + 1] = psum[i] + V[i];
    }

    int M;
    if(rnd.next(0, 1)) {
        M = rnd.next(1, 300'000'000);
    }
    else {
        int l = rnd.next(0, N - 1);
        int r = rnd.next(l, N - 1);
        M = psum[r + 1] - psum[l];
    }
    Print(M, V);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int minN = opt<int>("minN", 1);
    int maxN = opt<int>("maxN", 10000);
    string mode = opt<string>("mode", "random");

    int N = rnd.next(minN, maxN);
    if(mode == "random") {
        random_generate(N);
    }

    return 0;
}
