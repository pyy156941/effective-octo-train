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

int n, q;
int siz[300001], dfn[300001], dfc = 0, fa[300001];
vector <int> adj[300001];
int p[300001];
bool nok[300001];

void DFS(int cur)
{
	siz[cur] = 1;
	dfn[cur] = ++dfc;
	for (auto it : adj[cur])
	{
		if (it == fa[cur]) continue;
		DFS(it);
		siz[cur] += siz[it];
	}
}

bool ChkAncestry(int a, int b)
{
	return (dfn[b] >= dfn[a] && dfn[b] < dfn[a] + siz[a]);
}

void Solve()
{
	dfc = 0;
	int x, y;
	cin >> n >> q;
	for (int i = 1; i <= n; i++) siz[i] = fa[i] = dfn[i] = 0, adj[i].clear(), nok[i] = false;
	for (int i = 2; i <= n; i++)
	{
		cin >> fa[i];
		adj[i].push_back(fa[i]);
		adj[fa[i]].push_back(i);
	}
	DFS(1);
	for (int i = 1; i <= n; i++) cin >> p[i];
	int nc = 0;
	for (int i = 1; i < n; i++) 
	{
		if (!ChkAncestry(fa[p[i + 1]], p[i])) nc++, nok[i] = true;
	}
	for (int i = 1; i <= q; i++)
	{
		cin >> x >> y;
		if (x > 1) 
		{
			if (nok[x - 1]) nc--, nok[x - 1] = false;
		}
		if (y > 1)
		{
			if (nok[y - 1]) nc--, nok[y - 1] = false;
		}
		if (x < n)
		{
			if (nok[x]) nc--, nok[x] = false;
		}
		if (y < n)
		{
			if (nok[y]) nc--, nok[y] = false;
		}
		swap(p[x], p[y]);
		if (x > 1)
		{
			if (!ChkAncestry(fa[p[x]], p[x - 1]))
			{
				if (!nok[x - 1]) nok[x - 1] = true, nc++; 
			}
		}
		if (y > 1)
		{
			if (!ChkAncestry(fa[p[y]], p[y - 1]))
			{
				if (!nok[y - 1]) nok[y - 1] = true, nc++; 
			}
		}
		if (x < n)
		{
			if (!ChkAncestry(fa[p[x + 1]], p[x]))
			{
				if (!nok[x]) nok[x] = true, nc++; 
			}
		}
		if (y < n)
		{
			if (!ChkAncestry(fa[p[y + 1]], p[y]))
			{
				if (!nok[y]) nok[y] = true, nc++; 
			}
		}
//		cerr << nc << endl;
//		for (int j = 1; j <= n; j++) cerr << p[j] << ' ';
//		cerr << endl;
//		for (int j = 1; j <= n; j++) cerr << nok[j] << ' ';
//		cerr << endl;
		if (nc) cout << "NO\n";
		else cout << "YES\n";
	}
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