#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = opt<int>("N", 1);
    cout << N << '\n';

    return 0;
}
