#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<pair<int, int>> list;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		list.push_back(make_pair(b, a));
	}

	sort(list.begin(), list.end());

	int now = -1, ans = 0;

	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].second >= now)
		{
			now = list[i].first;
			ans++;
		}
	}

	cout << ans;
	return 0;
}