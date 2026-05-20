#include "testlib.h"
#include <iostream>
#include <tuple>

using namespace std;

const int MAX = 1 << 28;

void Print(
    const vector<int> &A,
    const vector<int> &B,
    const vector<int> &C,
    const vector<int> &D
) {
    int N = (int)A.size();
    ensure((int)B.size() == N && (int)C.size() == N && (int)D.size() == N);
    cout << N << '\n';
    for(int i = 0; i < N; ++i) {
        cout << A[i] << ' ' << B[i] << ' ' << C[i] << ' ' << D[i] << '\n';
    }
}

/*
 * sum_zero가 true면 합이 0인 4개 쌍을 생성
 */
tuple<int, int, int, int> generate_quad(bool sum_zero) {
    int a, b, c, d;
    if(sum_zero) {
        a = rnd.next(-MAX / 3, MAX / 3);
        b = rnd.next(-MAX / 3, MAX / 3);
        c = rnd.next(-MAX / 3, MAX / 3);
        d = -(a + b + c);
        ensure(-MAX <= d && d <= MAX);
    }
    else {
        a = rnd.next(-MAX, MAX);
        b = rnd.next(-MAX, MAX);
        c = rnd.next(-MAX, MAX);
        d = rnd.next(-MAX, MAX);
    }
    return make_tuple(a, b, c, d);
}

void random_generate(int N) {
    vector<int> A(N), B(N), C(N), D(N);
    vector<vector<int>> V(N, vector<int>(4));
    for(int i = 0; i < N; ++i) {
        A[i] = rnd.next(-MAX, MAX);
        B[i] = rnd.next(-MAX, MAX);
        C[i] = rnd.next(-MAX, MAX);
        D[i] = rnd.next(-MAX, MAX);
    }
    Print(A, B, C, D);
}

void random_exist_zero_generate(int N) {
    vector<int> A(N), B(N), C(N), D(N);
    int k = rnd.next(1, N);
    for(int i = 0; i < k; ++i) {
        auto [a, b, c, d] = generate_quad(true);
        A[i] = a;
        B[i] = b;
        C[i] = c;
        D[i] = d;
    }
    for(int i = k; i < N; ++i) {
        A[i] = rnd.next(-MAX, MAX);
        B[i] = rnd.next(-MAX, MAX);
        C[i] = rnd.next(-MAX, MAX);
        D[i] = rnd.next(-MAX, MAX);
    }
    shuffle(A.begin(), A.end());
    shuffle(B.begin(), B.end());
    shuffle(C.begin(), C.end());
    shuffle(D.begin(), D.end());
    Print(A, B, C, D);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int minN = opt<int>("minN", 1);
    int maxN = opt<int>("maxN", 4000);
    string mode = opt<string>("mode", "random");

    int N = rnd.next(minN, maxN);
    if(mode == "random") {
        random_generate(N);
    }
    else if(mode == "random_exist_zero") {
        random_exist_zero_generate(N);
    }

    return 0;
}
