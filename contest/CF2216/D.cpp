// Problem: D. RReeppeettiittiioonn
// Contest: Codeforces - Codeforces Round 1092 (Unrated, Div. 2, Based on THUPC 2026 — Finals)
// URL: https://codeforces.com/contest/2216/problem/D
// Memory Limit: 512 MB
// Time Limit: 2500 ms
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

int all_tid(ll n, ll b)
{
	ll t = n;
	ll lasv = -1, lasl = 0, llen = 0;
	while (t)
	{
		int it = t % b;
		t /= b;
		if (lasv < 0)
		{
			lasv = it;
			lasl = 1;
		}
		else if (lasv != it)
		{
			if (!llen) llen = lasl;
			else if (llen != lasl) llen = gcd(llen, lasl);
			lasv = it;
			lasl = 1;
		}
		else lasl++;
		if (llen == 1) return 0;
	}
	if (!llen) llen = lasl;
	else if (llen != lasl) llen = gcd(llen, lasl);
	if (llen == 1) return 0;
	int res = -1;
	for (int i = 1; i <= sqrt(llen); i++)
	{
		if (llen % i) continue;
		if (i * i == llen) res++;
		else res += 2;
	}
	// cerr << n << ' ' << b << ' ' << res << endl;
	return res;
}

ll thres;
int get_sol(ll n, ll x)
{
	int res = 0;
	ll c = n / x;
	ll b = c - 1;
	if (b > thres && x < b) res++;
	return res;
}

void solve()
{
	ll n;
	cin >> n;
	ll ans = 0;
	thres = sqrt(n) + 100ll;
	for (ll i = 2; i <= min(n, thres); i++) ans += all_tid(n, i);
	for (ll i = 2; i <= sqrt(n); i++)
	{
		if (n % i) continue;
		if (i * i == n) ans += get_sol(n, i);
		else ans += get_sol(n, i), ans += get_sol(n, n / i);
	}
	ans += get_sol(n, 1);
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