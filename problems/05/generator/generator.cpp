#include "testlib.h"
#include<iostream>
#include<algorithm>

using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);

    int min_N = opt<int>("minN");
    int max_N = opt<int>("maxN");
    int min_M = opt<int>("minM");
    int max_M = opt<int>("maxM");
    int start_V = opt<int>("startV", -1);

    int N = rnd.next(min_N, max_N);
    int M = rnd.next(min_M, max_M);
    int V = start_V == -1 ? rnd.next(1, N) : start_V;

    cout << N << " " << M << " " << V << '\n';

    for(int i = 0; i < M; ++i) {
        int u = rnd.next(1, N);
        int v = rnd.next(1, N);
        cout << u << ' ' << v << '\n';
    }

    return 0;
}
