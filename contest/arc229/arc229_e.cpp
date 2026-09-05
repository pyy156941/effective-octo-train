// Problem: E - Taka and Hashi
// Contest: AtCoder - AtCoder Regular Contest-- 229
// URL: https://atcoder.jp/contests/arc229/tasks/arc229_e
// Memory Limit: 1024 MB
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

vector <int> adj[200001][3];
vector <int> sl[200001][3];

struct dsu
{
	int n;
	int fa[200001];
	
	void clear(int _n)
	{
		n = _n;
		for (int i = 1; i <= n; i++) fa[i] = i;
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
		fa[fx] = fy;
	}
}s[3];

map <pair <int, int>, bool> vis23;
bool vis1[200001];

vector <int> intersect(int f2, int f3)
{
	if (vis23.find({f2, f3}) != vis23.end()) return {};
	vector <int> res;
	for (int i = 0; i < sl[f3][2].size(); i++)
	{
		int cur = sl[f3][2][i];
		auto it = lower_bound(sl[f2][1].begin(), sl[f2][1].end(), cur);
		if (it != sl[f2][1].end() && (*it) == cur) res.pb(cur);
	}
	vis23[{f2, f3}] = true;
	return res; 
}

void solve()
{
	int n, m;
	cin >> n >> m;
	vis23.clear();
	for (int i = 1; i <= n; i++) vis1[i] = false, adj[i][0].clear(), adj[i][1].clear(), adj[i][2].clear(), sl[i][0].clear(), sl[i][1].clear(), sl[i][2].clear();
	s[0].clear(n);
	s[1].clear(n);
	s[2].clear(n);
	int u, v, l;
	for (int i = 1; i <= m; i++)
	{
		cin >> u >> v >> l;
		adj[u][l - 1].pb(v);
		adj[v][l - 1].pb(u);
		s[l - 1].merge(u, v);
	}
	for (int i = 1; i <= n; i++) for (int j = 0; j < 3; j++) s[j].fa[i] = s[j].find(i);
	for (int i = 1; i <= n; i++) for (int j = 0; j < 3; j++) sl[s[j].fa[i]][j].pb(i);
	for (int i = 1; i <= n; i++) for (int j = 0; j < 3; j++) if (sl[i][j].size()) sort(sl[i][j].begin(), sl[i][j].end());
	vector <int> n1 = sl[s[0].fa[1]][0];
	vector <int> n23 = intersect(s[1].fa[1], s[2].fa[1]);
	vector <int> ans;
	for (auto x : n1) vis1[s[0].fa[x]] = true, ans.pb(x);
	for (auto x : n23) vis23[{s[1].fa[x], s[2].fa[x]}] = true, ans.pb(x);
	for (int _ = 1; _ < n; _++)
	{
		if (!n1.size() && !n23.size()) break;
		vector <int> nn23;
		for (auto x : n1)
		{
			vector <int> tmp = intersect(s[1].fa[x], s[2].fa[x]);
			for (auto e : tmp) nn23.pb(e);
		}
		vector <int> nn1, np1;
		for (auto x : n23) if (!vis1[s[0].fa[x]]) np1.pb(s[0].fa[x]), vis1[s[0].fa[x]] = true;
		for (auto p : np1) for (auto x : sl[p][0]) nn1.pb(x);
		n23 = move(nn23);
		n1 = move(nn1);
		for (auto x : n1) ans.pb(x);
		for (auto x : n23) ans.pb(x);
	}
	sort(ans.begin(), ans.end());
	ans.erase(unique(ans.begin(), ans.end()), ans.end());
	cout << ans.size() << endl;
	for (auto x : ans) cout << x << ' '; 
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