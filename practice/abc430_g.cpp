// Problem: G - Range Set Modifying Query
// Contest: AtCoder - AtCoder Beginner Contest 430
// URL: https://atcoder.jp/contests/abc430/tasks/abc430_g
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

int n, q;
struct Node1
{
	int sc[61], lt[61];
}tree[1200001];

struct Node2
{
	int mx, cnt, lt;
}tot_tree[1200001];

void Pushup(int cur)
{
	for (int i = 1; i <= 60; i++) tree[cur].sc[i] = tree[ls(cur)].sc[i] + tree[rs(cur)].sc[i];
}

void Pushup_Tot(int cur)
{
	if (tot_tree[ls(cur)].mx > tot_tree[rs(cur)].mx) tot_tree[cur].mx = tot_tree[ls(cur)].mx, tot_tree[cur].cnt = tot_tree[ls(cur)].cnt;
	else if (tot_tree[ls(cur)].mx < tot_tree[rs(cur)].mx) tot_tree[cur].mx = tot_tree[rs(cur)].mx, tot_tree[cur].cnt = tot_tree[rs(cur)].cnt;
	else tot_tree[cur].mx = tot_tree[ls(cur)].mx, tot_tree[cur].cnt = tot_tree[ls(cur)].cnt + tot_tree[rs(cur)].cnt;
}

void Pushdown(int cur, int s, int t)
{
	int mid = (s + t) >> 1;
	for (int i = 1; i <= 60; i++)
	{
		if (tree[cur].lt[i] == -1) continue;
		if (tree[cur].lt[i]) 
		{
			tree[ls(cur)].lt[i] = tree[cur].lt[i];
			tree[rs(cur)].lt[i] = tree[cur].lt[i];
			tree[ls(cur)].sc[i] = mid - s + 1;
			tree[rs(cur)].sc[i] = t - mid;
		}
		if (!tree[cur].lt[i])
		{
			tree[ls(cur)].lt[i] = tree[cur].lt[i];
			tree[rs(cur)].lt[i] = tree[cur].lt[i];
			tree[ls(cur)].sc[i] = 0;
			tree[rs(cur)].sc[i] = 0;
		}
		tree[cur].lt[i] = -1; 
	}
}

void Pushdown_Tot(int cur)
{
	tot_tree[ls(cur)].mx += tot_tree[cur].lt;
	tot_tree[rs(cur)].mx += tot_tree[cur].lt;
	tot_tree[ls(cur)].lt += tot_tree[cur].lt;
	tot_tree[rs(cur)].lt += tot_tree[cur].lt;
	tot_tree[cur].lt = 0;
}

void Build(int cur, int s, int t)
{
	if (s == t)
	{
		tot_tree[cur].mx = tot_tree[cur].lt = 0;
		tot_tree[cur].cnt = 1;
		for (int i = 1; i <= 60; i++) tree[cur].sc[i] = 0, tree[cur].lt[i] = -1;
		return;
	}
	int mid = (s + t) >> 1;
	Build(ls(cur), s, mid);
	Build(rs(cur), mid + 1, t);
	Pushup_Tot(cur);
	Pushup(cur);
}

void Print_Tot(int cur, int s, int t)
{
	cerr << s << ' ' << t << ' ' << tot_tree[cur].mx << ' ' << tot_tree[cur].cnt << ' ' << tot_tree[cur].lt << endl;
	if (s == t) return;
	int mid = (s + t) >> 1;
	Print_Tot(ls(cur), s, mid);
	Print_Tot(rs(cur), mid + 1, t);
}

void Update_Tot(int cur, int l, int r, int s, int t, int x)
{
	if (l <= s && t <= r)
	{
		tot_tree[cur].mx += x;
		tot_tree[cur].lt += x;
		return;
	}
	Pushdown_Tot(cur);
	int mid = (s + t) >> 1;
	if (l <= mid) Update_Tot(ls(cur), l, r, s, mid, x);
	if (r > mid) Update_Tot(rs(cur), l, r, mid + 1, t, x);
	Pushup_Tot(cur);
}

pair <int, int> Query(int cur, int l, int r, int s, int t)
{
	if (l <= s && t <= r) return {tot_tree[cur].mx, tot_tree[cur].cnt};
	Pushdown_Tot(cur);
	int mid = (s + t) >> 1;
	pair <int, int> res = {-1, 0};
	if (l <= mid)
	{
		auto tmp = Query(ls(cur), l, r, s, mid);
		res = tmp;
	}
	if (r > mid)
	{
		auto tmp = Query(rs(cur), l, r, mid + 1, t);
		if (tmp.first > res.first) res = tmp;
		else if (tmp.first == res.first) res.second += tmp.second;
	}
	return res;
}

void Add(int cur, int l, int r, int s, int t, int x)
{
	if (l <= s && t <= r)
	{
		if (!tree[cur].sc[x])
		{
			tree[cur].sc[x] = t - s + 1;
			tree[cur].lt[x] = 1;
			Update_Tot(1, s, t, 1, n, 1);
			return;
		}
		else if (tree[cur].sc[x] == t - s + 1) return;
	}
	Pushdown(cur, s, t);
	int mid = (s + t) >> 1;
	if (l <= mid) Add(ls(cur), l, r, s, mid, x);
	if (r > mid) Add(rs(cur), l, r, mid + 1, t, x);
	Pushup(cur);
}

void Del(int cur, int l, int r, int s, int t, int x)
{
	if (l <= s && t <= r)
	{
		if (tree[cur].sc[x] == t - s + 1)
		{
			tree[cur].sc[x] = 0;
			tree[cur].lt[x] = 0;
			Update_Tot(1, s, t, 1, n, -1);
			return;
		}
		else if (!tree[cur].sc[x]) return;
	}
	Pushdown(cur, s, t);
	int mid = (s + t) >> 1;
	if (l <= mid) Del(ls(cur), l, r, s, mid, x);
	if (r > mid) Del(rs(cur), l, r, mid + 1, t, x);
	Pushup(cur);
}

void Solve()
{
	multiRead(n, q);
	int mode, l, r, x;
	Build(1, 1, n);
	for (int i = 1; i <= q; i++)
	{
		multiRead(mode, l, r);
		if (mode == 1) 
		{
			cin >> x;
			Add(1, l, r, 1, n, x);
		}
		else if (mode == 2)
		{
			cin >> x;
			Del(1, l, r, 1, n, x);
		}
		else 
		{
			auto ans = Query(1, l, r, 1, n);
			cout << ans.first << ' ' << ans.second << endl;
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