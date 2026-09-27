// Problem: E - Wheel Distance
// Contest: AtCoder - UNICORNProgramming Contest2026(AtCoder Beginner Contest 477)
// URL: https://atcoder.jp/contests/abc477/tasks/abc477_e
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

struct nodeb
{
	int id;
	ll dis;
	nodeb(int _id, ll _dis) : id(_id), dis(_dis) {}

	bool operator < (const nodeb o) const
	{
		return dis > o.dis;
	}
};

int n;
vector <pair <int, int>> adj[200002];
ll dis[200002];
bool vis[200002];

void dij(int s)
{
	for (int i = 1; i <= n + 1; i++) dis[i] = 2e16, vis[i] = false;
	priority_queue <nodeb> Q;
	dis[s] = 0;
	Q.push(nodeb(s, dis[s]));
	while (!Q.empty())
	{
		auto [cn, _] = Q.top();
		Q.pop();
		if (vis[cn]) continue;
		vis[cn] = true;
		for (auto [to, w] : adj[cn])
		{
			if (dis[cn] + w < dis[to])
			{
				dis[to] = dis[cn] + w;
				Q.push(nodeb(to, dis[to]));
			}
		}
	}
}

int a[200001], b[200001];
ll pre[200001];
void solve()
{
	int q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		adj[i].pb({i % n + 1, a[i]});
		adj[i % n + 1].pb({i, a[i]});
		pre[i] = pre[i - 1] + (ll)a[i];
	}
	for (int i = 1; i <= n; i++) 
	{
		cin >> b[i];
		adj[i].pb({n + 1, b[i]});
		adj[n + 1].pb({i, b[i]});
	}
	dij(n + 1);
	int s, t;
	for (int i = 1; i <= q; i++)
	{
		cin >> s >> t;
		if (t == n + 1)
		{
			cout << dis[s] << endl;
			continue;
		}
		ll ans1 = pre[t - 1] - pre[s - 1];
		ll ans2 = pre[s - 1] + pre[n] - pre[t - 1];
		ll ans3 = dis[s] + dis[t];
		cout << min(min(ans1, ans2), ans3) << endl;
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