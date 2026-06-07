// Problem: F. Vessels, Heights and Two Versions (Hard Version)
// Contest: Codeforces - Codeforces Round 1102 (Div. 2)
// URL: https://codeforces.com/contest/2234/problem/F
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
	int n;
	ll sum[2500001], tag[2500001];
	
	void pushup(int cur)
	{
		sum[cur] = sum[ls(cur)] + sum[rs(cur)];
	}
	
	void pushdown(int cur, int s, int t)
	{
		if (!tag[cur]) return;
		int mid = (s + t) >> 1;
		sum[ls(cur)] = tag[cur] * (ll)(mid - s + 1);
		sum[rs(cur)] = tag[cur] * (ll)(t - mid);
		tag[ls(cur)] = tag[cur];
		tag[rs(cur)] = tag[cur];
		tag[cur] = 0;
	}
	
	void build(int cur, int s, int t)
	{
		sum[cur] = tag[cur] = 0;
		if (s == t) return;
		int mid = (s + t) >> 1;
		build(ls(cur), s, mid);
		build(rs(cur), mid + 1, t);
	}
	
	void update(int cur, int l, int r, int s, int t, ll x)
	{
		if (l <= s && t <= r)
		{
			sum[cur] = x * (ll)(t - s + 1);
			tag[cur] = x;
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
		if (l <= s && t <= r) return sum[cur];
		int mid = (s + t) >> 1;
		pushdown(cur, s, t);
		ll ans = 0;
		if (l <= mid) ans += query(ls(cur), l, r, s, mid);
		if (r > mid) ans += query(rs(cur), l, r, mid + 1, t);
		return ans;
	}
	
	void build(int _n) 
	{
		n = _n;
		build(1, 1, n);
	}
	
	void update(int l, int r, ll x) { update(1, l, r, 1, n, x); }
	ll query(int l, int r) { return query(1, l, r, 1, n); }
}ts, tp;

int a[600002];
ll ans[200005];
void solve()
{
	int n;
	cin >> n;
	int mxp = 0;
	a[0] = a[3 * n + 1] = 2e9;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		ans[i] = 0;
		a[i + n] = a[i + n + n] = a[i];
		if (!mxp || a[i] >= a[mxp]) mxp = i;
	}
	ts.build(3 * n), tp.build(3 * n);
	stack <int> S;
	S.push(0);
	for (int i = 1; i <= n; i++)
	{
		while (!S.empty() && a[S.top()] < a[i]) S.pop();
		ts.update(S.top() + 1, i, a[i]);
		S.push(i);
	}
	for (int i = 1; i <= n; i++)
	{
		if (i > mxp + 1) ans[i] += ts.query(mxp + n + 1, i + n - 1);
		else if (i <= mxp) ans[i] += ts.query(mxp + 1, i + n - 1);
		while (!S.empty() && a[S.top()] < a[i + n]) S.pop();
		ts.update(S.top() + 1, i + n, a[i + n]);
		S.push(i + n);
		// cerr << ans[i] << ' ';
	}
	// cerr << endl;
	while (!S.empty()) S.pop();
	S.push(3 * n + 1);
	for (int i = 3 * n; i > 2 * n; i--)
	{
		while (!S.empty() && a[S.top()] < a[i]) S.pop();
		tp.update(i, S.top() - 1, a[i]);
		S.push(i);
	}
	for (int i = n; i >= 1; i--)
	{
		while (!S.empty() && a[S.top()] < a[i + n]) S.pop();
		tp.update(i + n, S.top() - 1, a[i + n]);
		S.push(i + n);
		if (i > mxp) ans[i] += tp.query(i + n, mxp + 2 * n - 1);
		else if (i < mxp) ans[i] += tp.query(i + n, mxp + n - 1);
		// cerr << ans[i] << ' ';
	}
	// cerr << endl;
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