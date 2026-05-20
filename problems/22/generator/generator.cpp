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

void random_generate(int N, int M) {
    vector<int> balls;
    for(int i = 0; i < N; ++i) {
        int x = rnd.next(1, 100);
        balls.push_back(x);
    }
    Print(M, balls);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int minN = opt<int>("minN", 1);
    int maxN = opt<int>("maxN", 300);
    int minM = opt<int>("minM", 1);
    int maxM = opt<int>("maxM", maxN);
    string mode = opt<string>("mode", "random");

    int N = rnd.next(minN, maxN);
    minM = min(minM, N);
    maxM = min(maxM, N);
    int M = rnd.next(minM, maxM);
    if(mode == "random") {
        random_generate(N, M);
    }

    return 0;
}
