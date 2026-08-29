// Problem: E. Bricks
// Contest: Codeforces - Codeforces Round 668 (Div. 1)
// URL: https://codeforces.com/contest/1404/problem/E
// Memory Limit: 256 MB
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

bool multi_test = false;

int N;
struct Edge
{
	int v, nxt;
	ll cap, flow;
}e[1600002];

int ecnt = 1;
int dep[80001];
int head[80001], cHead[80001];

void addedge(int u, int v, int w)
{
	// cerr << u << ' ' << v << ' ' << w << endl;
	e[++ecnt] = {v, head[u], w, 0};
	head[u] = ecnt;
	e[++ecnt] = {u, head[v], 0, 0};
	head[v] = ecnt;
}

bool bfs(int s, int t)
{
	queue <int> Q;
	for (int i = 1; i <= N; i++) dep[i] = 0;
	dep[s] = 1;
	Q.push(s);
	while (!Q.empty())
	{
		int cur = Q.front();
		Q.pop();
		for (int it = head[cur]; it; it = e[it].nxt)
		{
			int v = e[it].v;
			if (!dep[v] && e[it].cap > e[it].flow)
			{
				dep[v] = dep[cur] + 1;
				Q.push(v);
			}
		}
	}
	return dep[t];
}

ll dfs(int cur, int t, long long flow)
{
	if (cur == t || !flow) return flow;
	ll ret = 0;
	for (int it = cHead[cur]; it; it = e[it].nxt)
	{
		cHead[cur] = it; // opt
		int v = e[it].v;
		ll c;
		if (dep[v] == dep[cur] + 1 && (c = dfs(v, t, min(flow - ret, e[it].cap - e[it].flow))))
		{
			ret += c;
			e[it].flow += c;
			e[it ^ 1].flow -= c;
		}
	}
	return ret;
}

ll flow(int s, int t)
{
	ll maxflow = 0;
	while (bfs(s, t))
	{
		for (int i = 1; i <= N; i++) cHead[i] = head[i];
		maxflow += dfs(s, t, 1e10);
	}
	return maxflow;
}

int n, m;
bool grid[201][201];
int idc = 0, ids_h[201][201], ids_v[201][201];
void solve()
{
	cin >> n >> m;
	string str;
	int bc = 0;
	for (int i = 1; i <= n; i++)
	{
		cin >> str;
		for (int j = 1; j <= m; j++) grid[i][j] = (str[j - 1] == '#' ? true : false), ids_h[i][j] = ids_v[i][j] = 0, bc += grid[i][j];
	}
	idc = 0;
	for (int i = 1; i <= n; i++) 
	{
		for (int j = 1; j < m; j++) 
		{
			if (grid[i][j] && grid[i][j + 1]) ids_h[i][j] = ++idc;
			else ids_h[i][j] = 0;
		}
	}
	for (int i = 1; i < n; i++) 
	{
		for (int j = 1; j <= m; j++) 
		{
			if (grid[i][j] && grid[i + 1][j]) ids_v[i][j] = ++idc;
			else ids_v[i][j] = 0;
		}
	}
	N = idc + 2;
	for (int i = 1; i <= n; i++) 
	{
		for (int j = 1; j < m; j++)
		{
			if (ids_h[i][j]) 
			{
				if (ids_v[i][j + 1]) addedge(ids_h[i][j], ids_v[i][j + 1], 1e8);
				if (ids_v[i][j]) addedge(ids_h[i][j], ids_v[i][j], 1e8);
				if (i > 1 && ids_v[i - 1][j + 1]) addedge(ids_h[i][j], ids_v[i - 1][j + 1], 1e8);
				if (i > 1 && ids_v[i - 1][j]) addedge(ids_h[i][j], ids_v[i - 1][j], 1e8); 
			}
		}
	}
	int S = N - 1, T = N;
	for (int i = 1; i <= n; i++) for (int j = 1; j < m; j++) if (ids_h[i][j]) addedge(S, ids_h[i][j], 1);
	for (int i = 1; i < n; i++) for (int j = 1; j <= m; j++) if (ids_v[i][j]) addedge(ids_v[i][j], T, 1);
	int ans = flow(S, T);
	cout << bc - (idc - ans) << endl; // idc - ans is the max independent set
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