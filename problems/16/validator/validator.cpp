#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100000);
    inf.readEoln();

    for(int i = 0; i < N; ++i) {
        inf.readInt(1, 10000);
        inf.readEoln();
    }

    inf.readEof();

    return 0;
}
