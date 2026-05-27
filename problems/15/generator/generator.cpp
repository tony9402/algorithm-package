#include "testlib.h"
#include <iostream>

using namespace std;

void random_generate(int N, int M) {
    cout << N << ' '<< M << '\n';
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            int x = rnd.next(0, 1);
            cout << x;
        }
        cout << '\n';
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int minN = opt<int>("minN", 1);
    int maxN = opt<int>("maxN", 1000);
    int minM = opt<int>("minM", 1);
    int maxM = opt<int>("maxM", 1000);
    string mode = opt<string>("mode", "random");
    
    if(mode == "random") {
        int N = rnd.next(minN, maxN);
        int M = rnd.next(minM, maxM);
        random_generate(N, M);
    }
    
    return 0;
}
