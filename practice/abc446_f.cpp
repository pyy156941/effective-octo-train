// Problem: F - Reachable Set 2
// Contest: AtCoder - AtCoder Beginner Contest 446
// URL: https://atcoder.jp/contests/abc446/tasks/abc446_f
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

bool multi_test = false;

vector <int> adj[300001];
int fa[300001], maxfa[300001], far[300001];
bool vis[300001];

void bfs(int s)
{
	queue <int> Q;
	vis[s] = 1;
	Q.push(s);
	while (!Q.empty())
	{
		int cur = Q.front();
		Q.pop();
		for (auto it : adj[cur])
		{
			fa[it] = min(fa[it], cur);
			if (!vis[it]) vis[it] = true, Q.push(it);
		}
	}
}

struct bit
{
	int n;
	int sum[300001];
	
	void update(int p, int x)
	{
		while (p <= n) 
		{
			sum[p] += x;
			p += lowbit(p);
		}
	}
	
	int query(int p)
	{
		int res = 0;
		while (p)
		{
			res += sum[p];
			p -= lowbit(p);
		}
		return res;
	}
}t;

void solve()
{
	int n, m;
	cin >> n >> m;
	int u, v;
	for (int i = 1; i <= m; i++) 
	{
		cin >> u >> v;
		adj[u].pb(v);
	}
	for (int i = 1; i <= n; i++) sort(adj[i].begin(), adj[i].end());
	fa[1] = 1;
	for (int i = 2; i <= n; i++) fa[i] = n + 1;
	bfs(1);
	t.n = n;
	for (int i = 1; i <= n; i++) far[i] = i;
	sort(far + 1, far + n + 1, [] (int a, int b) { return fa[a] < fa[b]; });
	int p = 0;
	int lst = 1, mn = n + 1, mx = 0;
	for (int i = 1; i <= n; i++) 
	{
		mn = min(mn, fa[i]);
		mx = max(mx, fa[i]);
		cerr << i << ' ' << mn << ' ' << mx << ' ' << lst << endl;
		if (i > 1 && (mn > lst || mx > i))
		{
			cout << -1 << endl;
			continue;
		}
		lst = i;
		mn = n + 1;
		mx = 0;
		while (p < n && fa[far[p + 1]] <= i) 
		{
			p++;
			t.update(far[p], 1);
		}
		cout << t.query(n) - t.query(i) << endl;
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