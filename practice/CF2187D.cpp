// Problem: D. Cool Problem
// Contest: Codeforces - Codeforces Round 1077 (Div. 1)
// URL: https://codeforces.com/contest/2187/problem/D
// Memory Limit: 256 MB
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

bool multi_test = true;

int n;
i128 x, y;
int s[100001];
bitset <100001> pos[2][2], neg[2][2];

ll get_sum(i128 v)
{
	return (v * v + (i128)(x - y) * v + (i128)n * x * y) / (i128)(2 * x);
}

constexpr i128 mod = 998244353;
void solve()
{
	string str;
	cin >> n >> x >> y >> str;
	for (int i = 1; i <= n; i++)
	{
		if (str[i - 1] == '?') s[i] = -1;
		else if (str[i - 1] == '0') s[i] = 0;
		else s[i] = 1;
	}
	pos[0][1].reset(), neg[0][1].reset();
	pos[1][1].reset(), neg[1][1].reset();
	pos[0][1][0] = 1;
	neg[0][1][0] = 1;
	int cd = 1;
	for (int i = 1; i <= n; i++)
	{
		cd ^= 1;
		if (s[i] == -1)
		{
			pos[0][cd] = neg[1][cd ^ 1] | (pos[0][cd ^ 1] << 1);
			pos[1][cd] = neg[0][cd ^ 1] | (pos[1][cd ^ 1] << 1);
			neg[0][cd] = pos[1][cd ^ 1] | (neg[0][cd ^ 1] >> 1);
			neg[1][cd] = pos[0][cd ^ 1] | (neg[1][cd ^ 1] >> 1);
		}
		else if (s[i] == 1)
		{
			pos[0][cd] = neg[1][cd ^ 1];
			pos[1][cd] = neg[0][cd ^ 1];
			neg[0][cd] = pos[1][cd ^ 1];
			neg[1][cd] = pos[0][cd ^ 1];
		}
		else
		{
			pos[0][cd] = pos[0][cd ^ 1] << 1;
			pos[1][cd] = pos[1][cd ^ 1] << 1;
			neg[0][cd] = neg[0][cd ^ 1] >> 1;
			neg[1][cd] = neg[1][cd ^ 1] >> 1;
		}
		pos[0][cd][0] = neg[0][cd][0] = pos[0][cd][0] | neg[0][cd][0]; // here pos[x][cd][0] and neg[x][cd][0] are essentially the same, so sync (they are calculated differently, not guaranteed to be equal)
		pos[1][cd][0] = neg[1][cd][0] = pos[1][cd][0] | neg[1][cd][0];
	}
	set <i128> sl;
	for (int i = 0; i <= n; i++) 
	{
		if (pos[0][cd][i]) sl.insert(get_sum((i128)x * i));
		if (pos[1][cd][i]) sl.insert(get_sum((i128)x * i + y));
		if (neg[0][cd][i]) sl.insert(get_sum((i128)-x * i));
		if (neg[1][cd][i]) sl.insert(get_sum((i128)-x * i + y));
	}
	i128 ans = 0;
	for (auto it : sl) ans = (ans + it % mod + mod) % mod;
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