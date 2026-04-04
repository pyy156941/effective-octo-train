// Problem: E. Remove at the lowest cost
// Contest: Codeforces - Codeforces Round 1070 (Div. 2)
// URL: https://codeforces.com/contest/2176/problem/E
// Memory Limit: 256 MB
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

bool multi_test = true;

struct node
{
	ll sum;
	int mx;
	bool lt;
}tree[800001];

void pushup(int cur)
{
	tree[cur].sum = tree[ls(cur)].sum + tree[rs(cur)].sum;
	tree[cur].mx = max(tree[ls(cur)].mx, tree[rs(cur)].mx);
}

void pushdown(int cur, int s, int t)
{
	int mid = (s + t) >> 1;
	if (!tree[cur].lt) return;
	tree[ls(cur)].mx = tree[cur].mx;
	tree[ls(cur)].sum = (ll)(mid - s + 1) * tree[cur].mx; 
	tree[ls(cur)].lt = true;
	tree[rs(cur)].mx = tree[cur].mx;
	tree[rs(cur)].sum = (ll)(t - mid) * tree[cur].mx;
	tree[rs(cur)].lt = true; 
	tree[cur].lt = false;
}

void build(int cur, int s, int t)
{
	if (s == t)
	{
		tree[cur].sum = tree[cur].mx = 1000000007;
		tree[cur].lt = false;
		return;
	}
	int mid = (s + t) >> 1;
	build(ls(cur), s, mid);
	build(rs(cur), mid + 1, t);
	pushup(cur);
}

void update(int cur, int l, int r, int s, int t, int x)
{
	if (l <= s && t <= r) 
	{
		tree[cur].mx = x;
		tree[cur].sum = (ll)(t - s + 1) * x;
		tree[cur].lt = true;
		return;
	}
	pushdown(cur, s, t);
	int mid = (s + t) >> 1;
	if (l <= mid) update(ls(cur), l, r, s, mid, x);
	if (r > mid) update(rs(cur), l, r, mid + 1, t, x);
	pushup(cur);
}

ll qv(int cur, int p, int s, int t)
{
	if (s == t) return tree[cur].sum;
	pushdown(cur, s, t);
	int mid = (s + t) >> 1;
	if (p <= mid) return qv(ls(cur), p, s, mid);
	else return qv(rs(cur), p, mid + 1, t);
}

int n, a[200001], c[200001];
int lb[200001], rb[200001], ind[200001];
void solve()
{
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> c[i];
	stack <int> s;
	for (int i = 1; i <= n; i++) rb[i] = n;
	for (int i = 1; i <= n; i++) 
	{
		while (!s.empty() && a[s.top()] < a[i]) rb[s.top()] = i - 1, s.pop();
		s.push(i);
	}
	while (!s.empty()) s.pop();
	for (int i = 1; i <= n; i++) lb[i] = 1; 
	for (int i = n; i >= 1; i--)
	{
		while (!s.empty() && a[s.top()] < a[i]) lb[s.top()] = i + 1, s.pop();
		s.push(i);
	}
	while (!s.empty()) s.pop();
	build(1, 1, n);
	for (int i = 1; i <= n; i++) ind[i] = i;
	sort(ind + 1, ind + n + 1, [] (int a, int b) { return c[a] > c[b]; });
	for (int i = 1; i <= n; i++) update(1, lb[ind[i]], rb[ind[i]], 1, n, c[ind[i]]);
	// for (int i = 1; i <= n; i++) cerr << qv(1, i, 1, n) << ' ';
	// cerr << endl;
	cout << tree[1].sum - tree[1].mx << ' ';
	int p;
	for (int i = 1; i <= n; i++)
	{
		cin >> p;
		update(1, lb[p], rb[p], 1, n, 0);
		cout << tree[1].sum - tree[1].mx << ' ';
	}
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