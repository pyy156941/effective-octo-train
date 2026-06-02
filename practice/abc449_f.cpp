// Problem: F - Grid Clipping
// Contest: AtCoder - AtCoder Beginner Contest 449
// URL: https://atcoder.jp/contests/abc449/tasks/abc449_f
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

int vr[400007], vc[400007], cv = 0, cc = 0;

struct sgt
{
	int n;
	
	struct node
	{
		int l, r, tag;
		int sum;
	}tree[2000001];
	
	void build(int cur, int s, int t)
	{
		tree[cur].tag = 0, tree[cur].sum = 0, tree[cur].l = vr[s], tree[cur].r = vr[t + 1];
		if (s == t) return;
		int mid = (s + t) >> 1;
		build(ls(cur), s, mid);
		build(rs(cur), mid + 1, t);
	}
	
	void pushup(int cur, int s, int t)
	{
		if (tree[cur].tag > 0) tree[cur].sum = tree[cur].r - tree[cur].l;
		else 
		{
			if (s != t) tree[cur].sum = tree[ls(cur)].sum + tree[rs(cur)].sum;
			else tree[cur].sum = 0;
		}
	}
	
	void update(int cur, int l, int r, int s, int t, int x)
	{
		if (l <= s && t <= r)
		{
			tree[cur].tag += x;
			pushup(cur, s, t);
			return;
		}
		int mid = (s + t) >> 1;
		if (l <= mid) update(ls(cur), l, r, s, mid, x);
		if (r > mid) update(rs(cur), l, r, mid + 1, t, x);
		pushup(cur, s, t);
	}
	
	int getsum() { return tree[1].sum; }
}t;

int r[200001], c[200001], rb[200001], cb[200001];
vector <int> in[400001], out[400001];
void solve()
{
	int H, W, h, w, n;
	cin >> H >> W >> h >> w >> n;
	cv = cc = 0;
	H -= h - 1;
	W -= w - 1;
	for (int i = 1; i <= n; i++)
	{
		cin >> r[i] >> c[i];
		rb[i] = max(1, r[i] - h + 1);
		cb[i] = max(1, c[i] - w + 1);
		r[i] = min(H + 1, r[i] + 1);
		c[i] = min(W + 1, c[i] + 1);
		vr[++cv] = r[i];
		vr[++cv] = rb[i];
		vc[++cc] = c[i];
		vc[++cc] = cb[i];
	}
	sort(vr + 1, vr + cv + 1);
	sort(vc + 1, vc + cc + 1);
	cv = unique(vr + 1, vr + cv + 1) - vr - 1;
	cc = unique(vc + 1, vc + cc + 1) - vc - 1;
	for (int i = 1; i <= n; i++)
	{
		r[i] = lower_bound(vr + 1, vr + cv + 1, r[i]) - vr;
		rb[i] = lower_bound(vr + 1, vr + cv + 1, rb[i]) - vr;
		c[i] = lower_bound(vc + 1, vc + cc + 1, c[i]) - vc;
		cb[i] = lower_bound(vc + 1, vc + cc + 1, cb[i]) - vc;
	}
	for (int i = 1; i <= cc; i++) in[i].clear(), out[i].clear();
	// [cb[i], c[i] - 1]
	if (!n)
	{
		cout << (ll)H * W << endl;
		return;
	}
	t.build(1, 1, cv - 1);
	ll covered = 0;
	for (int i = 1; i <= n; i++)
	{
		in[cb[i]].pb(i);
		out[c[i]].pb(i);
		// cerr << rb[i] << ' ' << r[i] << ' ' << cb[i] << ' ' << c[i] << endl;
	}
	for (int i = 1; i <= cc; i++)
	{
		int cl = 0;
		if (i > 1) cl = vc[i] - vc[i - 1];
		covered += (ll)t.getsum() * cl;
		// cerr << vc[i] << ' ' << covered << endl;
		for (auto it : in[i]) t.update(1, rb[it], r[it] - 1, 1, cv - 1, 1);
		for (auto it : out[i]) t.update(1, rb[it], r[it] - 1, 1, cv - 1, -1);
	}
	cout << (ll)H * W - covered << endl;
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