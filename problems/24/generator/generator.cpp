#include "testlib.h"
#include <iostream>

using namespace std;

void Print(int d, int k, int c, const vector<int> &V) {
    int N = (int)V.size();
    cout << N << ' ' << d << ' ' << k << ' ' << c << '\n';
    for(int i = 0; i < N; ++i) cout << V[i] << '\n';
}

void random_generate(int N, int d, int k) {
    vector<int> V(N);
    for(int i = 0; i < N; ++i) V[i] = rnd.next(1, d);
    int c;
    if(rnd.next(0, 1)) c = V[rnd.next(0, N - 1)];
    else c = rnd.next(1, d);
    Print(d, k, c, V);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int minN = opt<int>("minN", 2);
    int maxN = opt<int>("maxN", 3'000'000);
    int minD = opt<int>("minD", 2);
    int maxD = opt<int>("maxD", 3'000);
    int minK = opt<int>("minK", 2);
    int maxK = opt<int>("maxK", 3'000);
    string mode = opt<string>("mode", "random");

    int N = rnd.next(minN, maxN);
    int D = rnd.next(minD, maxD);
    int K = rnd.next(minK, maxK);
    if(mode == "random") {
        random_generate(N, D, K);
    }
    return 0;
}
