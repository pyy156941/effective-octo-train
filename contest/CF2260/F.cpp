// Problem: F. Edge Three-Coloring
// Contest: Codeforces - Educational Codeforces Round 194 (Rated for Div. 2)
// URL: https://codeforces.com/contest/2260/problem/F
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

bool multi_test = true;

int fa[3001], dep[3001], siz[3001], fa_t[3001];
vector <int> adj[3001], adj_t[3001];
vector <pair <int, int>> nt;

void dfs(int cur)
{
	for (auto it : adj[cur])
	{
		if (it == fa[cur]) continue;
		if (fa[it]) 
		{
			nt.pb({min(it, cur), max(it, cur)});
			continue;
		}
		fa[it] = cur;
		dep[it] = dep[cur] + 1;
		dfs(it);
	}
}

void dfs_t(int cur)
{
	siz[cur] = 1;
	for (auto it : adj_t[cur])
	{
		if (it == fa_t[cur]) continue;
		if (fa_t[it]) continue;
		fa_t[it] = cur;
		dfs_t(it);
		siz[cur] += siz[it];
	}
}

int cdeg[3001], ec[3001];

void jmp(int u, int v)
{
	while (dep[u] != dep[v])
	{
		if (dep[u] > dep[v]) ec[u]++, u = fa[u];
		else ec[v]++, v = fa[v];
	}
	while (u != v) 
	{
		ec[u]++;
		ec[v]++;
		u = fa[u];
		v = fa[v];
	}
}

void solve()
{
	int n, m, u, v;
	cin >> n >> m;
	nt.clear();
	for (int i = 1; i <= n; i++) fa[i] = dep[i] = 0, adj[i].clear();
	for (int i = 1; i <= m; i++)
	{
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	fa[1] = 1;
	dfs(1);
	sort(nt.begin(), nt.end());
	nt.erase(unique(nt.begin(), nt.end()), nt.end());
	// cerr << n << ' ' << m << ' ' << nt.size() << endl;
	// for (auto [u, v] : nt) cerr << u << ' ' << v << endl;
	int cross = m - n + 1;
	for (int mask = 1; mask < (1 << cross); mask++) // mask = 0 -> mask = 1 : WA #2 -> WA #17
	{
		for (int i = 1; i <= n; i++) cdeg[i] = ec[i] = 0;
		for (int i = 0; i < cross; i++)
		{
			if (!(mask & (1 << i))) continue;
			cdeg[nt[i].first]++;
			cdeg[nt[i].second]++;
			jmp(nt[i].first, nt[i].second);
		}
		for (int i = 2; i <= n; i++) if (ec[i] % 2) cdeg[fa[i]]++, cdeg[i]++;
		bool ok = true;
		for (int i = 1; i <= n; i++)
		{
			if (cdeg[i] != 0 && cdeg[i] != 2) 
			{
				ok = false;
				break;
			}
		}
		if (!ok) continue;
		for (int i = 1; i <= n; i++) adj_t[i].clear(), fa_t[i] = siz[i] = 0;
		for (int i = 0; i < cross; i++)
		{
			if (mask & (1 << i)) continue;
			adj_t[nt[i].first].pb(nt[i].second);
			adj_t[nt[i].second].pb(nt[i].first);
		}
		for (int i = 2; i <= n; i++) if (ec[i] % 2 == 0) adj_t[i].pb(fa[i]), adj_t[fa[i]].pb(i);
		fa_t[1] = 1; // Addition : WA #17 -> AC
		dfs_t(1);
		if (siz[1] == n)
		{
			cout << "YES" << endl;
			return;
		}
	}
	cout << "NO" << endl;
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