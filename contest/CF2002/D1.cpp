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

int fa[300001], siz[300001];
vector <int> adj[300001];
set <int> S[300001];
int p[300001], pl[300001];
bool ok[300001];
int nkc = 0;
set <int> rek;

void DFS(int cur)
{
	siz[cur] = 1;
	for (auto it : adj[cur])
	{
		if (it == fa[cur]) continue;
		DFS(it);
		siz[cur] += siz[it];
	}
}

void Add(int cur, int x, bool rec)
{
	while (cur)
	{
		S[cur].insert(x);
		if (rec) rek.insert(cur);
		cur = fa[cur];
	}
}

void Del(int cur, int x, bool rec)
{
	while (cur)
	{
		S[cur].erase(S[cur].find(x));
		if (rec) rek.insert(cur);
		cur = fa[cur];
	}
}

void Solve()
{
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++) adj[i].clear();
	for (int i = 2; i <= n; i++) 
	{
		cin >> fa[i];
		adj[i].pb(fa[i]);
		adj[fa[i]].pb(i);
	}
	for (int i = 1; i <= n; i++) cin >> p[i], pl[p[i]] = i, S[i].clear();
	DFS(1);
	for (int i = 1; i <= n; i++) Add(i, pl[i], false);
	nkc = 0;
	for (int i = 1; i <= n; i++)
	{
		if (*S[i].begin() == pl[i] && (*--S[i].end()) == pl[i] + siz[i] - 1) ok[i] = true;
		else ok[i] = false, nkc++;
	}
	int x, y;
	for (int i = 1; i <= q; i++)
	{
		cin >> x >> y;
		rek.clear();
		Del(p[x], pl[p[x]], true);
		Del(p[y], pl[p[y]], true);
		swap(pl[p[x]], pl[p[y]]);
		swap(p[x], p[y]);
//		for (int j = 1; j <= n; j++) cerr << pl[j] << ' ';
//		cerr << endl;
		Add(p[x], pl[p[x]], false);
		Add(p[y], pl[p[y]], false);
		for (auto it : rek)
		{
			if (!ok[it]) nkc--;
			if (*S[it].begin() == pl[it] && (*--S[it].end()) == pl[it] + siz[it] - 1) ok[it] = true;
			else ok[it] = false, nkc++;
		}
		if (nkc) ync(0);
		else ync(1);
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