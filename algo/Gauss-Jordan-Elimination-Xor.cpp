#include <bits/stdc++.h>

using namespace std;

int n, m;
bitset <1002> a[2001];
bitset <2001> b;
bitset <1001> res;

int Solve()
{
	for (int i = 1; i <= m; i++) a[i][n + 1] = b[i];
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		int cur = i;
		while (cur <= m && !a[cur][i]) cur++;
		if (cur > m) return 0;
		ans = max(ans, cur);
		if (cur != i) swap(a[cur], a[i]);
		for (int j = 1; j <= m; j++)
		{
			if (i == j || !a[j][i]) continue;
			a[j] ^= a[i];
		}
	}
	for (int i = 1; i <= n; i++) res[i] = a[i][n + 1];
	return ans;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	string str;
	bool t;
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> str >> t;
		for (int j = 1; j <= n; j++)
		{
			a[i][j] = (str[j - 1] == '0' ? 0 : 1);
		}
		b[i] = t;
	}
	int ans = Solve();
/*	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n + 1; j++) cerr << a[i][j];
		cerr << endl;
	}*/
	if (!ans)
	{
		cout << "Cannot Determine\n";
		return 0;
	}
	cout << ans << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << (res[i] ? "?y7M#\n" : "Earth\n");
	}
	return 0;
}