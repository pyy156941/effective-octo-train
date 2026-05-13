// Problem: F. MEX Replacement on Tree
// Contest: Codeforces - Codeforces Round 1093 (Div. 2)
// URL: https://codeforces.com/contest/2220/problem/F
// Memory Limit: 256 MB
// Time Limit: 3500 ms
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

struct bit
{
	int n;
	ll tree[200001];
	
	void clear(int _n)
	{
		n = _n;
		for (int i = 0; i <= n; i++) tree[i] = 0;
	}
	
	void update(int p, ll x)
	{
		while (p <= n)
		{
			tree[p] += x;
			p += lowbit(p);
		}
	}
	
	ll query(int p) // int -> ll WA #7
	{
		ll sum = 0;
		while (p)
		{
			sum += tree[p];
			p -= lowbit(p);
		}
		return sum;
	}
	
	ll query(int l, int r)
	{
		return query(r) - query(l - 1);
	}
}ms, mc, ms2, mc2;

int p[200001], pl[200001];
int fa[200001], dfn[200001], dfc = 0, rnk[200001], siz[200001];
int mex[200001], mex2[200001];
ll res[200001];
vector <int> adj[200001];

set <int> mis; // missing numbers
void dfs1(int cur)
{
	siz[cur] = 1;
	dfn[cur] = ++dfc;
	rnk[dfc] = cur;
	mis.erase(mis.find(p[cur]));
	mex[cur] = *mis.begin();
	mex2[cur] = *++mis.begin();
	for (auto it : adj[cur])
	{
		if (it == fa[cur]) continue;
		fa[it] = cur;
		dfs1(it);
		siz[cur] += siz[it];
	}
	mis.insert(p[cur]);
}

bool inst(int u, int v)
{
	return (dfn[u] <= dfn[v] && dfn[v] < dfn[u] + siz[u]);
}

vector <int> mv[200001], mv2[200002];
void solve()
{
	int n;
	cin >> n;
	mis.clear();
	for (int i = 0; i <= n; i++)
	{
		mv[i].clear(), mv2[i].clear(), adj[i].clear();
		fa[i] = dfn[i] = rnk[i] = siz[i] = 0;
		dfc = 0;
		mis.insert(i);
	}
	mv2[n + 1].clear(); // need to add this WA #2
	mis.insert(n + 1), mis.insert(n + 2);
	ms.clear(n), mc.clear(n), ms2.clear(n), mc2.clear(n);
	for (int i = 1; i <= n; i++) cin >> p[i], pl[p[i]] = i;
	int u, v;
	for (int i = 1; i < n; i++)
	{
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	dfs1(1);
	ll ans = 0;
	for (int i = 1; i <= n; i++) mv[mex[i]].pb(i), mv2[mex2[i]].pb(i), ans += (ll)mex[i];
	for (int i = 1; i <= n; i++)
	{
		ms2.update(dfn[i], mex2[i]);
		// cerr << mex[i] << ' ' << mex2[i] << endl;
	}
	for (auto it : mv[n])
	{
		mc.update(dfn[it], 1);
		ms.update(dfn[it], n);
	}
	for (auto it : mv2[n])
	{
		mc2.update(dfn[it], 1);
		ms2.update(dfn[it], -n);
	}
	for (auto it : mv2[n + 1]) 
	{
		mc2.update(dfn[it], 1);
		ms2.update(dfn[it], -(n + 1));
	}
	for (int i = n - 1; i >= 0; i--) 
	{
		int cur = pl[i];
		if (p[cur] > mex[cur])
		{
			int l = dfn[cur], r = dfn[cur] + siz[cur] - 1;
			// cerr << cur << ' ' << l << ' ' << r << endl;
			if (inst(cur, pl[mex[cur]]))
			{
				int sl = pl[mex[cur]]; // root of subtree where mex is larger
				int li = dfn[sl], ri = dfn[sl] + siz[sl] - 1;
				res[cur] = mc.query(li, ri) * (ll)i - ms.query(li, ri) + ans;
				if (li > l) res[cur] += mc2.query(l, li - 1) * (ll)i + ms2.query(l, li - 1) - (ll)mex[cur] * (li - l);
				if (ri < r) res[cur] += mc2.query(ri + 1, r) * (ll)i + ms2.query(ri + 1, r) - (ll)mex[cur] * (r - ri);
			}
			else res[cur] = mc2.query(l, r) * (ll)i + ms2.query(l, r) + ans - (ll)mex[cur] * (r - l + 1);
		}
		else res[cur] = -1e14;
		for (auto it : mv[i]) 
		{
			mc.update(dfn[it], 1);
			ms.update(dfn[it], i);
		}
		for (auto it : mv2[i])
		{
			mc2.update(dfn[it], 1);
			ms2.update(dfn[it], -i);
		}
	}
	for (int i = 1; i <= n; i++) ans = max(ans, res[i]);
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