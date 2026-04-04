// Problem: G - Knight Placement
// Contest: AtCoder - AtCoder Beginner Contest 445
// URL: https://atcoder.jp/contests/abc445/tasks/abc445_g
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
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
#define least2p(x) ((x == 1) ? 0 : __lg(x) + ((x & (x - 1)) != 0))

#define yn(x) pc(x ? 'Y' : 'N'), pc(x ? 'e' : 'o'), x ? (pc('s'), pc('\n')) : pc('\n')
#define ync(x) pc(x ? 'Y' : 'N'), pc(x ? 'E' : 'O'), x ? (pc('S'), pc('\n')) : pc('\n')
#define ynl(x) pc(x ? 'y' : 'n'), pc(x ? 'e' : 'o'), x ? (pc('s'), pc('\n')) : pc('\n')

template <typename T>
T readInt() 
{
    T x = 0;
    int f = 1;
    char ch = getchar();
    while (!isdigit(ch)) 
    {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) 
    {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    return x * f;
}

template <typename T>
void readInt(T &x) {
    x = 0;
    int f = 1;
    char ch = getchar();
    while (!isdigit(ch)) 
    {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) 
    {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    x *= f;
}

template <typename T>
void writeInt(T x) 
{
    if (x < 0) 
    {
        putchar('-');
        x = -x;
    }
    if (x > 9) writeInt(x / 10);
    putchar(x % 10 + '0');
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
int n, m;
struct Edge
{
	int v, nxt;
	ll cap, flow;
}e[1440001];

int ecnt = 1;
int dep[90001];
int head[90001], cHead[90001];

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
		Q.pop();
		for (int it = head[cur]; it; it = e[it].nxt)
		{
			int v = e[it].v;
			if (!dep[v] && e[it].cap > e[it].flow)
			{
				dep[v] = dep[cur] + 1;
				Q.push(v);
			}
		}
	}
	return dep[t];
}

ll DFS(int cur, int t, ll flow)
{
	if (cur == t || !flow) return flow;
	ll ret = 0;
	for (int it = cHead[cur]; it; it = e[it].nxt)
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

bool grid[301][301], color[301][301], ans[301][301];

int w;
int to_id(int x, int y)
{
	return (x - 1) * w + y;
}

pair <int, int> to_coord(int id)
{
	return {(id - 1) / w + 1, (id - 1) % w + 1};
}

void Solve()
{
	int a, b;
	string str;
	multi_read(w, a, b);
	for (int i = 1; i <= w; i++) 
	{
		cin >> str;
		for (int j = 1; j <= w; j++) grid[i][j] = (true ? str[j - 1] == '.' : false);
	}
	int g = gcd(a, b);
	int dx[8] = {a, a, b, b, -a, -a, -b, -b}, dy[8] = {b, -b, a, -a, b, -b, a, -a}; 
	a /= g, b /= g;
	if (a % 2 && b % 2)
	{
		for (int i = 1; i <= w; i++)
		{
			for (int j = 1; j <= w; j++) color[i][j] = (i / g) % 2;
		}
	}
	else
	{
		for (int i = 1; i <= w; i++)
		{
			for (int j = 1; j <= w; j++) color[i][j] = (i / g + j / g) % 2;
		}
	}
	for (int i = 1; i <= w; i++)
	{
		for (int j = 1; j <= w; j++)
		{
			if (!grid[i][j]) continue;
			for (int d = 0; d < 8; d++)
			{
				int nx = i + dx[d], ny = j + dy[d];
				if (nx < 1 || nx > w || ny < 1 || ny > w) continue;
				if (!grid[nx][ny]) continue;
				if (color[i][j]) AddEdge(to_id(i, j), to_id(nx, ny), 4e7);
			}
		}
	}
	int S = w * w + 1, T = w * w + 2;
	n = w * w + 2;
	for (int i = 1; i <= w; i++)
	{
		for (int j = 1; j <= w; j++)
		{
			if (!grid[i][j]) continue;
			if (color[i][j]) AddEdge(S, to_id(i, j), 1);
			else AddEdge(to_id(i, j), T, 1);
		}
	}
	MaxFlow(S, T);
	BFS(S, T);
	for (int i = 1; i <= w * w; i++)
	{
		auto [x, y] = to_coord(i);
		if (!grid[x][y]) continue;
		if (dep[i] && color[x][y]) ans[x][y] = true;
		if (!dep[i] && !color[x][y]) ans[x][y] = true;
	}
	for (int i = 1; i <= w; i++)
	{
		for (int j = 1; j <= w; j++)
		{
			if (!grid[i][j]) cout << '#';
			else if (ans[i][j]) cout << 'o';
			else cout << '.';
		}
		cout << endl;
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