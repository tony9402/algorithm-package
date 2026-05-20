#include<iostream>
#include<string>
#include<algorithm>

using namespace std;
char Map[1001][1001];
int dp[1001][1001];
int ans;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n,m;
	cin >> n >> m;
	for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            cin >> Map[i][j];
        }
    }

	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int now = Map[i][j] - 48;
			if(now)dp[i][j] = 1+min({dp[i-1][j-1],dp[i-1][j],dp[i][j-1]});
			ans = max(dp[i][j], ans);
		}
	}
	cout << ans*ans;
}