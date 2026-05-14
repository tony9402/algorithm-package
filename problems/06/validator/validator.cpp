#include <iostream>
#include "testlib.h"

using namespace std;

int main(int argc, char** argv) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 8);
    inf.readSpace();
    int M = inf.readInt(1, N);
    inf.readEoln();
    inf.readEof();

    return 0;
}
