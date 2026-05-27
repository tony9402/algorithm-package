#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 18);
    inf.readEoln();
    
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            int x = inf.readInt(0, 1);
            if(j + 1 != N) inf.readSpace();
        }
        inf.readEoln();
    }
    inf.readEof();
    
    return 0;
}
