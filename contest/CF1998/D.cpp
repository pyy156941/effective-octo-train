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
#define debug(x) cerr << #x << " : " << x << endl;
#define isdigit(x) (x >= '0' && x <= '9')

#define yn(x) pc(x ? 'Y' : 'N'), pc(x ? 'e' : 'o'), x ? (pc('s'), pc('\n')) : pc('\n')
#define ync(x) pc(x ? 'Y' : 'N'), pc(x ? 'E' : 'O'), x ? (pc('S'), pc('\n')) : pc('\n')
#define ynl(x) pc(x ? 'y' : 'n'), pc(x ? 'e' : 'o'), x ? (pc('s'), pc('\n')) : pc('\n')

template <typename ... Args>
void multiRead(Args& ... args)
{
    ((cin >> args), ...);
}

template <typename ... Args>
void multiWrite(Args ... args)
{
    ((cout << args << " "), ...);
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
T Inv(T a, T p)
{
	T x, y;
	exgcd(a, p, x, y);
	return (x + p) % p;
}

template <typename T>
T QPow(T a, T b, T mod)
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

bool multiTest = true;

int n, m;
int dis[200001];
vector <int> fr[200001];
pair <int, int> e[200001];

int tree[800001], lt[800001];
void Pushup(int cur)
{
	tree[cur] = tree[ls(cur)] + tree[rs(cur)];
}

void Pushdown(int cur, int s, int t)
{
	if (lt[cur] == -1) return;
	int mid = (s + t) >> 1;
	tree[ls(cur)] = lt[cur] * (mid - s + 1);
	tree[rs(cur)] = lt[cur] * (t - mid);
	lt[ls(cur)] = lt[rs(cur)] = lt[cur];
	lt[cur] = -1;
}

void Build(int cur, int l, int r)
{
	lt[cur] = -1;
	if (l == r)
	{
		tree[cur] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	Build(ls(cur), l, mid);
	Build(rs(cur), mid + 1, r);
	Pushup(cur);
}

void Set(int cur, int l, int r, int s, int t)
{
	if (l <= s && t <= r)
	{
		tree[cur] = 0;
		lt[cur] = 0;
		return;
	}
	int mid = (s + t) >> 1;
	Pushdown(cur, s, t);
	if (l <= mid) Set(ls(cur), l, r, s, mid);
	if (r > mid) Set(rs(cur), l, r, mid + 1, t);
	Pushup(cur);
}

int Query(int cur, int p, int s, int t)
{
	if (s == t) return tree[cur];
	int mid = (s + t) >> 1;
	Pushdown(cur, s, t);
	if (p <= mid) return Query(ls(cur), p, s, mid);
	else return Query(rs(cur), p, mid + 1, t);
}

void Solve()
{
	int u, v;
	cin >> n >> m;
	dis[1] = 0;
	for (int i = 1; i <= n; i++) fr[i].clear();
	for (int i = 1; i <= m; i++)
	{
		cin >> u >> v;
		fr[v].pb(u);
		e[i] = {u, v};
	}
	for (int i = 2; i <= n; i++)
	{
		dis[i] = dis[i - 1] + 1;
		for (auto it : fr[i]) dis[i] = min(dis[i], dis[it] + 1);
	}
	Build(1, 1, n);
	for (int i = 1; i <= m; i++)
	{
		int st = e[i].first, en = e[i].second;
		if (en - dis[st] - 2 >= st + 1) Set(1, st + 1, en - dis[st] - 2, 1, n);
	}
	for (int i = 1; i < n; i++) cout << Query(1, i, 1, n);
	cout << '\n';
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr);
	int _ = 1;
	if (multiTest) cin >> _;
	while (_--) Solve();
	return 0;
}