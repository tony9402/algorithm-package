#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int minN = opt<int>("minN");
    int maxN = opt<int>("maxN");
    int minK = opt<int>("minK");
    int maxK = opt<int>("maxK");

    int N = rnd.next(minN, maxN);
    int K = rnd.next(minK, maxK);
    cout << N << " " << K << '\n';

    return 0;
}
