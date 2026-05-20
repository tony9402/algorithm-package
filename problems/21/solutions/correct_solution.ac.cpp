#include<iostream>
#include<vector>
#include<algorithm>

#define all(x) x.begin(), x.end()

using namespace std;
typedef long long ll;

vector<ll> list;

bool check(ll mid, ll now, ll cnt)
{
	if (!cnt)return true;
	for (int i = now; i < list.size(); i++)
		if (list[i] - list[now] >= mid)return check(mid, i, cnt - 1);
	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		ll input;
		cin >> input;
		list.push_back(input);
	}
	sort(all(list));
	ll left = 1, right = list.back() + 1;
	ll ans = 0;

	while (left <= right)
	{
		ll mid = (left + right) / 2;
		if (check(mid, 0, k - 1))left = mid + 1;
		else right = mid - 1;
	}
	cout << left - 1;
	return 0;
}