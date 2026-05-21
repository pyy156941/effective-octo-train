// Problem: E. Graph Cutting
// Contest: Codeforces - Codeforces Round 1099 (Div. 2)
// URL: https://codeforces.com/contest/2231/problem/E
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

int n, d;
vector <int> adj[2001];
int fa[2001], dep[2001], siz[2001], dfn[2001], rnk[2001], dfc = 0;
ll d1[2001][2011], d2[2001][2001], ans[2001]; // d1 is the number of nodes with depth j relative to i in subtree i
// d2 is the number of combinations of two paths i -> u and i -> v (LCA(u, v) != u or v) that cover j nodes in subtree i

void dfs1(int cur)
{
	siz[cur] = 1;
	dfn[cur] = ++dfc;
	rnk[dfc] = cur;
	for (auto it : adj[cur])
	{
		if (it == fa[cur]) continue;
		fa[it] = cur;
		dep[it] = dep[cur] + 1;
		dfs1(it);
		siz[cur] += siz[it];
		for (int i = 0; i <= n; i++)
		{
			int j = d - i - 1;
			if (j < 0) break;
			ans[cur] += d2[cur][j] * d1[it][i];
		}
		for (int i = 0; i <= n; i++)
		{
			int j = d - i - 1;
			if (j <= 0) break;
			ans[cur] += d2[it][i] * d1[cur][j];
		}
		for (int i = 0; i <= n; i++)
		{
			if (!d1[it][i]) break;
			for (int j = 1; j <= n; j++)
			{
				if (!d1[cur][j]) break;
				d2[cur][i + j + 2] += d1[it][i] * d1[cur][j];
				if (i + j + 2 == d)	ans[cur] += (ll)(i + j - 1) * d1[it][i] * d1[cur][j];
			}
		}
		for (int i = 0; i <= n; i++) d2[cur][i + 1] += d2[it][i];
		for (int i = 0; i <= n; i++)
		{
			if (!d1[it][i]) break;
			d1[cur][i + 1] += d1[it][i];
		}
	}
	d1[cur][0]++;
	ans[cur] += (ll)(d - 2) * d1[cur][d - 1];
	ans[cur] += d2[cur][d];
	// debug(cur);
	// for (int i = 0; i <= n; i++) cerr << d1[cur][i] << ' ';
	// cerr << endl;
	// for (int i = 0; i <= n; i++) cerr << d2[cur][i] << ' ';
	// cerr << endl;
	// debug(ans[cur]);
}

void solve()
{
	cin >> n >> d;
	for (int i = 1; i <= n; i++)
	{
		fa[i] = dep[i] = siz[i] = dfn[i] = rnk[i] = ans[i] = 0;
		dfc = 0;
		adj[i].clear();
		for (int j = 0; j <= n + 10; j++) d1[i][j] = d2[i][j] = 0;
	}
	int u, v;
	for (int i = 1; i < n; i++) 
	{
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	dfs1(1);
	ll fans = 0;
	for (int i = 1; i <= n; i++) fans += ans[i];
	cout << fans << endl;
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