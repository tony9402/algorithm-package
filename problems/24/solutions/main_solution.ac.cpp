#include <iostream>
#include <algorithm>

using namespace std;

int v[3000001],Count[3001];
bool used[3001];
int l,r,ans,cnt;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    int n,d,k,c;cin >> n >> d >> k >> c;
    for(int i=0;i<n;i++)cin >> v[i];

    while(r<k){
        if(!used[v[r]])cnt++;
        used[v[r]] = true;
        Count[v[r]]++;
        r++;
    }
    if(used[c])ans = cnt;
    else ans = cnt + 1;
    while(l < n){
        if(--Count[v[l]] == 0){
            used[v[l]] = false;
            cnt--;
        }
        Count[v[r]]++;
        if(!used[v[r]]){
            used[v[r]] = true;
            cnt++;
        }
        if(used[c])ans = max(ans, cnt);
        else ans = max(ans, cnt + 1);
        l++; r = (r + 1) % n;
    }
    cout << ans;

    return 0;
}