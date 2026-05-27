#include "testlib.h"
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

void Print(const vector<pair<int, int>> &V) {
    int N = (int)V.size();
    cout << N << '\n';
    for(const auto &[p, d]: V) {
        cout << p << ' ' << d << '\n';
    }
}


void random_generate(int N) {
    vector<pair<int, int>> V;
    for(int i = 0; i < N; ++i) {
        int p = rnd.next(1, 10000);
        int d = rnd.next(1, 10000);
        V.emplace_back(p, d);
    }
    Print(V);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int minN = opt<int>("minN", 0);
    int maxN = opt<int>("maxN", 10000);
    string mode = opt<string>("mode", "random");
    
    int N = rnd.next(minN, maxN);
    if(mode == "random") {
        random_generate(N);
    }
    return 0;
}
