#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> vc;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, input;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> input;
		vc.push_back(input);
	}

	if (n == 1)return cout << vc[0],0;

	sort(vc.begin(), vc.end());
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		ans = ans > vc[i] * (n - i) ? ans : vc[i] * (n - i);
	}
	cout << ans;
	return 0;
}