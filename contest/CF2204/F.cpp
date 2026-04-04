// Problem: F. Sum of Fractions
// Contest: Codeforces - Educational Codeforces Round 188 (Rated for Div. 2)
// URL: https://codeforces.com/contest/2204/problem/F
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

bool multi_test = false;

int n, m;
int a[500001], k[500001];
int st[500001][21]; // min
int l2[500001];

void init_st()
{
	l2[1] = 0;
	for (int i = 2; i <= n; i++) l2[i] = l2[i / 2] + 1;
	for (int i = 1; i <= n; i++) st[i][0] = i;
	for (int b = 1; b <= 20; b++)
	{
		for (int i = 1; i <= n; i++) 
		{
			int c1 = st[i][b - 1];
			int c2 = st[min(n, i + (1 << (b - 1)))][b - 1];
			if (a[c1] < a[c2]) st[i][b] = c1;
			else st[i][b] = c2;
		}
	}
	return;
}

int qmin(int l, int r)
{
	int s = l2[r - l + 1];
	int c1 = st[l][s], c2 = st[r - (1 << s) + 1][s];
	if (a[c1] < a[c2]) return c1;
	return c2;
}

ll times[500001];
pair <int, int> ai[500001];
constexpr ll mod = 998244353;
void get(int l, int r)
{
	if (l > r) return;
	if (l == r) 
	{
		times[l] = 1;
		return;
	}
	int p = qmin(l, r);
	times[p] = (ll)(p - l + 1) * (r - p + 1) % mod;
	get(l, p - 1);
	get(p + 1, r);
	return;
}

ll ans[500001];
void solve()
{
	multi_read(n, m);
	for (int i = 1; i <= n; i++) cin >> a[i], ai[i] = {a[i], i};
	init_st();
	for (int i = 1; i <= m; i++) cin >> k[i];
	get(1, n);
	ll ians = 0;
	for (int i = 1; i <= n; i++)
	{
		ians += mod_inv((ll)a[i], mod) * (((ll)i * (ll)(n - i + 1) - times[i]) % mod) % mod; 
		ians %= mod;
	}
	for (int i = 1; i <= m; i++) ans[i] = ians;
	sort(ai + 1, ai + n + 1);
	ll s1 = 0, s2 = 0, c1 = 0;
	for (int i = 1; i <= n; i++) s2 = (s2 + mod_inv((ll)a[i], mod) * times[i] % mod) % mod;
	int p = 0;
	for (int i = 1; i <= m; i++)
	{
		while (p < n && ai[p + 1].first <= k[i] + 1) 
		{
			p++;
			s1 = (s1 + (ll)ai[p].first * times[ai[p].second] % mod) % mod;
			s2 = (s2 - mod_inv((ll)ai[p].first, mod) * times[ai[p].second] % mod + mod) % mod;
			c1 = (c1 + times[ai[p].second]) % mod;
		}
		ans[i] = (ans[i] + (ll)(k[i] + 1) * s2 % mod);
		ans[i] = (ans[i] + (ll)(k[i] + 2) * c1 % mod) % mod;
		ans[i] = (ans[i] - s1 + mod) % mod;
	}
	for (int i = 1; i <= m; i++) cout << ans[i] << endl;
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