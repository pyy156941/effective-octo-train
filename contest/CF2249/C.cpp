// Problem: C. Double-Rift Dial
// Contest: Codeforces - Codeforces Round 1112 (Div. 1)
// URL: https://codeforces.com/contest/2249/problem/C
// Memory Limit: 256 MB
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

bool multi_test = true;

struct sgt
{
	int tree[2000001];
	int lt[2000001];
	
	void build(int cur, int s, int t)
	{
		tree[cur] = lt[cur] = 0;
		if (s == t) return;
		int mid = (s + t) >> 1;
		build(ls(cur), s, mid);
		build(rs(cur), mid + 1, t);
	}
	
	void pushup(int cur)
	{
		tree[cur] = max(tree[ls(cur)], tree[rs(cur)]);
	}
	
	void pushdown(int cur)
	{
		if (lt[cur] == 0) return;
		tree[ls(cur)] += lt[cur];
		tree[rs(cur)] += lt[cur];
		lt[ls(cur)] += lt[cur];
		lt[rs(cur)] += lt[cur];
		lt[cur] = 0;
	}
	
	void update(int cur, int l, int r, int s, int t, int x)
	{
		if (l <= s && t <= r) 
		{
			tree[cur] += x;
			lt[cur] += x;
			return;
		}
		int mid = (s + t) >> 1;
		pushdown(cur);
		if (l <= mid) update(ls(cur), l, r, s, mid, x);
		if (r > mid) update(rs(cur), l, r, mid + 1, t, x);
		pushup(cur);
	}
	
	int query(int cur, int l, int r, int s, int t)
	{
		if (l <= s && t <= r) return tree[cur];
		int mid = (s + t) >> 1;
		pushdown(cur);
		int ans = 0;
		if (l <= mid) ans = max(ans, query(ls(cur), l, r, s, mid));
		if (r > mid) ans = max(ans, query(rs(cur), l, r, mid + 1, t));
		return ans;
	}
}t;

int n;
int p[400001], pl[200001];
bool occ[200001]; // initial pass
void solve()
{
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> p[i], p[i + n] = p[i];
	int N = 2 * n - 1;
	t.build(1, 1, N);
	for (int i = 1; i <= n; i++) occ[i] = false;
	int cur = 0;
	for (int i = n; i <= N; i++)
	{
		if (p[i] == 1)
		{
			if (!occ[2]) cur++;
		}
		else if (p[i] == n)
		{
			if (!occ[n - 1]) cur++;
		}
		else
		{
			cur--;
			if (!occ[p[i] - 1]) cur++;
			if (!occ[p[i] + 1]) cur++;
		}
		occ[p[i]] = true;
		pl[p[i]] = i;
		t.update(1, i, i, 1, N, cur);
	}
	int ans = 0;
	if (t.query(1, n, N, 1, N) <= 2) ans++;
	for (int i = n - 1; i >= 1; i--)
	{
		int lim = i + n - 1;
		if (p[i] == 1)
		{
			int p2 = pl[2];
			t.update(1, i, p2 - 1, 1, N, 1);
		}
		else if (p[i] == n)
		{
			int pn1 = pl[n - 1];
			t.update(1, i, pn1 - 1, 1, N, 1);
		}
		else
		{
			int pin1 = pl[p[i] - 1], pip1 = pl[p[i] + 1];
			t.update(1, i, min(pin1, pip1) - 1, 1, N, 1);
			t.update(1, max(pin1, pip1), lim, 1, N, -1);
		}
		pl[p[i]] = i;
		if (t.query(1, i, lim, 1, N) <= 2) ans++;
	}
	cout << ans << endl;
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