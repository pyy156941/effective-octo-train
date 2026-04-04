// Problem: E. Chain Queries
// Contest: Codeforces - Codeforces Round 947 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/1975/problem/E
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

bool c[200001];
int n, q;
int fa[200001], dep[200001];

struct cmp
{
	bool operator () (const int a, const int b) const
	{
		if (dep[a] == dep[b]) return a < b;
		return dep[a] < dep[b];
	}
};

multiset <int, cmp> des;
int buc[200001];
vector <int> adj[200001];

void DFS(int cur)
{
	for (auto it : adj[cur])
	{
		if (it == fa[cur]) continue;
		fa[it] = cur;
		dep[it] = dep[cur] + 1;
		DFS(it);
	}
}

void Solve()
{
	cin >> n >> q;
	des.clear();
	for (int i = 0; i <= n; i++)
	{
		buc[i] = 0;
		adj[i].clear();
		dep[i] = fa[i] = 0;
	}
	for (int i = 1; i <= n; i++) cin >> c[i];
	int u, v;
	for (int i = 1; i < n; i++)
	{
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	DFS(1);
	int bc = 0;
	for (int i = 1; i <= n; i++)
	{
		if (!c[i]) continue;
		des.insert(i);
		if (fa[i]) buc[fa[i]]++;
		bc++;
	}
	int f2c = 0, f1c = 0, f0c = 0, foc = 0, fc = 0;
	for (int i = 1; i <= n; i++)
	{
		if (!c[i]) continue;
		int sc = buc[i];
		fc += sc;
		if (sc == 2) f2c++;
		else if (sc == 1) f1c++;
		else if (!sc) f0c++;
		else foc++;
	}
	for (int i = 1; i <= q; i++)
	{
		cin >> u;
		if (c[u])
		{
			int sc = buc[u];
			if (sc == 2) f2c--;
			else if (sc == 1) f1c--;
			else if (!sc) f0c--;
			else foc--;
			fc -= sc;
			if (c[fa[u]]) fc--;
			des.erase(des.find(u));
			if (fa[u] && c[fa[u]])
			{
				sc = buc[fa[u]];
				if (sc == 2) f2c--;
				else if (sc == 1) f1c--;
				else if (!sc) f0c--;
				else foc--;
				buc[fa[u]]--;
				sc = buc[fa[u]];
				if (sc == 2) f2c++;
				else if (sc == 1) f1c++;
				else if (!sc) f0c++;
				else foc++;
			}
			else buc[fa[u]]--;
			c[u] = false;
			bc--;
		}
		else
		{
			int sc = buc[u];
//			cerr << u << ' ' << sc << endl;
			if (sc == 2) f2c++;
			else if (sc == 1) f1c++;
			else if (!sc) f0c++;
			else foc++;
			fc += sc;
			if (c[fa[u]]) fc++;
			des.insert(u);
			if (fa[u] && c[fa[u]])
			{
				sc = buc[fa[u]];
				if (sc == 2) f2c--;
				else if (sc == 1) f1c--;
				else if (!sc) f0c--;
				else foc--;
				buc[fa[u]]++;
				sc = buc[fa[u]];
				if (sc == 2) f2c++;
				else if (sc == 1) f1c++;
				else if (!sc) f0c++;
				else foc++;
			}
			else buc[fa[u]]++;
			c[u] = true;
			bc++;
		}
//		cerr << f2c << ' ' << f1c << ' ' << f0c << ' ' << foc << endl;
		if (!bc)
		{
			cout << "No\n";
			continue;
		}
		if (bc == 1)
		{
			cout << "Yes\n";
			continue;
		}
		if (foc || fc != bc - 1) 
		{
			cout << "No\n";
			continue;
		}
		int top = *des.begin();
		if (f1c == bc - 1 && f0c == 1 && buc[top] == 1 && !c[fa[top]]) 
		{
			cout << "Yes\n";
			continue;
		}
		if (f2c == 1 && f0c == 2 && f1c == bc - 3 && buc[top] == 2 && !c[fa[top]])
		{
			cout << "Yes\n";
			continue;
		}
		cout << "No\n";
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