#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
map <ll, int> mp;

ll exgcd(ll a, ll b, ll &x, ll &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	else
	{
		ll r = exgcd(b, a % b, y, x);
		y -= a / b * x;
		return r;
	}
}

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

ll BSGS(ll p, ll b, ll n) // b ^ x = n mod p
{
	mp.clear(); 
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
		if (mp.find(base) == mp.end()) continue;
		int f = mp[base];
		if (i * lim >= f) return i * lim - f;
	}
	return -1;
}

ll inv(ll a, ll p)
{
	ll x, y;
	exgcd(a, p, x, y);
	return (x + p) % p;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int a, p, b;
	while (1)
	{
		cin >> a >> p >> b;
		if (a + p + b == 0) break;
		b %= p;
		if (b == 1 || p == 1) 
		{
			cout << 0 << "\n";
			continue;
		}
		int gcd = __gcd(a, p), k = 0;
		ll mul = 1;
		bool flag = false;
		while (gcd > 1)
		{
			if (b % gcd) 
			{
				cout << "No Solution\n";
				flag = true;
				break;
			}
			k++;
			p /= gcd;
			b /= gcd;
			mul = (mul * (a / gcd)) % p;
			if (mul == b) 
			{
				cout << k << '\n';
				flag = true;
				break;
			}
			gcd = __gcd(a, p);
		}
		if (flag) continue;
		ll rig = b * inv(mul, p) % p;
		ll ans = BSGS(p, a, rig);
		if (ans == -1) cout << "No Solution\n";
		else cout << ans + k << '\n';
	}
	return 0;
}