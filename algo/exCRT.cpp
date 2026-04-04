#include <bits/stdc++.h>

using namespace std;

typedef __int128 ll;
int n;
pair <ll, ll> eq[200001];

void Read(ll &x)
{
	x = 0;
	int f = 1;
	char ch = getchar();
	while (!isdigit(ch))
	{
		if (ch == '-') f = -1; ch = getchar();	
	}	
	while (isdigit(ch))
	{
		x = x * 10 + ch - 48; ch = getchar();
	}
	x *= f;
} 

void Print(ll x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x > 9) Print(x / 10);
	putchar(x % 10 + '0');
}

ll gcd(ll a, ll b)
{
	if (b == 0) return a;
	else return gcd(b, a % b);
}

ll qpow(ll a, ll b, ll p)
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

void exgcd(ll a, ll b, ll &x, ll &y)
{
	if (!b)
	{
		x = 1, y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}

ll inv(ll a, ll p)
{
	ll res, y;
	exgcd(a, p, res, y);
	return res;
}

pair <ll, ll> slove(ll a, ll b) // x1, x2
{
	pair <ll, ll> res;
	res.first = (inv(a, b) + b) % b;
	res.second = (1 - a * res.first) / b;
//	cerr << (int)a << ' ' << (int)b << ' ' << (int)res.first << ' ' << (int)res.second << endl;
	return res;
}

pair <ll, ll> rep(pair <ll, ll> eq1, pair <ll, ll> eq2)
{
	ll a1 = eq1.first, a2 = eq2.first, b1 = eq1.second, b2 = eq2.second;
	ll ga = gcd(a1, a2), p = a1 * a2 / ga;
	assert((b2 - b1) % ga == 0);
	pair <ll, ll> res;
	res.first = p;
	pair <ll, ll> tmp = slove(a1 / ga, a2 / ga);
	tmp.first = (tmp.first * ((b2 - b1) / ga) + p) % p;
	res.second = (tmp.first * a1 % p + b1 + p) % p;
	return res;
}

int main()
{
//	ios :: sync_with_stdio(false);
//	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	int st = 1, en = n;
	for (int i = 1; i <= n; i++) Read(eq[i].first), Read(eq[i].second);
	while (en - st)
	{
		eq[++en] = rep(eq[st], eq[st + 1]);
		st += 2;
	}
	Print(eq[en].second);
	putchar('\n');
	return 0;
}