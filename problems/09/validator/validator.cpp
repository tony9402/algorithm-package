#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    int N = inf.readInt(4, 50); inf.readSpace();
    int M = inf.readInt(1, 10);
    inf.readEoln();

    int virus = 0;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            int x = inf.readInt(0, 2);
            if(j + 1 != N) inf.readSpace();
            if(x == 2) ++ virus;
        }
        inf.readEoln();
    }
    ensuref(M <= virus && virus <= 10, "wrong virus");
    inf.readEof();

    return 0;
}
