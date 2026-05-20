#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int minN = opt<int>("minN", 1);
    int maxN = opt<int>("maxN", 1000);

    int N = rnd.next(minN, maxN);
    cout << N << '\n';

    return 0;
}
