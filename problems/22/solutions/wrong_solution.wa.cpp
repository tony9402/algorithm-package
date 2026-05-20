#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
vector<int> vc, answer;
int n, k;

bool possible(int m, int c)
{
	if(c)cout<<m<<'\n',answer.clear();
	int g = 1, cnt = 0, sum = 0;
	for (int i = 0; i < n; i++)
	{
		if (sum + vc[i] > m || n - i == k - g)
		{
			if (k == g)return false;
			if(c)answer.push_back(cnt);
			sum = vc[i],cnt=1,g++;
		}
		else
			sum += vc[i],cnt++;
	}
	if(c)answer.push_back(cnt);
	return (g <= k);
}

int Parametric_Search(int l, int r)
{
	if (l+1>=r)return r;
	int m = (l + r) / 2;
	if (possible(m,0))return Parametric_Search(l, m);
	return Parametric_Search(m, r);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k;
	int l = 0, r = 0;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		vc.push_back(x);
		r += x;
		l = max(l, x);
	}
	possible(Parametric_Search(l-1,r),1);
	for (auto &i : answer)
		cout << i << ' ';

    cout << 0;
	return 0;
}