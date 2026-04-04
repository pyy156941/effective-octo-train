#include <bits/stdc++.h>

using namespace std;

const long long mod = 1000000007;

int n;
long long tr[401][801];

long long QPow(long long a, long long b)
{
	long long ans = 1;
	while (b)
	{
		if (b % 2) ans = (ans * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return ans;
}

long long Inverse(long long x)
{
	return QPow(x, mod - 2ll);
}

bool Simplify()
{
	for (int i = 1; i <= n; i++)
	{
		long long pv = -2e9;
		int p = i;
		for (int j = i; j <= n; j++)
		{
			if (abs(tr[j][i]) > pv)
			{
				pv = abs(tr[j][i]);
				p = j;
			}
		}
		if (!pv) return false;
		if (p != i) for (int j = 1; j <= 2 * n; j++) swap(tr[p][j], tr[i][j]);
		long long inv = Inverse(tr[i][i]);
		for (int j = 1; j <= n; j++)
		{
			if (j == i) continue;
			long long t = tr[j][i] * inv % mod;
			for (int k = i; k <= 2 * n; k++) tr[j][k] = (tr[j][k] - tr[i][k] * t % mod + mod) % mod; 
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = n + 1; j <= 2 * n; j++)
		{
			tr[i][j] = (tr[i][j] * Inverse(tr[i][i])) % mod;
		}
	}
	return true;
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> tr[i][j];
		}
		tr[i][n + i] = 1;
	}
	if (!Simplify()) cout << "No Solution\n";
	else
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = n + 1; j <= 2 * n; j++)
			{
				cout << tr[i][j] << ' ';
			}
			cout << endl;
		}
	}
}