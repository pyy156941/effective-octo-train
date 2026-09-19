// Problem: G - Lightweight Knapsack
// Contest: AtCoder - JPRS Programming Contest 2026#1 (AtCoder Beginner Contest 442)
// URL: https://atcoder.jp/contests/abc442/tasks/abc442_g
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#pragma GCC optimize("O3,Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

using namespace std;

#define pb push_back
#define eb emplace_back
#define ls(x) x << 1
#define rs(x) x << 1 | 1
#define lowbit(x) (x & (-x))
#define ctz(x) (__builtin_ctz(x))
#define ppc(x) (__builtin_popcount(x))

using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;
using i128 = __int128;

#define gc() getchar()
#define pc(x) putchar(x)
#define isdigit(x) (x >= '0' && x <= '9')
#define least2p(x) ((x == 1) ? 0 : __lg(x) + ((x & (x - 1)) != 0))
#define debug(x) cerr << #x << " : " << x << endl;

#define yn(x) \
do \
{ \
    cout << (x ? 'Y' : 'N'); \
    cout << (x ? 'e' : 'o'); \
    cout << (x ? 's' : '\n'); \
    if (!x) cout << '\n'; \
} while(0)

#define ync(x) \
do \
{ \
    cout << (x ? 'Y' : 'N'); \
    cout << (x ? 'E' : 'O'); \
    cout << (x ? 'S' : '\n'); \
    if (!x) cout << '\n'; \
} while(0)

#define ynl(x) \
do \
{ \
    cout << (x ? 'y' : 'n'); \
    cout << (x ? 'e' : 'o'); \
    cout << (x ? 's' : '\n'); \
    if (!x) cout << '\n'; \
} while(0)

istream& operator >> (istream& cin, i128& x)
{
    x = 0;
    int f = 1;
    char ch;
    ch = cin.get();
    while (ch == ' ' || ch == '\n' || ch == '\t') ch = cin.get();
    if (ch == '-')
    {
        f = -1;
        ch = cin.get();
    }
    while (isdigit(ch))
    {
        x = x * 10 + (ch - '0');
        ch = cin.get();
    }
    cin.putback(ch);
    x *= f;
    return cin;
}

ostream& operator << (ostream& cout, i128 x)
{
    if (x == 0)
    {
        cout << '0';
        return cout;
    }
    if (x < 0)
    {
        cout << '-';
        x = -x;
    }
    if (x >= 10) cout << (x / 10);
    cout << (char)('0' + (x % 10));
    return cout;
}

template <typename ... Args>
void multi_read(Args& ... args)
{
    ((cin >> args), ...);
}

template <typename ... Args>
void multi_write(Args ... args)
{
    ((cout << args << " "), ...);
}

template <typename ... Args>
void multi_write_endl(Args ... args)
{
    ((cout << args << " "), ...);
    cout << endl;
}

template <typename T>
T fastgcd(T a, T b) // unsigned only, requires C++20
{
	if (a < b) 
	{
		T temp = a;
		a = b;
		b = temp;
	}
	if (!b) return a;
	a %= b;
	if (!a) return b;
	auto za = ctz(a);
	auto zb = ctz(b);
	a >>= za;
	b >>= zb;
	do 
	{
		T dif = a - b;
		if (a > b) a = b, b = dif;
		else b = b - a;
		b >>= ctz(dif);
	} while (!b);
	return a << min(za, zb);
}

template <typename T>
void exgcd(T a, T b, T &x, T &y)
{
	if (b == 0)
	{
		x = 1, y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}

template <typename T>
T mod_inv(T a, T p)
{
	T x, y;
	exgcd(a, p, x, y);
	return (x + p) % p;
}

template <typename T>
T qpow(T a, T b, T mod)
{
	T ans = 1;
	while (b)
	{
		if (b & 1) ans = ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}

bool multi_test = false;

struct item
{
	ll w, v, k;
	
	bool operator < (const item a) const
	{
		if (v * 6 / w != a.v * 6 / a.w) return (v * 6 / w) > (a.v * 6 / a.w);
		return w > a.w;
	}
}a[200001], l[200001];

ll dpa[40], dpl[40];
void solve()
{
	int n;
	ll c;
	cin >> n >> c;
	for (int i = 1; i <= n; i++) cin >> a[i].w >> a[i].v >> a[i].k;
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) l[i].w = a[i].w, l[i].v = a[i].v, l[i].v = a[i].v;
	ll cur = 0, v1 = 0;
	for (int i = 1; i <= n; i++)
	{
		if (cur + a[i].k * a[i].w <= c) 
		{
			cur += a[i].k * a[i].w;
			v1 += a[i].v * a[i].k;
			l[i].k = 0;
		}
		else
		{
			ll mxc = (c - cur) / a[i].w;
			cur += mxc * a[i].w;
			v1 += mxc * a[i].v;
			l[i].k = a[i].k - mxc;
			a[i].k = mxc;
		}
	}
	
	ll rest = c - cur;
	ll maxt = 30;
	for (int i = 1; i <= maxt; i++) dpa[i] = 1e18;
	for (int i = 1; i <= n; i++)
	{
		for (int j = maxt; j >= a[i].w; j--)
		{
			for (int k = 1; k <= min(a[i].k, j / a[i].w); k++) dpa[j] = min(dpa[j], dpa[j - k * a[i].w] + a[i].v * k);
		}
	}
	for (int i = 1; i <= maxt; i++) dpl[i] = -1e18;
	for (int i = 1; i <= n; i++)
	{
		for (int j = maxt; j >= l[i].w; j--)
		{
			for (int k = 1; k <= min(l[i].k, j / l[i].w); k++) dpl[j] = max(dpl[j], dpl[j - k * l[i].w] + l[i].v * k);
		}
	}
	ll ans = 0;
	for (int i = 0; i <= maxt; i++)
	{
		for (int j = 0; j <= maxt; j++)
		{
			if (j - i > rest) continue;
			ans = max(ans, v1 + dpl[j] - dpa[i]);
		}
	}
	cout << ans << endl;
	return;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr);
	int _ = 1;
	if (multi_test) cin >> _;
	while (_--) solve();
	return 0;
}