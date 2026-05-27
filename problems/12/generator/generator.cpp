#include "testlib.h"
#include <iostream>
#include <vector>

using namespace std;

void Print(const vector<int> &V) {
    int N = (int)V.size();
    cout << N << '\n';
    for(int i = 0; i < N; ++i) {
        cout << V[i] << '\n';
    }
}

void random_generate(int N) {
    vector<int> V(N);
    for(int i = 0; i < N; ++i) V[i] = rnd.next(1, 10000);
    Print(V);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int minN = opt<int>("minN", 1);
    int maxN = opt<int>("maxN", 300);
    string mode = opt<string>("mode", "random");
    
    int N = rnd.next(minN, maxN);
    if(mode == "random") {
        random_generate(N);
    }

    return 0;
}
