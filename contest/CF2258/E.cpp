// Problem: E. DivMEX
// Contest: Codeforces - Codeforces Round 1118 (Div. 2)
// URL: https://codeforces.com/contest/2258/problem/E
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

constexpr int N = 200003;

vector <int> pr;
bool np[N + 1];
void init()
{
	for (int i = 2; i <= N; i++)
	{
		if (!np[i]) 
		{
			pr.pb(i);
			for (int j = i + i; j <= N; j += i) np[j] = true;
		}
	}
}

struct sgt
{
	int mn[800001];
	
	void pushup(int cur)
	{
		mn[cur] = min(mn[ls(cur)], mn[rs(cur)]);
	}
	
	void update(int cur, int s, int t, int p, int x)
	{
		if (s == t) 
		{
			mn[cur] = x;
			return;
		}
		int mid = (s + t) >> 1;
		if (p <= mid) update(ls(cur), s, mid, p, x);
		if (p > mid) update(rs(cur), mid + 1, t, p, x);
		pushup(cur);
	}
	
	int query(int cur, int s, int t, int l, int r)
	{
		if (l <= s && t <= r) return mn[cur];	
		int mid = (s + t) >> 1, ans = N;
		if (l <= mid) ans = min(ans, query(ls(cur), s, mid, l, r));
		if (r > mid) ans = min(ans, query(rs(cur), mid + 1, t, l, r));
		return ans;
	}
	
	void build(int cur, int s, int t)
	{
		mn[cur] = 0;
		if (s == t) return;
		int mid = (s + t) >> 1;
		build(ls(cur), s, mid);
		build(rs(cur), mid + 1, t);
	}
}t;

int n, a[200001];
int mp[N];
void solve()
{
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	if (n == 1)
	{
		cout << 1 << endl << 2 << endl;
		return;
	}
	vector <int> c;
	for (auto p : pr)
	{
		if (p > min(N, n + 100)) break;
		ll cur = 1;
		while (cur * (ll)p <= min(N, n + 100)) 
		{
			cur *= p;
			c.pb(cur);
		}
	}
	sort(c.begin(), c.end());
	while (c.size() > 1 && c[c.size() - 2] > n) c.pop_back();
	int cc = c.size();
	for (int i = 0; i < N; i++) mp[i] = 0;
	for (int i = 0; i < cc; i++) mp[c[i]] = i;
	vector <int> lst(cc);
	vector <bool> ans(cc);
	t.build(1, 0, cc - 1);
	for (int i = 1; i <= n; i++)
	{
		vector <int> divs;
		int tmp = a[i];
		for (auto p : pr) 
		{
			if (p > 450) break;
			if (tmp % p) continue;
			int cur = 1;
			while (tmp % p == 0) 
			{
				tmp /= p, cur *= p, 
				divs.pb(mp[cur]);
			}
		}
		if (tmp > 1) divs.pb(mp[tmp]);
		for (auto d : divs)
		{
			int l = lst[d];
			if (l == i - 1) continue;
			int mn = d > 0 ? t.query(1, 0, cc - 1, 0, d - 1) : l + 1;
			// cerr << i << ' ' << c[d] << ' ' << l << ' ' << mn << endl;
			if (mn > l) ans[d] = true;
		}
		for (auto d : divs) t.update(1, 0, cc - 1, d, i), lst[d] = i;
	}
	for (int i = 0; i < cc; i++)
	{
		int l = lst[i];
		if (l == n) continue;
		int mn = i > 0 ? t.query(1, 0, cc - 1, 0, i - 1) : l + 1;
		if (mn > l) ans[i] = true;
	}
	int sum = 0;
	for (int i = 0; i < cc; i++) sum += ans[i];
	cout << sum << endl;
	for (int i = 0; i < cc; i++) if (ans[i]) cout << c[i] << ' ';
	cout << endl;
	return;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr);
	int _ = 1;
	init();
	if (multi_test) cin >> _;
	while (_--) solve();
	return 0;
}