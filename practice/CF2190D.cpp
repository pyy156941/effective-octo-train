// Problem: D. Prufer Vertex
// Contest: Codeforces - Codeforces Round 1073 (Div. 1)
// URL: https://codeforces.com/contest/2190/problem/D
// Memory Limit: 256 MB
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

int fa[200001], siz[200001];

void clear(int n)
{
	for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
}

int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
	int fx = find(x), fy = find(y);
	if (fx == fy) return;
	if (siz[fx] > siz[fy]) swap(fx, fy);
	fa[fx] = fy;
	siz[fy] += siz[fx];
}

bool a2n[200000], c2n[200000];

constexpr ll mod = 998244353;
ll ans[200000];
void solve()
{
	int n, m;
	multi_read(n, m);
	clear(n - 1);
	for (int i = 1; i < n; i++) a2n[i] = c2n[i] = false, ans[i] = 0;
	int u, v;
	for (int i = 1; i <= m; i++) 
	{
		multi_read(u, v);
		if (u == n) a2n[v] = true;
		else if (v == n) a2n[u] = true;
		else merge(u, v);
	}
	ll k = 1, sn = 1;
	ll tot = 1;
	for (int i = 1; i < n; i++) if (a2n[i]) c2n[find(i)] = true;
	for (int i = 1; i < n; i++) if (c2n[find(i)]) c2n[i] = true;
	for (int i = 1; i < n; i++) 
	{
		if (!c2n[i] && fa[i] == i) k++, tot = tot * siz[i] % mod;
		else if (c2n[i]) sn++;
	}
	tot = tot * sn % mod;
	if (k > 1) tot = tot * qpow((ll)n, k - 2, mod) % mod;
	else tot = 1;
	// cerr << k << ' ' << tot << endl;
	if (c2n[n - 1]) 
	{
		for (int i = 1; i < n; i++)
		{
			if (a2n[i] && find(i) == find(n - 1)) ans[i] = tot;
			cout << ans[i] << ' ';
		}
		cout << endl;
		return;
	}
	ll sn1 = siz[find(n - 1)];
	ll isn = mod_inv(sn, mod), isn1 = mod_inv(sn1, mod), in = mod_inv((ll)n, mod);
	for (int i = 1; i < n; i++)
	{
		ll si = siz[find(i)];
		if (a2n[i]) ans[i] = tot * si % mod * isn % mod;
		else if (find(i) == find(n - 1)) ans[i] = tot * (sn + sn1) % mod * isn % mod * isn1 % mod * in % mod;
		else if (!c2n[i]) ans[i] = tot * isn % mod * in % mod;
		cout << ans[i] << ' ';
	}
	cout << endl;
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