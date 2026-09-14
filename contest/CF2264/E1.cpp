// Problem: E1. A Prime Flood (Easy Version)
// Contest: Codeforces - Codeforces Round 1121 (Div. 2)
// URL: https://codeforces.com/contest/2264/problem/E1
// Memory Limit: 256 MB
// Time Limit: 3000 ms
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

constexpr int N = 3000;
bool np[N + 1];
int tmc[N + 1];
vector <int> pr;
void init()
{
	for (int i = 2; i <= N; i++)
	{
		if (!np[i]) 
		{
			pr.pb(i);
			for (int j = 2 * i; j <= N; j += i) np[j] = true;
		}
	}
	tmc[1] = N + 1;
	for (int i = 2; i <= N; i++)
	{
		for (auto p : pr)
		{
			if (i % p == 0) 
			{
				tmc[i] = i * p;
				break;
			}
		}
	}
}

int buc[3001], pre[3001], x[3001][3001];
vector <int> pf[3001];

constexpr ll mod = 998244353;
void solve()
{
	int n, a;
	cin >> n;
	for (int i = 1; i <= n; i++) 
	{
		buc[i] = pre[i] = 0;
		for (auto p : pr) if (i % p == 0) pf[i].pb(p);
	}
	for (int i = 1; i <= n; i++)
	{
		cin >> a;
		buc[a]++;
	}
	pre[0] = 0;
	for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + buc[i];
	for (int i = 1; i <= n; i++)
	{
		x[i][i] = i;
		for (int j = i + 1; j <= n; j++)
		{
			bool ok = false;
			for (auto p : pf[j]) 
			{
				if (i % p) 
				{
					ok = true;
					break;
				}
			}
			if (!ok) x[i][j] = x[i - 1][j - 1];
			else x[i][j] = x[i][j - 1];
		}
	}
	ll ans = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = i; j <= n; j++)
		{
			ll mult = (qpow(2ll, (ll)buc[j], mod) + mod - 1) % mod;
			if (j > i)
			{
				mult = (mult * (qpow(2ll, (ll)buc[i], mod) + mod - 1) % mod) % mod;
				mult = (mult * qpow(2ll, (ll)pre[j - 1] - pre[i], mod)) % mod;
			}
			ans = (ans + x[i][j] * mult % mod) % mod;
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
	init();
	if (multi_test) cin >> _;
	while (_--) solve();
	return 0;
}