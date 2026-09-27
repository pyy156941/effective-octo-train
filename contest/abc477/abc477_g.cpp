// Problem: G - Frequency Query on Tree
// Contest: AtCoder - UNICORNProgramming Contest2026(AtCoder Beginner Contest 477)
// URL: https://atcoder.jp/contests/abc477/tasks/abc477_g
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

bool multi_test = false;

int n;
int x[200001];
int fa[200001], dep[200001], siz[200001], hson[200001], in[200001], out[200001], top[200001];
int bfn[400001], bfc = 0;
vector <int> adj[200001];

void dfs1(int cur)
{
	siz[cur] = 1;
	bfn[++bfc] = cur;
	in[cur] = bfc;
	for (auto it : adj[cur])
	{
		if (it == fa[cur]) continue;
		fa[it] = cur;
		dep[it] = dep[cur] + 1;
		dfs1(it);
		siz[cur] += siz[it];
		if (!hson[cur] || siz[it] > siz[hson[cur]]) hson[cur] = it;
	}
	bfn[++bfc] = cur;
	out[cur] = bfc;
}

void dfs2(int cur, int head)
{
	top[cur] = head;
	if (hson[cur]) dfs2(hson[cur], head);
	for (auto it : adj[cur])
	{
		if (it == fa[cur] || it == hson[cur]) continue;
		dfs2(it, it);
	}
}

int lca(int x, int y)
{
	while (top[x] != top[y])
	{
		if (dep[top[x]] > dep[top[y]]) x = fa[top[x]];
		else y = fa[top[y]];
	}
	return dep[x] > dep[y] ? y : x;
}

int bsn, bsq;
int lb[200001], rb[200001], bel[200001], blk[200001];
int buc[200001], cbuc[200001]; // occurrence of color, occurrence of occurrence of color
bool occ[200001]; // parity of occurrence of node

void update_occ(int o, int x)
{
	cbuc[o] += x;
	blk[bel[o]] += x;
}

int query(int a, int b)
{
	int res = 0;
	if (bel[a] == bel[b])
	{
		for (int i = a; i <= b; i++) res += cbuc[i];
		return res;
	}
	for (int i = a; i <= rb[bel[a]]; i++) res += cbuc[i];
	for (int i = lb[bel[b]]; i <= b; i++) res += cbuc[i];
	for (int i = bel[a] + 1; i < bel[b]; i++) res += blk[i];
	return res;
}

void update_c(int c, int x)
{
	update_occ(buc[c], -1);
	buc[c] += x;
	update_occ(buc[c], 1);
}

void update_node(int p)
{
	if (occ[p]) update_c(x[p], -1);
	else update_c(x[p], 1);
	occ[p] ^= 1;
}

int getblockq(int p)
{
	return (p + bsq - 1) / bsq;
}

struct qry
{
	int s, t, a, b, l, id;
	bool type;
	
	bool operator < (const qry o) const
	{
		if (getblockq(s) != getblockq(o.s)) return s < o.s;
		return (getblockq(s) & 1) ? t < o.t : t > o.t;
	}
}qs[200001];
int ans[200001];

void solve()
{
	int q, u, v;
	cin >> n >> q;
	bsn = sqrt(n);
	bsq = sqrt(q);
	for (int l = 1, c = 1; l <= n; l += bsn, c++)
	{
		int r = min(l + bsn - 1, n);
		lb[c] = l, rb[c] = r;
		for (int j = l; j <= r; j++) bel[j] = c;
	}
	for (int i = 1; i <= n; i++) cin >> x[i];
	for (int i = 1; i < n; i++)
	{
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	dfs1(1);
	dfs2(1, 1);
	for (int i = 1; i <= q; i++)
	{
		cin >> qs[i].s >> qs[i].t >> qs[i].a >> qs[i].b;
		qs[i].id = i;
		if (in[qs[i].s] > in[qs[i].t]) swap(qs[i].s, qs[i].t);
		int l = lca(qs[i].s, qs[i].t);
		if (l == qs[i].s) qs[i].type = false, qs[i].s = in[qs[i].s], qs[i].t = in[qs[i].t];
		else qs[i].type = true, qs[i].l = l, qs[i].s = out[qs[i].s], qs[i].t = in[qs[i].t];
	}
	sort(qs + 1, qs + q + 1);
	int l = 1, r = 0;
	for (int i = 1; i <= q; i++)
	{
		// cerr << qs[i].s << ' ' << qs[i].t << endl;
		while (l > qs[i].s) update_node(bfn[--l]);
		while (r < qs[i].t) update_node(bfn[++r]);
		while (l < qs[i].s) update_node(bfn[l++]);
		while (r > qs[i].t) update_node(bfn[r--]);
		// for (int j = 1; j <= n; j++) cerr << buc[j] << ' ';
		// cerr << endl;
		// for (int j = 1; j <= n; j++) cerr << cbuc[j] << ' ';
		// cerr << endl;
		if (qs[i].type) update_node(qs[i].l);
		ans[qs[i].id] = query(qs[i].a, qs[i].b);
		if (qs[i].type) update_node(qs[i].l);
	}
	for (int i = 1; i <= q; i++) cout << ans[i] << endl;
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