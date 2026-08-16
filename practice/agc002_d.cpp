// Problem: D - Stamp Rally
// Contest: AtCoder - AtCoder Grand Contest 002
// URL: https://atcoder.jp/contests/agc002/tasks/agc002_d
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

bool multi_test = false;

int n, m;
int fa[200001];
int fa_t[200001];
vector <int> adj[200001];
int dep[200001], kfa[19][200001], siz[200001];
pair <int, int> e[100001];
int val[100001];

int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

void dfs(int cur)
{
	if (cur <= n) siz[cur] = 1; // original points
	for (auto it : adj[cur])
	{
		if (it == fa_t[cur]) continue;
		fa_t[it] = cur;
		dep[it] = dep[cur] + 1;
		dfs(it);
		siz[cur] += siz[it];
	}
}

int check(int x, int y, int z, int d)
{
	for (int b = 18; b >= 0; b--) if (val[kfa[b][x] - n] <= d) x = kfa[b][x];
	for (int b = 18; b >= 0; b--) if (val[kfa[b][y] - n] <= d) y = kfa[b][y];
	// cerr << x << ' ' << y << ' ' << z << ' ' << d << endl;
	if (x == y) return siz[x] >= z;
	else return (siz[x] + siz[y]) >= z;
}

void solve()
{
	cin >> n >> m;
	for (int i = 1; i <= n + m; i++) 
	{
		fa[i] = i;
		fa_t[i] = dep[i] = siz[i] = 0;
		adj[i].clear();
		for (int b = 0; b <= 18; b++) kfa[b][i] = 0;
	}
	int cur = n;
	for (int i = 1; i <= m; i++)
	{
		cin >> e[i].first >> e[i].second;
		int fx = find(e[i].first), fy = find(e[i].second);
		if (fx == fy) continue;
		fa[fx] = ++cur;
		fa[fy] = cur;
		fa_t[fx] = cur;
		fa_t[fy] = cur;
		adj[cur].pb(fx);
		adj[cur].pb(fy);
		val[cur - n] = i;
	}
	fa_t[cur] = cur;
	dfs(cur);
	for (int i = 1; i <= n + m; i++) kfa[0][i] = fa_t[i];
	for (int b = 1; b <= 18; b++) for (int i = 1; i <= n + m; i++) kfa[b][i] = kfa[b - 1][kfa[b - 1][i]];
	int q, x, y, z;
	cin >> q;
	for (int i = 1; i <= q; i++)
	{
		cin >> x >> y >> z;
		int l = 1, r = m, ans = m;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			if (check(x, y, z, mid)) r = mid - 1, ans = mid;
			else l = mid + 1;
		}
		cout << ans << endl;
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