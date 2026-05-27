#include<iostream>
#include<vector>
#include<algorithm>

#define all(x) x.begin(), x.end()

using namespace std;

int arr[4000][4];
vector<int> l, r;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    for(int i=0;i<n;i++)
        for(int j=0;j<4;j++)
            cin >> arr[i][j];

    l.resize(n*n);
    r.resize(n*n);

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            l[i*n+j]=arr[i][0]+arr[j][1];
            r[i*n+j]=arr[i][2]+arr[j][3];
        }
    }

    sort(all(l));
    sort(all(r));
    
    unsigned int ans = 0;
    for(auto i : l){
        auto up = upper_bound(all(r), -i);
        auto lp = lower_bound(all(r), -i);
        ans = ans + (up - lp);
    }

    cout << ans;
}