// Problem: F1. Christmas Reindeer (easy version)
// Contest: Codeforces - Educational Codeforces Round 186 (Rated for Div. 2)
// URL: https://codeforces.com/contest/2182/problem/F1
// Memory Limit: 512 MB
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

ll calc(ll p, ll c, ll alr)
{
	if (p < alr || !c) return 0;
	ll lef = p - alr + 1;
	if (c >= lef) return (1ll << lef) - 1ll;
	else return (1ll << lef) - (1ll << (lef - c));
}

int cnt[61];
ll fact[600001], invf[600001];
constexpr ll mod = 998244353;

ll binom(ll n, ll m)
{
	if (m > n) return 0;
	return fact[n] * invf[m] % mod * invf[n - m] % mod;
}

ll solve(ll x, ll xb, ll alr)
{
	// cerr << x << ' ' << xb << ' ' << alr << endl;
	if (x <= 0)
	{
		ll all = 0;
		for (int b = xb; b >= 0; b--) all += cnt[b];
		return qpow(2ll, all, mod);
	}
	if (xb < 0) return 1;
	ll mx = 0, calr = alr;
	for (int b = xb; b >= 0; b--)
	{
		if (!cnt[b]) continue;
		mx += calc(b, cnt[b], calr);
		calr += cnt[b];
	}
	if (mx < x) return 0;
	ll ans = 0, fb = -1;
	for (int b = xb; b >= alr; b--)
	{
		if ((1ll << (b - alr)) < x) 
		{
			fb = b;
			break;
		}
	}
	if (fb > -1)
	{
		for (int i = 0; i <= cnt[fb]; i++)
		{
			ll ch = calc(fb, i, alr);
			ans += binom(cnt[fb], i) * solve(x - ch, fb - 1, alr + i) % mod;
			// cerr << fb << ' ' << i << ' ' << ans << endl;
			ans %= mod;
		}
	}
	ll cc = 0;
	for (int b = 0; b <= xb; b++)
	{
		if (cnt[b] && b >= alr && (1ll << (b - alr)) >= x)
		{
			ans += qpow(2ll, cc, mod) * ((qpow(2ll, (ll)cnt[b], mod) + mod - 1) % mod) % mod;
			ans %= mod;
		}
		cc += cnt[b];
	}
	return ans;
}

void solve()
{
	int n, m, c;
	cin >> n >> m;
	fact[0] = fact[1] = 1;
	invf[0] = invf[1] = 1;
	for (int i = 1; i <= n + m; i++) fact[i] = (fact[i - 1] * (ll)i) % mod, invf[i] = mod_inv(fact[i], mod);
	for (int i = 0; i <= 60; i++) cnt[i] = 0;
	for (int i = 1; i <= n; i++) cin >> c, cnt[c]++;
	int mode;
	ll x;
	for (int i = 1; i <= m; i++)
	{
		cin >> mode >> x;
		if (mode == 1) cnt[x]++;
		else if (mode == 2) cnt[x]--;
		else cout << solve(x, 60, 0) << endl;
	}
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