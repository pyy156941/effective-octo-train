// Problem: D. Binary Not Search and Queries
// Contest: Codeforces - Codeforces Round 1082 (Div. 1)
// URL: https://codeforces.com/contest/2201/problem/D
// Memory Limit: 512 MB
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

bool multiTest = true;

struct Node
{
	int lefl, lefv, rigl, rigv, mx;
	ll ans;
}tree[800001];

ll c2(ll a)
{
	return a * (a + 1) / 2;
}

void Pushup(int cur, int s, int t)
{
	tree[cur].lefl = tree[ls(cur)].lefl, tree[cur].rigl = tree[rs(cur)].rigl;
	tree[cur].lefv = tree[ls(cur)].lefv, tree[cur].rigv = tree[rs(cur)].rigv;
	if (tree[ls(cur)].mx < tree[rs(cur)].mx)
	{
		tree[cur].ans = tree[rs(cur)].ans;
		tree[cur].mx = tree[rs(cur)].mx;
	}
	else if (tree[ls(cur)].mx > tree[rs(cur)].mx)
	{
		tree[cur].ans = tree[ls(cur)].ans;
		tree[cur].mx = tree[ls(cur)].mx;
	}
	else
	{
		// int su = 0;
		// if (tree[ls(cur)].rigv == tree[cur].mx) su += tree[ls(cur)].rigl;
		// if (tree[rs(cur)].lefv == tree[cur].mx) su += tree[rs(cur)].lefl;
		// if (su == t - s + 1) tree[cur].lefl = tree[cur].rigl = su;
		// Above Wrong!
		int mid = (s + t) >> 1;
		tree[cur].mx = tree[ls(cur)].mx;
		if (tree[ls(cur)].lefl == mid - s + 1)
		{
			if (tree[rs(cur)].lefv == tree[ls(cur)].lefv) tree[cur].lefl += tree[rs(cur)].lefl;
		}
		if (tree[rs(cur)].rigl == t - mid)
		{
			if (tree[ls(cur)].rigv == tree[rs(cur)].rigv) tree[cur].rigl += tree[ls(cur)].rigl;
		}
		tree[cur].ans = tree[ls(cur)].ans + tree[rs(cur)].ans;
		if (tree[ls(cur)].rigv == tree[cur].mx && tree[rs(cur)].lefv == tree[cur].mx) 
		{
			tree[cur].ans += c2(tree[ls(cur)].rigl + tree[rs(cur)].lefl);
			tree[cur].ans -= c2(tree[ls(cur)].rigl);
			tree[cur].ans -= c2(tree[rs(cur)].lefl);
		}
	}
}

void Build(int cur, int s, int t)
{
	if (s == t) 
	{
		tree[cur].lefl = tree[cur].rigl = 1;
		tree[cur].lefv = tree[cur].rigv = tree[cur].mx = 0;
		tree[cur].ans = 1;
		return;
	}
	int mid = (s + t) >> 1;
	Build(ls(cur), s, mid);
	Build(rs(cur), mid + 1, t);
	Pushup(cur, s, t);
}

void Update(int cur, int p, int s, int t, int val)
{
	if (s == t)
	{
		tree[cur].lefl = tree[cur].rigl = 1;
		tree[cur].lefv = tree[cur].rigv = tree[cur].mx = val;
		tree[cur].ans = 1;
		return;
	}
	int mid = (s + t) >> 1;
	if (p <= mid) Update(ls(cur), p, s, mid, val);
	if (p > mid) Update(rs(cur), p, mid + 1, t, val);
	Pushup(cur, s, t);
}

int a[200001];
set <int> pl[200001];
void Solve()
{
	int n, q;
	multiRead(n, q);
	for (int i = 1; i <= n; i++) pl[i].clear();
	for (int i = 1; i <= n; i++) cin >> a[i], pl[a[i]].insert(i);
	Build(1, 1, n);
	int p, x;
	for (int i = 1; i <= n; i++)
	{
		if (!pl[i].size()) continue;
		int fir = *pl[i].begin();
		int las = *(--pl[i].end());
		Update(1, fir, 1, n, las - fir);
	}
	for (int i = 1; i <= q; i++)
	{
		multiRead(p, x);
		int fir1 = *pl[a[p]].begin();
		Update(1, fir1, 1, n, 0);
		auto it = pl[a[p]].lower_bound(p);
		pl[a[p]].erase(it);
		if (pl[a[p]].size())
		{
			int fir2 = *pl[a[p]].begin();
			int las2 = *(--pl[a[p]].end());
			Update(1, fir2, 1, n, las2 - fir2);
		}
		a[p] = x;
		if (pl[a[p]].size())
		{
			int fir3 = *pl[a[p]].begin();
			int las3 = *(--pl[a[p]].end());
			Update(1, fir3, 1, n, 0);
		}
		pl[a[p]].insert(p);
		int fir4 = *pl[a[p]].begin();
		int las4 = *(--pl[a[p]].end());
		Update(1, fir4, 1, n, las4 - fir4);
		cout << tree[1].mx << ' ' << (!tree[1].mx ? 0 : tree[1].ans) << endl;
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