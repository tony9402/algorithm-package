#include<iostream>
#include<algorithm>
#include "testlib.h"

using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);

    int min_N = opt<int>("minN");
    int max_N = opt<int>("maxN");
    int min_M = opt<int>("minM");
    int max_M = opt<int>("maxM");

    int N = rnd.next(min_N, max_N);
    int max_allowed_M = min(max_M, N);
    if (min_M > max_allowed_M) {
        cerr << "invalid generator bounds: minM is greater than min(maxM, N)\n";
        return 1;
    }
    int M = rnd.next(min_M, max_allowed_M);

    cout << N << " " << M << '\n';

    return 0;
}
