#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    int N = inf.readInt(1, 300); inf.readSpace();
    int M = inf.readInt(1, N);
    inf.readEoln();
    
    for(int i = 0; i < N; ++i) {
        int x = inf.readInt(1, 100);
        if(i + 1 == N) inf.readEoln();
        else inf.readSpace();
    }
    inf.readEof();
    return 0;
}
