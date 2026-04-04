// Problem: D2. Tree Orientation (Hard Version)
// Contest: Codeforces - Codeforces Round 1086 (Div. 2)
// URL: https://codeforces.com/contest/2208/problem/D2
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

int fa[8001];

void clear(int n)
{
	for (int i = 1; i <= n; i++) fa[i] = i;
}

int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

bool merge(int x, int y)
{
	int fx = find(x), fy = find(y);
	if (fx == fy) return false;
	fa[fy] = fx;
	return true;
}

bool b[8001][8001];
int degin[8001];
int order[8001];
bool vis[8001];
vector <pair <int, int>> ans;
vector <int> adj[8001], adj2[8001];

void dfs(int cur)
{
	vis[cur] = true;
	for (auto it : adj2[cur]) dfs(it);
}

bool verify(int n)
{
	if (ans.size() != n - 1) return false;
	for (auto [u, v] : ans)
	{
		bool ok = merge(u, v);
		adj2[u].pb(v);
		if (!ok) return false;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++) vis[j] = false;
		dfs(i);
		for (int j = 1; j <= n; j++) if (b[i][j] != vis[j]) return false;
	}
	return true;
}

void solve()
{
	int n;
	cin >> n;
	clear(n);
	ans.clear();
	for (int i = 1; i <= n; i++) degin[i] = 0, vis[i] = false, order[i] = i, adj[i].clear(), adj2[i].clear();
	string str;
	for (int i = 1; i <= n; i++)
	{
		cin >> str;
		for (int j = 1; j <= n; j++)
		{
			if (str[j - 1] == '0') b[i][j] = false;
			else b[i][j] = true, degin[j]++, adj[i].pb(j);
		}
		degin[i]--;
	}
	for (int i = 1; i <= n; i++)
	{
		if (!b[i][i]) 
		{
			cout << "No\n";
			return;
		}
		for (int j = i + 1; j <= n; j++)
		{
			if (b[i][j] && b[j][i])
			{
				cout << "No\n";
				return;
			}
		}
	}
	auto cmp = [] (const int u, const int v) { return degin[u] < degin[v]; };
	sort(order + 1, order + n + 1, cmp);
	for (int i = 1; i <= n; i++) sort(adj[i].begin(), adj[i].end(), cmp);
	for (int i = 1; i <= n; i++)
	{
		int cur = order[i];
		for (int j = 1; j <= n; j++) vis[j] = false;
		for (auto it : adj[cur])
		{
			if (vis[it] || it == cur) continue;
			vis[it] = true;
			ans.pb({cur, it});
			for (auto it2 : adj[it]) vis[it2] = true;
		}
	}
	bool ok = verify(n);
	if (!ok)
	{
		cout << "No\n";
		return;
	}
	cout << "Yes\n";
	for (auto [u, v] : ans) multi_write_endl(u, v);
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