// Problem: F. Odd Queries on Odd Array
// Contest: Codeforces - Codeforces Round 1057 (Div. 2)
// URL: https://codeforces.com/contest/2153/problem/F
// Memory Limit: 1024 MB
// Time Limit: 10000 ms
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

vector <int> adj[500001];
vector <ll> pre_ex[500001]; // prefix answer across subtrees of i, excluding value of i
vector <int> pre_s[500001]; // number of subtrees of i, counting only single values of i
int fa[500001], kfa[20][500001], dep[500001], siz[500001];
int val[500001];
ll pre[500001], suf[500002];
int buc[500001];
pair <int, int> range[500001];

void dfs1(int cur)
{
	siz[cur] = 1;
	for (auto it : adj[cur])
	{
		dep[it] = dep[cur] + 1;
		dfs1(it);
		siz[cur] += siz[it];
	}
}

void dfs2(int cur)
{
	ll accu_ex = 0;
	int accu_s = 0;
	for (auto it : adj[cur])
	{
		dfs2(it);
		ll cur_ex = 0;
		int cur_s = 0;
		if (val[it] == val[cur])
		{
			cur_ex = 0;
			cur_s = 1;
		}
		else
		{
			cur_ex = pre[it + siz[it] - 1] - pre[it - 1];
			cur_s = 0;
		}
		accu_ex += (ll)cur_ex;
		accu_s += cur_s;
		pre_ex[cur].pb(accu_ex);
		pre_s[cur].pb(accu_s);
	}
}

int lca(int x, int y)
{
	if (dep[x] > dep[y]) swap(x, y); // jump y to x's depth
	int dif = dep[y] - dep[x];
	for (int i = 19; i >= 0; i--) if (dif & (1 << i)) y = kfa[i][y];
	for (int i = 19; i >= 0; i--) if (kfa[i][x] != kfa[i][y]) x = kfa[i][x], y = kfa[i][y];
	if (x != y) x = y = fa[x];
	return x;
}

int jump_k(int x, int k)
{
	for (int i = 19; i >= 0; i--) if (k & (1 << i)) x = kfa[i][x];
	return x;
}

ll query(int l, int r)
{
	if (l == r) return val[l];
	int x = lca(l, r);
	int dl = dep[l] - dep[x], dr = dep[r] - dep[x];
	int mids = l, midt = r;
	ll res = 0;
	if (val[l] == val[x]) mids = lower_bound(adj[x].begin(), adj[x].end(), l) - adj[x].begin();
	else
	{
		int xsl = jump_k(l, dl - 1);
		res += suf[l] - suf[xsl + siz[xsl]];
		mids = lower_bound(adj[x].begin(), adj[x].end(), xsl) - adj[x].begin() + 1;
	}
	if (val[r] == val[x]) midt = lower_bound(adj[x].begin(), adj[x].end(), r) - adj[x].begin();
	else
	{
		int xsr = jump_k(r, dr - 1);
		res += pre[r] - pre[xsr - 1];
		midt = lower_bound(adj[x].begin(), adj[x].end(), xsr) - adj[x].begin() - 1;
	}
	// debug(res);
	// debug(mids);
	// debug(midt);
	int xvc = 0;
	if (l == x) xvc++; // extra val[x], special case when r is in the leftmost subtree of l
	if (midt >= mids) 
	{
		res += pre_ex[x][midt];
		if (mids) res -= pre_ex[x][mids - 1];
		xvc += (ll)pre_s[x][midt]; // count of val[x] in the trees between l and r
		if (mids) xvc -= (ll)pre_s[x][mids - 1];
	}
	if (xvc % 2) res += (ll)val[x];
	return res;
}

void solve()
{
	int n, q;
	cin >> n >> q;
	for (int i = 0; i <= n; i++) 
	{
		range[i].first = n + 1;
		range[i].second = 0;
		adj[i].clear();
		pre_ex[i].clear();
		pre_s[i].clear();
		fa[i] = dep[i] = siz[i] = 0;
		for (int b = 0; b <= 19; b++) kfa[b][i] = 0;
	}
	for (int i = 1; i <= n; i++) 
	{
		cin >> val[i];
		range[val[i]].first = min(range[val[i]].first, i);
		range[val[i]].second = max(range[val[i]].second, i);
	}
	for (int i = 1; i <= n; i++) buc[i] = 0;
	pre[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		buc[val[i]]++;
		if (buc[val[i]] % 2) pre[i] = pre[i - 1] + (ll)val[i];
		else pre[i] = pre[i - 1] - (ll)val[i];
	}
	for (int i = 1; i <= n; i++) buc[i] = 0;
	suf[n + 1] = 0; // clear this
	for (int i = n; i >= 1; i--) 
	{
		buc[val[i]]++;
		if (buc[val[i]] % 2) suf[i] = suf[i + 1] + (ll)val[i];
		else suf[i] = suf[i + 1] - (ll)val[i];
	}
	stack <int> st;
	st.push(0);
	for (int i = 1; i <= n; i++)
	{
		if (!st.empty()) 
		{
			adj[st.top()].pb(i);
			fa[i] = st.top();
		}
		if (range[val[i]].first == i) st.push(i);
		if (range[val[i]].second == i) st.pop();
	}
	for (int i = 0; i <= n; i++) kfa[0][i] = fa[i];
	for (int b = 1; b <= 19; b++) for (int i = 0; i <= n; i++) kfa[b][i] = kfa[b - 1][kfa[b - 1][i]]; 
	dfs1(0);
	dfs2(0);
	int l, r;
	ll lans = 0;
	for (int i = 1; i <= q; i++)
	{
		cin >> l >> r;
		int tl = (l - 1 + lans) % n + 1;
		int tr = (r - 1 + lans) % n + 1;
		l = min(tl, tr), r = max(tl, tr);
		// cerr << l << ' ' << r << endl;
		lans = query(l, r);
		cout << lans << ' ';
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