// Problem: F - Count Cells in a Window
// Contest: AtCoder - UNICORNProgramming Contest2026(AtCoder Beginner Contest 477)
// URL: https://atcoder.jp/contests/abc477/tasks/abc477_f
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
#define isdigit(x) (x >= '0' && x <= '9')
#define least2p(x) ((x == 1) ? 0 : __lg(x) + ((x & (x - 1)) != 0))
#define debug(x) cerr << #x << " : " << x << endl;

#define yn(x) \
do \
{ \
    cout << (x ? 'Y' : 'N'); \
    cout << (x ? 'e' : 'o'); \
    cout << (x ? 's' : '\n'); \
    if (!x) cout << '\n'; \
} while(0)

#define ync(x) \
do \
{ \
    cout << (x ? 'Y' : 'N'); \
    cout << (x ? 'E' : 'O'); \
    cout << (x ? 'S' : '\n'); \
    if (!x) cout << '\n'; \
} while(0)

#define ynl(x) \
do \
{ \
    cout << (x ? 'y' : 'n'); \
    cout << (x ? 'e' : 'o'); \
    cout << (x ? 's' : '\n'); \
    if (!x) cout << '\n'; \
} while(0)

istream& operator >> (istream& cin, i128& x)
{
    x = 0;
    int f = 1;
    char ch;
    ch = cin.get();
    while (ch == ' ' || ch == '\n' || ch == '\t') ch = cin.get();
    if (ch == '-')
    {
        f = -1;
        ch = cin.get();
    }
    while (isdigit(ch))
    {
        x = x * 10 + (ch - '0');
        ch = cin.get();
    }
    cin.putback(ch);
    x *= f;
    return cin;
}

ostream& operator << (ostream& cout, i128 x)
{
    if (x == 0)
    {
        cout << '0';
        return cout;
    }
    if (x < 0)
    {
        cout << '-';
        x = -x;
    }
    if (x >= 10) cout << (x / 10);
    cout << (char)('0' + (x % 10));
    return cout;
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

template <typename ... Args>
void multi_write_endl(Args ... args)
{
    ((cout << args << " "), ...);
    cout << endl;
}

template <typename T>
T fastgcd(T a, T b) // unsigned only, requires C++20
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
T mod_inv(T a, T p)
{
	T x, y;
	exgcd(a, p, x, y);
	return (x + p) % p;
}

template <typename T>
T qpow(T a, T b, T mod)
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

bool multi_test = false;

struct sgt
{
	ll tree[800001], lt[800001];
	
	void pushup(int cur)
	{
		tree[cur] = tree[ls(cur)] + tree[rs(cur)];
	}
	
	void pushdown(int cur, int s, int t)
	{
		if (!lt[cur]) return;
		int mid = (s + t) >> 1;
		tree[ls(cur)] += lt[cur] * (ll)(mid - s + 1);
		tree[rs(cur)] += lt[cur] * (ll)(t - mid);
		lt[ls(cur)] += lt[cur];
		lt[rs(cur)] += lt[cur];
		lt[cur] = 0;
	}
	
	void build(int cur, int s, int t)
	{
		tree[cur] = lt[cur] = 0;
		if (s == t) return;
		int mid = (s + t) >> 1;
		build(ls(cur), s, mid);
		build(rs(cur), mid + 1, t);
	}
	
	void update(int cur, int l, int r, int s, int t, int x)
	{
		if (l <= s && t <= r)
		{
			tree[cur] += (ll)x * (t - s + 1);
			lt[cur] += x;
			return;
		}
		int mid = (s + t) >> 1;
		pushdown(cur, s, t);
		if (l <= mid) update(ls(cur), l, r, s, mid, x);
		if (r > mid) update(rs(cur), l, r, mid + 1, t, x);
		pushup(cur);
	}
	
	ll query(int cur, int l, int r, int s, int t)
	{
		if (l <= s && t <= r) return tree[cur];
		int mid = (s + t) >> 1;
		pushdown(cur, s, t);
		ll res = 0;
		if (l <= mid) res += query(ls(cur), l, r, s, mid);
		if (r > mid) res += query(rs(cur), l, r, mid + 1, t);
		return res;
	}
}t;

struct qry
{
	int l, r, d, id, c;
	qry(int _l, int _r, int _d, int _id, int _c) : l(_l), r(_r), d(_d), id(_id), c(_c) {}
	
	bool operator < (const qry o) const
	{
		return d < o.d;
	}
};

ll ans[200001];
int l[200001], r[200001];
void solve()
{
	int n, m, q, u, d, ql, qr;
	cin >> n >> m >> q;
	for (int i = 1; i <= n; i++) cin >> l[i] >> r[i];
	vector <qry> qs;
	for (int i = 1; i <= q; i++)
	{
		cin >> u >> d >> ql >> qr;
		qs.pb(qry(ql, qr, d, i, 1));
		if (u > 1) qs.pb(qry(ql, qr, u - 1, i, -1));
	}
	sort(qs.begin(), qs.end());
	int pd = 0;
	t.build(1, 1, m);
	for (auto cur : qs)
	{
		int cl = cur.l, cr = cur.r, cd = cur.d, id = cur.id, cc = cur.c;
		while (pd < cd)
		{
			pd++;
			t.update(1, l[pd], r[pd], 1, m, 1);
		}
		ans[cur.id] += t.query(1, cl, cr, 1, m) * cc;
	}
	for (int i = 1; i <= q; i++) cout << ans[i] << endl;
	return;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr);
	int _ = 1;
	if (multi_test) cin >> _;
	while (_--) solve();
	return 0;
}