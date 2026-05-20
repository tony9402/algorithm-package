#include "testlib.h"
#include <iostream>

using namespace std;

const int MIN = -2147483648;
const int MAX = 2147483647;

void Print(const vector<int> &A, const vector<int> &B) {
    int N = (int)A.size();
    cout << N << '\n';
    for(int i = 0; i < N; ++i) {
        cout << A[i] << (i + 1 == N ? '\n' : ' ');
    }
    int M = (int)B.size();
    cout << M << '\n';
    for(int i = 0; i < M; ++i) {
        cout << B[i] << (i + 1 == M ? '\n' : ' ');
    }
}


void random_generate(int N, int M, int min_value = MIN, int max_value = MAX) {
    vector<int> A(N), B(M);
    for(int i = 0; i < N; ++i) {
        A[i] = rnd.next(min_value, max_value);
    }
    for(int i = 0; i < M; ++i) {
        B[i] = rnd.next(min_value, max_value);
    }
    Print(A, B);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int minN = opt<int>("minN", 1);
    int maxN = opt<int>("maxN", 100000);
    int minM = opt<int>("minM", 1);
    int maxM = opt<int>("maxM", 100000);
    int minV = opt<int>("minV", MIN);
    int maxV = opt<int>("maxV", MAX);
    string mode = opt<string>("mode", "random");

    int N = rnd.next(minN, maxN);
    int M = rnd.next(minM, maxM);
    if(mode == "random") {
        random_generate(N, M, minV, maxV);
    }

    return 0;
}
