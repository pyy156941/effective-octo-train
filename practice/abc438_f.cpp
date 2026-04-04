// Problem: F - Sum of Mex
// Contest: AtCoder - AtCoder Beginner Contest 438
// URL: https://atcoder.jp/contests/abc438/tasks/abc438_f
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
#define debug(x) cerr << #x << " : " << x << endl;
#define isdigit(x) (x >= '0' && x <= '9')
#define least2p(x) ((x == 1) ? 0 : __lg(x) + ((x & (x - 1)) != 0))s

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
void fastgcd(T a, T b) // unsigned only
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
	auto za = countr_zero(a);
	auto zb = countr_zero(b);
	a >>= za;
	b >>= zb;
	do 
	{
		T dif = a - b;
		if (a > b) a = b, b = dif;
		else b = b - a;
		b >>= countr_zero(dif);
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

bool multiTest = false;

vector <int> adj[200001];
int siz[200001], hson[200001], dep[200001], fa[200001], top[200001];

void DFS1(int cur)
{
	siz[cur] = 1;
	hson[cur] = 0;
	for (auto it : adj[cur])
	{
		if (it == fa[cur]) continue;
		dep[it] = dep[cur] + 1;
		fa[it] = cur;
		DFS1(it);
		siz[cur] += siz[it];
		if (!hson[cur] || siz[it] > siz[hson[cur]]) hson[cur] = it;
	}
}

void DFS2(int cur, int head)
{
	top[cur] = head;
	if (!hson[cur]) return;
	DFS2(hson[cur], head);
	for (auto it : adj[cur])
	{
		if (it == fa[cur] || it == hson[cur]) continue;
		DFS2(it, it);
	}
}

int lca(int x, int y)
{
	while (top[x] != top[y])
	{
		if (dep[top[x]] < dep[top[y]]) y = fa[top[y]];
		else x = fa[top[x]];
	}
	return dep[x] < dep[y] ? x : y;
}

void Solve()
{
	int n;
	cin >> n;
	for (int i = 1; i < n; i++) 
	{
		int u, v;
		multiRead(u, v);
		adj[u + 1].pb(v + 1);
		adj[v + 1].pb(u + 1);	
	}
	DFS1(1);
	DFS2(1, 1);
	int head = 1, tail = 2; 
	ll ans = (ll)n * (n + 1) / 2;
	int otherpart = 1;
	int subtree_of_2 = 0;
	for (int i = 2; i <= n; i++) 
	{
		if (fa[i] == 1) 
		{
			ans -= (ll)siz[i] * (siz[i] + 1) / 2;
			if (lca(2, i) != i) otherpart += siz[i]; 
			else subtree_of_2 = i;
		}
	}
	ans += (ll)siz[2] * otherpart;
	// cerr << ans << endl;
	for (int i = 3; i <= n; i++)
	{
		int lca_head = lca(i, head);
		int lca_tail = lca(i, tail);
		int lca_2 = lca(i, subtree_of_2);
		if (head == 1)
		{
			if (lca_tail == tail) tail = i, ans += (ll)siz[tail] * otherpart;
			else if (lca_tail == i) ans += (ll)siz[tail] * otherpart;
			else if (lca_2 != 1) break;
			else head = i, ans += (ll)siz[tail] * siz[head];
		}
		else
		{
			if (lca_tail == tail) tail = i;
			else if (lca_tail == i);
			else if (lca_head == head) head = i;
			else if (lca_head == i); 
			else break;
			ans += (ll)siz[tail] * siz[head];
		}
		// cerr << i << ' ' << ans << endl;
	}
	cout << ans << endl;
	return;
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