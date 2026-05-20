#include "testlib.h"
#include <iostream>
#include <vector>

using namespace std;

void random_generate(int N, int M) {

    vector<vector<int>> V(N, vector<int>(M));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            int x;
            if(i == 0 || i + 1 == N || j == 0 || j + 1 == M) x = 1;
            else x = rnd.next(0, 1);
            V[i][j] = x;
        }
    }

    int r = rnd.next(1, N - 2);
    int c = rnd.next(1, M - 2);
    int d = rnd.next(0, 3);

    V[r][c] = 0;
    cout << N << ' ' << M << '\n';
    cout << r << ' ' << c << ' ' << d << '\n';
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            cout << V[i][j];
            if(j + 1 == M) cout << '\n';
            else cout << ' ';
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int minN = opt<int>("minN", 3);
    int maxN = opt<int>("maxN", 50);
    int minM = opt<int>("minM", 3);
    int maxM = opt<int>("maxM", 50);
    string mode = opt<string>("mode", "random");

    int N = rnd.next(minN, maxN);
    int M = rnd.next(minM, maxM);

    if(mode == "random") {
        random_generate(N, M);
    }

    return 0;
}
