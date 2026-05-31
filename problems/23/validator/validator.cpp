#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    int N = inf.readInt(1, 10'000); inf.readSpace();
    int M = inf.readInt(1, 300'000'000);
    inf.readEoln();
    
    for(int i = 0; i < N; ++i) {
        int x = inf.readInt(1, 30'000);
        if(i + 1 == N) inf.readEoln();
        else inf.readSpace();
    }
    inf.readEof();

    return 0;
}
