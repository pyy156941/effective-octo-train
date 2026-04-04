#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
map <ll, int> mp;

ll QPow(ll a, ll b, ll p)
{
	ll ans = 1;
	while (b)
	{
		if (b & 1) ans = (ans * a) % p;
		a = (a * a) % p;
		b >>= 1;
	}
	return ans;
}

int main()
{
	int p, b, n;
	cin >> p >> b >> n;
	b %= p;
	int lim = ceil(sqrt(p));
	ll base = n;
	for (int i = 1; i <= lim; i++)
	{
		base = (base * b) % p;
		mp[base] = i;
	}
	ll bm = QPow(b, lim, p);
	base = 1;
	for (int i = 1; i <= lim; i++)
	{
		base = (base * bm) % p;
		if (mp[base] && i * lim >= mp[base])
		{
			cout << i * lim - mp[base] << endl;
			return 0;
		}
	}
	cout << "no solution\n";
	return 0;
}