// Problem: D. Paint the Tree
// Contest: Codeforces - Codeforces Round 947 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/1975/problem/D
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

vector <int> adj[200001];
int fa[200001];
vector <int> bta;

void DFS1(int cur, vector <int> &dep)
{
	for (auto it : adj[cur])
	{
		if (it == fa[cur]) continue;
		fa[it] = cur;
		dep[it] = dep[cur] + 1;
		DFS1(it, dep);
	}
}

void Solve()
{
	int n;
	cin >> n;
	int a, b, u, v;
	cin >> a >> b;
	bta.clear();
	for (int i = 1; i <= n; i++)
	{
		adj[i].clear();
		fa[i] = 0;
	}
	for (int i = 1; i < n; i++)
	{
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	vector <int> depa(n + 1);
	DFS1(a, depa);
	for (int cur = b; cur != a; cur = fa[cur]) bta.pb(cur);
	bta.pb(a);
	int m1 = 0;
	for (int i = 1; i <= n; i++)
	{
		if (depa[i] > depa[m1]) m1 = i;
		fa[i] = 0;
	}
	vector <int> dep1(n + 1), dep2(n + 1);
	DFS1(m1, dep1);
	int m2 = 0;
	for (int i = 1; i <= n; i++)
	{
		if (dep1[i] > dep1[m2]) m2 = i;
		fa[i] = 0;
	}
//	cerr << endl;
	DFS1(m2, dep2);
	reverse(bta.begin(), bta.end());
//	cerr << m1 << ' ' << m2 << endl;
	int ans = 10000000;
	for (int s = 0; s <= (bta.size() - 1) / 2; s++) 
	{
//		cerr << bta[s] << endl;
		ans = min(ans, 2 * (n - 1) + max(s, depa[b] - s) - max(dep1[bta[s]], dep2[bta[s]]));
	}
	cerr << endl;
	cout << ans << '\n';
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