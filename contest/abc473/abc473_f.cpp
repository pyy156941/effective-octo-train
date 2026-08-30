// Problem: F - A/AB Insertion
// Contest: AtCoder - AtCoder Beginner Contest 473
// URL: https://atcoder.jp/contests/abc473/tasks/abc473_f
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
	int mn[2000001], lt[2000001];
	
	void pushup(int cur)
	{
		mn[cur] = min(mn[ls(cur)], mn[rs(cur)]);
	}
	
	void pushdown(int cur)
	{
		if (!lt[cur]) return;
		mn[ls(cur)] += lt[cur];
		mn[rs(cur)] += lt[cur];
		lt[ls(cur)] += lt[cur];
		lt[rs(cur)] += lt[cur];
		lt[cur] = 0;
	}
	
	void update(int cur, int l, int r, int s, int t, int x)
	{
		if (l <= s && t <= r) 
		{
			mn[cur] += x;
			lt[cur] += x;
			return;
		}
		pushdown(cur);
		int mid = (s + t) >> 1;
		if (l <= mid) update(ls(cur), l, r, s, mid, x);
		if (r > mid) update(rs(cur), l, r, mid + 1, t, x);
		pushup(cur);
	}
	
	int query(int cur, int l, int r, int s, int t)
	{
		if (l <= s && t <= r) return mn[cur];
		pushdown(cur);
		int mid = (s + t) >> 1;
		int ans = 1e7;
		if (l <= mid) ans = min(ans, query(ls(cur), l, r, s, mid));
		if (r > mid) ans = min(ans, query(rs(cur), l, r, mid + 1, t));
		return ans;
	}
}t;

int val[500001], pre[500001];
void solve()
{
	int n, q;
	string str;	
	cin >> n >> str >> q;
	for (int i = 1; i <= n; i++) val[i] = (str[i - 1] == 'A' ? 1 : -1), pre[i] = pre[i - 1] + val[i];
	for (int i = 1; i <= n; i++) t.update(1, i, i, 1, n, pre[i]);
	int mode, l, r, p;
	char x;
	for (int i = 1; i <= q; i++)
	{
		cin >> mode;
		if (mode == 1) 
		{
			cin >> p >> x;
			int nv = 0, dif;
			if (x == 'A') nv = 1;
			else nv = -1;
			dif = nv - val[p];
			val[p] = nv;
			t.update(1, p, n, 1, n, dif);
		}
		else
		{
			cin >> l >> r;
			int res = t.query(1, l, r, 1, n);
			if (l > 1) res -= t.query(1, l - 1, l - 1, 1, n);
			// for (int j = 1; j <= n; j++) cerr << t.query(1, j, j, 1, n) << ' ';
			// cerr << endl;
			// for (int j = 1; j <= n; j++) cerr << val[j] << ' ';
			// cerr << endl;
			// cerr << res << endl;
			if (res >= 0) cout << "Yes" << endl;
			else cout << "No" << endl;
		}
	}
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