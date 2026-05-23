// Problem: C1. Beautiful Patterns (Easy Version)
// Contest: Codeforces - Codeforces Round 1069 (Div. 1)
// URL: https://codeforces.com/contest/2174/problem/C1
// Memory Limit: 512 MB
// Time Limit: 2000 ms
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

bool multi_test = true;

ll preo1[2001], preo0[2001], pree1[2001], pree0[2001];
ll ipm[2001]; 
void solve()
{
	ll n, m, mod;
	cin >> n >> m >> mod;
	ll ans = 0;
	ipm[0] = 1;
	ll im = mod_inv(m, mod);
	for (int i = 1; i <= n; i++) ipm[i] = (ipm[i - 1] * im) % mod;
	for (int i = 1; i <= n; i++)
	{
		if (i % 2) 
		{
			preo1[i] = (ll)(n - i + 1) * ipm[i / 2] % mod;
			preo0[i] = (ll)(n - i) * ipm[i / 2] % mod;
			pree1[i] = pree0[i] = 0;
		}
		else
		{
			pree1[i] = (ll)(n - i + 1) * ipm[i / 2] % mod;
			pree0[i] = (ll)(n - i) * ipm[i / 2] % mod;
			preo1[i] = preo0[i] = 0;
		}
		preo1[i] += preo1[i - 1];
		preo1[i] %= mod;
		preo0[i] += preo0[i - 1];
		preo0[i] %= mod;
		pree1[i] += pree1[i - 1];
		pree1[i] %= mod;
		pree0[i] += pree0[i - 1];
		pree0[i] %= mod;
	}
	for (int i = 1; i <= n; i++)
	{
		ans += (ll)(n - i + 1) * ((i - 1) / 2) % mod * ipm[i / 2] % mod * 2ll % mod;
		ans += (ll)(n - i + 1) * ipm[i / 2] % mod;
		ans %= mod;
	}
	for (int i = 1; i <= n; i++)
	{
		ans += (ll)(n - i + 1) * (n - i) % mod * ipm[i / 2 + i / 2] % mod;
		if (i % 2)
		{
			ans += (ll)(n - i + 1) * preo0[i - 1] % mod * ipm[i / 2] % mod * 2ll % mod;
			ans += (ll)(n - i + 1) * pree1[i - 1] % mod * ipm[i / 2] % mod * 2ll % mod;
			ans %= mod;
		}
		else
		{
			ans += (ll)(n - i + 1) * preo1[i - 1] % mod * ipm[i / 2] % mod * 2ll % mod;
			ans += (ll)(n - i + 1) * pree0[i - 1] % mod * ipm[i / 2] % mod * 2ll % mod;
			ans %= mod;
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