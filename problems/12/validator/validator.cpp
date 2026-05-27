#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 300);
    inf.readEoln();
    
    for(int i = 0; i < N; ++i) {
        int x = inf.readInt(1, 10000);
        inf.readEoln();
    }
    inf.readEof();
    
    return 0;
}
