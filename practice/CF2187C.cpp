// Problem: C. Jerry and Tom
// Contest: Codeforces - Codeforces Round 1077 (Div. 1)
// URL: https://codeforces.com/contest/2187/problem/C
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

int n, m;
vector <int> adj[200001];
int fa[200001], hson[200001], dfn[200001], rnk[200001], siz[200001], dep[200001], top[200001], dfc = 0;

void dfs1(int cur)
{
	dfn[++dfc] = cur;
	rnk[cur] = dfc;
	siz[cur] = 1;
	for (auto it : adj[cur])
	{
		if (it == fa[cur]) continue;
		fa[it] = cur;
		dep[it] = dep[cur] + 1;
		dfs1(it);
		siz[cur] += siz[it];
		if (!hson[cur] || siz[it] > siz[hson[cur]]) hson[cur] = it;
	}
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

struct fenwick_tree
{
	ll tree[200001];
	
	void clear()
	{
		for (int i = 1; i <= n; i++) tree[i] = 0;
	}
	
	void update(int p, ll x)
	{
		while (p <= n) 
		{
			tree[p] += x;
			p += lowbit(p);
		}
	}
	
	ll query(int p)
	{
		ll res = 0;
		while (p)
		{
			res += tree[p];
			p -= lowbit(p);
		}
		return res;
	}
}t1, t2;

ll dfs3(int cur, bool keep)
{
	ll ans = 0;
	for (auto it : adj[cur])
	{
		if (it == fa[cur] || it == hson[cur]) continue;
		ans += dfs3(it, false);
	}
	if (hson[cur]) ans += dfs3(hson[cur], true);
	for (auto it : adj[cur])
	{
		if (it == fa[cur] || it == hson[cur]) continue;
		for (int i = rnk[it]; i < rnk[it] + siz[it]; i++)
		{
			int d = dep[dfn[i]];
			ans += (t1.query(n) - t1.query(d - 1)) * (ll)(d - dep[cur]);
			ans += t2.query(d) - t1.query(d) * (ll)dep[cur]; // if dep is the same, we have to count twice (swap pair)
		}
		for (int i = rnk[it]; i < rnk[it] + siz[it]; i++)
		{
			t1.update(dep[dfn[i]], 1);
			t2.update(dep[dfn[i]], (ll)dep[dfn[i]]);
		}
	}
	t1.update(dep[cur], 1);
	t2.update(dep[cur], (ll)dep[cur]);
	// cerr << cur << ' ' << ans << endl;
	if (!keep) 
	{
		for (int i = rnk[cur]; i < rnk[cur] + siz[cur]; i++) 
		{
			t1.update(dep[dfn[i]], -1);
			t2.update(dep[dfn[i]], (ll)-dep[dfn[i]]);
		}
	}
	return ans;
}

int mxr[200001];

void solve()
{
	int u, v;
	multi_read(n, m);
	t1.clear(), t2.clear();
	for (int i = 1; i <= n; i++)
	{
		fa[i] = hson[i] = dfn[i] = rnk[i] = siz[i] = dep[i] = top[i] = dfc = 0;
		adj[i].clear();
		mxr[i] = i + 1;
	}
	for (int i = 1; i <= m; i++)
	{
		multi_read(u, v);
		mxr[u] = max(mxr[u], v);
	}
	for (int i = 1; i < n; i++)
	{
		adj[i].pb(mxr[i]);
		adj[mxr[i]].pb(i);
	}
	dep[n] = 1;
	dfs1(n);
	dfs2(n, n);
	ll ans = dfs3(n, false);
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