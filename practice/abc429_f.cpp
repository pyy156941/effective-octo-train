// Problem: F - Shortest Path Query
// Contest: AtCoder - Polaris.AI Programming Contest 2025（AtCoder Beginner Contest 429）
// URL: https://atcoder.jp/contests/abc429/tasks/abc429_f
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
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

const int inf = 1048576;
struct Node
{
	int sp[3][3];
}tree[800001];
int grid[200001];

void Pushup(int cur, int s, int t)
{
	int mid = (s + t) >> 1;
	int inter = grid[mid] & grid[mid + 1];
	tree[cur].sp[0][0] = tree[cur].sp[0][1] = tree[cur].sp[0][2] = inf;
	tree[cur].sp[1][0] = tree[cur].sp[1][1] = tree[cur].sp[1][2] = inf;
	tree[cur].sp[2][0] = tree[cur].sp[2][1] = tree[cur].sp[2][2] = inf;
	if (inter & 4)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				tree[cur].sp[i][j] = min(tree[cur].sp[i][j], tree[ls(cur)].sp[i][2] + tree[rs(cur)].sp[2][j]);
			}
		}
	} 
	if (inter & 2)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				tree[cur].sp[i][j] = min(tree[cur].sp[i][j], tree[ls(cur)].sp[i][1] + tree[rs(cur)].sp[1][j]);
			}
		}
	}
	if (inter & 1)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				tree[cur].sp[i][j] = min(tree[cur].sp[i][j], tree[ls(cur)].sp[i][0] + tree[rs(cur)].sp[0][j]);
			}
		}
	}
}

void Build(int cur, int l, int r)
{
	if (l == r)
	{
		tree[cur].sp[0][0] = tree[cur].sp[0][1] = tree[cur].sp[0][2] = inf;
		tree[cur].sp[1][0] = tree[cur].sp[1][1] = tree[cur].sp[1][2] = inf;
		tree[cur].sp[2][0] = tree[cur].sp[2][1] = tree[cur].sp[2][2] = inf;
		if (grid[l] & 4) tree[cur].sp[2][2] = 1;
		if (grid[l] & 2) tree[cur].sp[1][1] = 1;
		if (grid[l] & 1) tree[cur].sp[0][0] = 1;
		if ((grid[l] & 3) == 3) tree[cur].sp[0][1] = tree[cur].sp[1][0] = 2;
		if ((grid[l] & 6) == 6) tree[cur].sp[1][2] = tree[cur].sp[2][1] = 2;
		if ((grid[l] & 7) == 7) tree[cur].sp[0][2] = tree[cur].sp[2][0] = 3;
		return;
	}
	int mid = (l + r) >> 1;
	Build(ls(cur), l, mid);
	Build(rs(cur), mid + 1, r);
	Pushup(cur, l, r);
}

void Update(int cur, int p, int line, int s, int t)
{
	if (s == t)
	{
		if (grid[s] & (1 << line)) grid[s] -= (1 << line);
		else grid[s] += (1 << line);
		tree[cur].sp[0][0] = tree[cur].sp[0][1] = tree[cur].sp[0][2] = inf;
		tree[cur].sp[1][0] = tree[cur].sp[1][1] = tree[cur].sp[1][2] = inf;
		tree[cur].sp[2][0] = tree[cur].sp[2][1] = tree[cur].sp[2][2] = inf;
		if (grid[s] & 4) tree[cur].sp[2][2] = 1;
		if (grid[s] & 2) tree[cur].sp[1][1] = 1;
		if (grid[s] & 1) tree[cur].sp[0][0] = 1;
		if ((grid[s] & 3) == 3) tree[cur].sp[0][1] = tree[cur].sp[1][0] = 2;
		if ((grid[s] & 6) == 6) tree[cur].sp[1][2] = tree[cur].sp[2][1] = 2;
		if ((grid[s] & 7) == 7) tree[cur].sp[0][2] = tree[cur].sp[2][0] = 3;
		return;
	}
	int mid = (s + t) >> 1;
	if (p <= mid) Update(ls(cur), p, line, s, mid);
	if (p > mid) Update(rs(cur), p, line, mid + 1, t);
	Pushup(cur, s, t);
}

void Solve()
{
	int n, q, p, line;
	string str; 
	cin >> n;
	for (int i = 0; i < 3; i++)
	{
		cin >> str;
		for (int j = 0; j < n; j++)
		{
			if (str[j] == '.') grid[j + 1] += (1 << i);
		}
	}
	Build(1, 1, n);
	cin >> q;
	for (int i = 1; i <= q; i++)
	{
		multiRead(line, p);
		line--;
		Update(1, p, line, 1, n);
		// for (int j = 1; j <= n; j++) cerr << grid[j] << ' ';
		// cerr << endl;
		int ans = tree[1].sp[0][2];
		if (ans >= inf) cout << "-1" << endl;
		else cout << ans - 1 << endl;
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