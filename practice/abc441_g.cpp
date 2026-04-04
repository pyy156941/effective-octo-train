// Problem: G - Takoyaki and Flip
// Contest: AtCoder - AtCoder Beginner Contest 441 (Promotion of Engineer Guild Fes)
// URL: https://atcoder.jp/contests/abc441/tasks/abc441_g
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

struct Node
{
	ll mx, lts;
	int dc;
	bool rev;
}tree[800001];

void Pushup(int cur)
{
	tree[cur].mx = max(tree[ls(cur)].mx, tree[rs(cur)].mx);
	tree[cur].dc = tree[ls(cur)].dc + tree[rs(cur)].dc;
}

void Pushdown(int cur, int s, int t)
{
	int mid = (s + t) >> 1;
	if (tree[cur].rev)
	{
		tree[ls(cur)].mx = tree[ls(cur)].lts = 0;
		tree[rs(cur)].mx = tree[rs(cur)].lts = 0;
		tree[ls(cur)].rev ^= 1;
		tree[rs(cur)].rev ^= 1;
		tree[ls(cur)].dc = (mid - s + 1) - tree[ls(cur)].dc;
		tree[rs(cur)].dc = (t - mid) - tree[rs(cur)].dc;
		tree[cur].rev = false;
	}
	if (tree[ls(cur)].dc < (mid - s + 1)) 
	{
		tree[ls(cur)].mx += tree[cur].lts;
		tree[ls(cur)].lts += tree[cur].lts;
	}
	if (tree[rs(cur)].dc < (t - mid))
	{
		tree[rs(cur)].mx += tree[cur].lts;
		tree[rs(cur)].lts += tree[cur].lts;
	}
	tree[ls(cur)].mx = min(tree[ls(cur)].mx, tree[cur].mx);
	tree[rs(cur)].mx = min(tree[rs(cur)].mx, tree[cur].mx);
	tree[cur].lts = 0;
}

void Build(int cur, int s, int t)
{
	tree[cur].lts = 0;
	tree[cur].mx = 0;
	tree[cur].dc = 0;
	tree[cur].rev = false;
	if (s == t) return;
	int mid = (s + t) >> 1;
	Build(ls(cur), s, mid);
	Build(rs(cur), mid + 1, t);
}

void Add(int cur, int l, int r, int s, int t, ll x)
{
	if (l <= s && t <= r)
	{
		if (tree[cur].dc == (t - s + 1)) return;
		tree[cur].mx += x;
		tree[cur].lts += x;
		return;
	}
	Pushdown(cur, s, t);
	int mid = (s + t) >> 1;
	if (l <= mid) Add(ls(cur), l, r, s, mid, x);
	if (r > mid) Add(rs(cur), l, r, mid + 1, t, x);
	Pushup(cur);
}

void Set(int cur, int l, int r, int s, int t)
{
	if (l <= s && t <= r)
	{
		tree[cur].mx = tree[cur].lts = 0;
		tree[cur].dc = (t - s + 1) - tree[cur].dc;
		tree[cur].rev ^= 1;
		return;
	}
	Pushdown(cur, s, t);
	int mid = (s + t) >> 1;
	if (l <= mid) Set(ls(cur), l, r, s, mid);
	if (r > mid) Set(rs(cur), l, r, mid + 1, t);
	Pushup(cur);
}

ll Query(int cur, int l, int r, int s, int t)
{
	if (l <= s && t <= r) return tree[cur].mx;
	Pushdown(cur, s, t);
	int mid = (s + t) >> 1;
	ll ans = 0;
	if (l <= mid) ans = max(ans, Query(ls(cur), l, r, s, mid));
	if (r > mid) ans = max(ans, Query(rs(cur), l, r, mid + 1, t));
	return ans;
}

void PrintTree(int cur, int s, int t)
{
	cerr << s << ' ' << t << ' ' << tree[cur].mx << endl;
	if (s == t) return;
	int mid = (s + t) >> 1;
	PrintTree(ls(cur), s, mid);
	PrintTree(rs(cur), mid + 1, t);
}

void Solve()
{
	int n, q;
	readInt(n), readInt(q);
	int mode = 0, l, r;
	ll x;
	Build(1, 1, n);
	for (int i = 1; i <= q; i++)
	{
		readInt(mode), readInt(l), readInt(r);
		if (mode == 1)
		{
			readInt(x);
			Add(1, l, r, 1, n, x);
		}
		else if (mode == 2) Set(1, l, r, 1, n);
		else 
		{
			ll ans = Query(1, l, r, 1, n);
			writeInt(ans), pc('\n');
		}
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