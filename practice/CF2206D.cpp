// Problem: D. Christmas Tree Un-decoration
// Contest: Codeforces - 2026 ICPC Asia Pacific Championship - Online Mirror (Unrated, Online Mirror, ICPC Rules, Teams Preferred)
// URL: https://codeforces.com/contest/2206/problem/D
// Memory Limit: 1024 MB
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

struct node
{
	ll mx, lt;
}tree[800001];

void pushup(int cur)
{
	tree[cur].mx = max(tree[ls(cur)].mx, tree[rs(cur)].mx);
}

void pushdown(int cur)
{
	if (tree[cur].lt == 0) return;
	tree[ls(cur)].mx += tree[cur].lt;
	tree[rs(cur)].mx += tree[cur].lt;
	tree[ls(cur)].lt += tree[cur].lt;
	tree[rs(cur)].lt += tree[cur].lt;
	tree[cur].lt = 0;
}

void build(int cur, int l, int r)
{
	tree[cur].mx = tree[cur].lt = 0; // here, don't use pushup to avoid leftovers (unpassed lt on leaf)
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(ls(cur), l, mid);
	build(rs(cur), mid + 1, r);
}

void update(int cur, int l, int r, int s, int t, ll x)
{
	if (l <= s && t <= r) 
	{
		tree[cur].mx += x;
		tree[cur].lt += x;
		return;
	}
	pushdown(cur);
	int mid = (s + t) >> 1;
	if (l <= mid) update(ls(cur), l, r, s, mid, x);
	if (r > mid) update(rs(cur), l, r, mid + 1, t, x);
	pushup(cur);
}

ll query(int cur, int l, int r, int s, int t)
{
	if (l <= s && t <= r) return tree[cur].mx;
	pushdown(cur);
	int mid = (s + t) >> 1;
	ll res = 0;
	if (l <= mid) res = max(res, query(ls(cur), l, r, s, mid));
	if (r > mid) res = max(res, query(rs(cur), l, r, mid + 1, t));
	return res;
}

int n, q;
ll a[200001];
ll dp[200001], s[200001]; // dp value of every son except heavy son
vector <int> adj[200001];
int fa[200001], dep[200001], siz[200001], hson[200001], dfn[200001], rnk[200001], top[200001], bot[200001], dfc = 0;

void dfs1(int cur)
{
	siz[cur] = 1;
	for (auto it : adj[cur])
	{
		if (it == fa[cur]) continue;
		dep[it] = dep[cur] + 1;
		dfs1(it);
		siz[cur] += siz[it];
		if (!hson[cur] || siz[it] > siz[hson[cur]]) hson[cur] = it; 
	}
}

void dfs2(int cur, int head)
{
	top[cur] = head;
	if (!bot[head] || dep[cur] > dep[bot[head]]) bot[head] = cur; // bottom of heavy chain
	dfn[cur] = ++dfc;
	rnk[dfc] = cur;
	if (hson[cur])
	{
		dfs2(hson[cur], head);
		dp[cur] += dp[hson[cur]];
	}
	for (auto it : adj[cur])
	{
		if (it == fa[cur] || it == hson[cur]) continue;
		dfs2(it, it);
		dp[cur] += dp[it];
		s[cur] += dp[it];
	}
	dp[cur] = max(dp[cur], a[cur]);
}

void update_chain(int u, int v, ll x)
{
	// cerr << u << ' ' << v << endl;
	while (top[u] != top[v])
	{
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		update(1, dfn[top[u]], dfn[u], 1, n, x);
		u = fa[top[u]];
	}
	if (dep[u] < dep[v]) swap(u, v);
	update(1, dfn[v], dfn[u], 1, n, x);
}

ll query_chain(int u, int v)
{
	// cerr << u << ' ' << v << endl;
	ll res = 0;
	while (top[u] != top[v])
	{
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		res = max(res, query(1, dfn[top[u]], dfn[u], 1, n));
		u = fa[top[u]];
	}
	if (dep[u] < dep[v]) swap(u, v);
	res = max(res, query(1, dfn[v], dfn[u], 1, n));
	return res;
}

void solve()
{
	cin >> n >> q;
	for (int i = 1; i <= n; i++) 
	{
		fa[i] = dep[i] = siz[i] = hson[i] = dfn[i] = rnk[i] = top[i] = bot[i] = 0;
		adj[i].clear();
		dfc = 0;
		dp[i] = s[i] = 0;
	}
	for (int i = 2; i <= n; i++) 
	{
		cin >> fa[i];
		adj[i].pb(fa[i]);
		adj[fa[i]].pb(i);
	}
	for (int i = 1; i <= n; i++) cin >> a[i];
	build(1, 1, n);
	dfs1(1);
	dfs2(1, 1);
	for (int i = 1; i <= n; i++)
	{
		update_chain(i, i, a[i]);
		if (hson[i]) update_chain(bot[top[i]], hson[i], s[i]);
	}
	int u;
	ll x;
	cout << dp[1] << endl;
	for (int i = 1; i <= q; i++)
	{
		cin >> u >> x;
		ll dif = x - a[u];
		update_chain(u, u, dif);
		a[u] = x;
		ll cur_dp = 0;
		while (u)
		{
			cur_dp = query_chain(bot[top[u]], top[u]);
			ll dift = cur_dp - dp[top[u]];
			dp[top[u]] = cur_dp; // do not update fa[top[u]], it might be top[fa[top[u]]]
			u = fa[top[u]]; 
			if (u) update_chain(bot[top[u]], hson[u], dift);
		}
		cout << dp[1] << endl;
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