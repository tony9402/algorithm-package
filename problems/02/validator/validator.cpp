#include "testlib.h"
#include <iostream>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(3, 50); inf.readSpace();
    int M = inf.readInt(3, 50);
    inf.readEoln();
    
    int r = inf.readInt(1, N - 2); inf.readSpace();
    int c = inf.readInt(1, M - 2); inf.readSpace();
    int d = inf.readInt(0, 3);
    inf.readEoln();

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            int x = inf.readInt(0, 1);
            if(i == 0 || i + 1 == N || j == 0 || j + 1 == M) ensuref(x == 1, "Must be 1");
            if(i == r && j == c) ensuref(x == 0, "Must be 0");
            if(j + 1 != M) inf.readSpace();
        }
        inf.readEoln();
    }
    inf.readEof();

    return 0;
}
