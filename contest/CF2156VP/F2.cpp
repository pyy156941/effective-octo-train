// Problem: F2. Strange Operation (Hard Version)
// Contest: Codeforces - Codeforces Round 1061 (Div. 2)
// URL: https://codeforces.com/contest/2156/problem/F2
// Memory Limit: 256 MB
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

bool multi_test = true;

struct bit
{
	int n;
	int tree[300001];
	
	void clear(int _n)
	{
		n = _n;
		for (int i = 1; i <= n; i++) tree[i] = 0;
	}
	
	void update(int p, int x)
	{
		while (p <= n)
		{
			tree[p] += x;
			p += lowbit(p);
		}
	}
	
	int query(int p)
	{
		int res = 0;
		while (p)
		{
			res += tree[p];
			p -= lowbit(p);
		}
		return res;
	}
	
	int query(int l, int r)
	{
		if (l > r) return 0;
		return query(r) - query(l - 1);
	}
}t1;

struct sgt
{
	int n;
	int tree[1200001];
	
	void pushup(int cur)
	{
		tree[cur] = min(tree[ls(cur)], tree[rs(cur)]);
	}
	
	void build(int cur, int s, int t)
	{
		if (s == t) 
		{
			tree[cur] = 1e6;
			return;
		}
		int mid = (s + t) >> 1;
		build(ls(cur), s, mid);
		build(rs(cur), mid + 1, t);
		pushup(cur);
	}
	
	void update(int cur, int s, int t, int p, int x)
	{
		if (s == t) 
		{
			tree[cur] = x;
			return;
		}
		int mid = (s + t) >> 1;
		if (p <= mid) update(ls(cur), s, mid, p, x);
		if (p > mid) update(rs(cur), mid + 1, t, p, x);
		pushup(cur);
	}
	
	int query(int cur, int l, int r, int s, int t)
	{
		if (l <= s && t <= r) return tree[cur];
		int mid = (s + t) >> 1;
		int ans = 1e6;
		if (l <= mid) ans = min(ans, query(ls(cur), l, r, s, mid));
		if (r > mid) ans = min(ans, query(rs(cur), l, r, mid + 1, t));
		return ans;
	}
	
	void build(int _n) 
	{
		n = _n;
		build(1, 1, n);
	}
	
	void update(int p, int x) { update(1, 1, n, p, x); }
	int query(int l, int r) { return query(1, l, r, 1, n); }
}t2;

int p[300001], ans[300001];
void solve()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> p[i];
	t1.clear(n);
	t2.build(n);
	for (int i = 1; i <= n; i++) t1.update(p[i], 1), t2.update(p[i], i);
	for (int i = 1; i <= n; i++)
	{
		int curv = n + 1;
		while (true)
		{
			int cur = t2.query(1, curv - 1);
			curv = p[cur];
			int rnk = t1.query(1, curv);
			if (rnk % 2) 
			{
				ans[cur] = i;
				t1.update(curv, -1);
				t2.update(curv, 1e6);
				break;
			}
		}
	}
	for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
	cout << endl;
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