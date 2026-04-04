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

int n, lb[200001], ub[200001];
struct Node
{
	bool type;
	int le, re; // if type, then lower/upper bound of both ends
	ll ans;
}tree[800001];

Node Merge(Node a, Node b)
{
	Node res;
	res.ans = a.ans + b.ans;
	if (a.type && b.type)
	{
		if (a.re < b.le) 
		{
			res.type = false;
			res.le = a.re;
			res.re = b.le;
			res.ans += b.le - a.re;
		}
		else if (a.le > b.re)
		{
			res.type = false;
			res.le = a.le;
			res.re = b.re;
			res.ans += a.le - b.re;
		}
		else
		{
			res.type = true;
			res.le = max(a.le, b.le);
			res.re = min(a.re, b.re);
		}
	}
	else if (a.type)
	{
		res.type = false;
		if (b.le < a.le) 
		{
			res.le = a.le;
			res.re = b.re;
			res.ans += a.le - b.le;
		}
		else if (b.le > a.re)
		{
			res.le = a.re;
			res.re = b.re;
			res.ans += b.le - a.re;
		}
		else 
		{
			res.le = b.le;
			res.re = b.re;
		}
	}
	else if (b.type)
	{
		res.type = false;
		if (a.re < b.le)
		{
			res.le = a.le;
			res.re = b.le;
			res.ans += b.le - a.re;
		}
		else if (a.re > b.re)
		{
			res.le = a.le;
			res.re = b.re;
			res.ans += a.re - b.re;
		}
		else
		{
			res.le = a.le;
			res.re = a.re;
		}
	}
	else
	{
		res.type = false;
		res.le = a.le;
		res.re = b.re;
		res.ans += abs(a.re - b.le);
	}
	return res;
}

void Pushup(int cur)
{
	tree[cur] = Merge(tree[ls(cur)], tree[rs(cur)]);
}

void Build(int cur, int l, int r)
{
	if (l == r)
	{
		tree[cur].ans = 0;
		tree[cur].le = lb[l];
		tree[cur].re = ub[l];
		tree[cur].type = true;
		return;
	}
	int mid = (l + r) >> 1;
	Build(ls(cur), l, mid);
	Build(rs(cur), mid + 1, r);
	Pushup(cur);
}

Node Query(int cur, int l, int r, int s, int t)
{
	if (l <= s && t <= r) return tree[cur];
	int mid = (s + t) >> 1;
	Node res;
	bool lf = false;
	if (l <= mid) 
	{
		res = Query(ls(cur), l, r, s, mid);
		lf = true;
	}
	if (r > mid)
	{
		auto rr = Query(rs(cur), l, r, mid + 1, t);
		if (lf) res = Merge(res, rr);
		else res = rr;
	}
	return res;
}

void Solve()
{
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> lb[i] >> ub[i];
	Build(1, 1, n);
	int q, sx, sy, tx, ty;
	cin >> q;
	for (int i = 1; i <= q; i++)
	{
		cin >> sx >> sy >> tx >> ty;
		if (sx > tx) swap(sx, tx), swap(sy, ty);
		auto res = Query(1, sx, tx, 1, n);
		ll ans = tx - sx;
		if (res.type)
		{
			ans += res.ans;
			if (sy > res.re && ty > res.re) ans += (ll)sy + ty - 2ll * res.re; 
			else if (sy < res.le && ty < res.le) ans += 2ll * res.le - sy - ty;
			else ans += abs(ty - sy);
		}
		else ans += res.ans + abs(sy - res.le) + abs(ty - res.re);
		cout << ans << '\n';
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