#include "testlib.h"
#include <iostream>

using namespace std;

void random_generate(int N, int max_time = 2147483647) {
    cout << N << '\n';
    for(int i = 0; i < N; ++i) {
        int l = rnd.next(0, max_time);
        int r = rnd.next(l, max_time);
        cout << l << ' ' << r << '\n';
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int minN = opt<int>("minN", 1);
    int maxN = opt<int>("maxN", 100000);
    int max_time = opt<int>("max_time", 2147483647);
    string mode = opt<string>("mode", "random");
    
    int N = rnd.next(minN, maxN);
    if(mode == "random") {
        random_generate(N, max_time);
    }
    
    return 0;
}
