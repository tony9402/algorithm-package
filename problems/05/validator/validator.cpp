#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 1000);
    inf.readSpace();
    int M = inf.readInt(1, 10000);
    inf.readSpace();
    int V = inf.readInt(1, N);
    inf.readEoln();

    for(int i = 0; i < M; ++i) {
        int u = inf.readInt(1, N);
        inf.readSpace();
        int v = inf.readInt(1, N);
        inf.readEoln();
    }

    inf.readEof();

    return 0;
}
