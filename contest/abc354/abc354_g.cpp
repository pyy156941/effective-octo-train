// Problem: G - Select Strings
// Contest: AtCoder - Panasonic Programming Contest 2024（AtCoder Beginner Contest 354）
// URL: https://atcoder.jp/contests/abc354/tasks/abc354_g
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

bool multiTest = false;

int n;
struct Edge
{
	int v, nxt;
	ll cap, flow;
}e[10501];

int ecnt = 1;
int dep[205];
int head[205], cHead[205];

void AddEdge(int u, int v, int w)
{
	e[++ecnt] = {v, head[u], w, 0};
	head[u] = ecnt;
	e[++ecnt] = {u, head[v], 0, 0};
	head[v] = ecnt;
}

bool BFS(int s, int t)
{
	queue <int> Q;
	for (int i = 1; i <= n; i++) dep[i] = 0;
	dep[s] = 1;
	Q.push(s);
	while (!Q.empty())
	{
		int cur = Q.front();
//		cerr << cur << ' ';
		Q.pop();
		for (int it = head[cur]; it != -1; it = e[it].nxt)
		{
			int v = e[it].v;
			if (!dep[v] && e[it].cap > e[it].flow)
			{
				dep[v] = dep[cur] + 1;
				Q.push(v);
			}
		}
	}
//	cerr << endl;
	return dep[t];
}

ll DFS(int cur, int t, ll flow)
{
	if (cur == t || !flow) return flow;
	ll ret = 0;
	for (int it = cHead[cur]; it != -1; it = e[it].nxt)
	{
		cHead[cur] = it; // opt
		int v = e[it].v;
		ll c;
		if (dep[v] == dep[cur] + 1 && (c = DFS(v, t, min(flow - ret, e[it].cap - e[it].flow))))
		{
			ret += c;
			e[it].flow += c;
			e[it ^ 1].flow -= c;
		}
	}
	return ret;
}

ll MaxFlow(int s, int t)
{
	ll maxflow = 0;
	while (BFS(s, t))
	{
		for (int i = 1; i <= n; i++) cHead[i] = head[i];
		maxflow += DFS(s, t, 1e10);
	}
	return maxflow;
}

bool Find(string a, string b)
{
	for (int i = 0; i + b.length() <= a.length(); i++)
	{
		if (a.substr(i, b.length()) == b) return true; 
	}
	return false;
}

string s[101];
int a[101];

void Solve()
{
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> s[i];
	ll sum = 0;
	for (int i = 1; i <= n; i++) cin >> a[i], sum += a[i];
	int S = n + n + 1, T = n + n + 2;
	for (int i = 1; i <= n + n + 2; i++) head[i] = -1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j < n; j++)
		{
			if (i == j) continue;
			if (s[i] == s[j])
			{
				if (i > j) AddEdge(i, j + n, 2e9);
			}
			else if (Find(s[i], s[j]) || Find(s[j], s[i])) 
			{
				AddEdge(i, j + n, 2e9);
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		AddEdge(S, i, a[i]);
		AddEdge(i + n, T, a[i]);
	}
	n += n + 2;
	cout << sum - MaxFlow(S, T) << endl;
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