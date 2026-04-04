// Problem: C. Where's My Water?
// Contest: Codeforces - Codeforces Round 1085 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/2207/problem/C
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
void fastgcd(T a, T b) // unsigned only, requires C++20
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

int a[2002];

ll pg[2002], sg[2002];
ll pa[2002], sa[2002];
ll get_best(int l, int r, int h)
{
	stack <pair <int, int>> stk;
	pg[l - 1] = 0;
	stk.push({l - 1, 1e9 + 7});
	for (int i = l; i <= r; i++)
	{
		while (!stk.empty() && stk.top().second < a[i]) stk.pop();
		pg[i] = pg[stk.top().first] + (ll)(h - min(h, a[i])) * (ll)(i - stk.top().first);
		stk.push({i, a[i]});
	}
	while (!stk.empty()) stk.pop();
	sg[r + 1] = 0;
	stk.push({r + 1, 1e9 + 7});
	for (int i = r; i >= l; i--)
	{
		while (!stk.empty() && stk.top().second < a[i]) stk.pop();
		sg[i] = sg[stk.top().first] + (ll)(h - min(h, a[i])) * (ll)(stk.top().first - i);
		stk.push({i, a[i]});
	}
	while (!stk.empty()) stk.pop();
	ll res = 0;
	for (int i = l; i <= r; i++) res = max(res, pg[i] + sg[i] - (ll)(h - min(h, a[i])));
	// cerr << l << ' ' << r << ' ' << h << ' ' << res << endl;
	return res;
}

void solve()
{
	int n, h;
	multi_read(n, h);
	for (int i = 1; i <= n; i++) cin >> a[i];
	a[0] = h + 1, a[n + 1] = h + 1;
	get_best(1, n, h);
	for (int i = 1; i <= n; i++) pa[i] = pg[i], sa[i] = sg[i];
	ll ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (a[i - 1] < a[i] || a[i + 1] < a[i]) continue;
		ll cur = pa[i] + sa[i] - (ll)(h - a[i]);
		ans = max(ans, cur);
		int cmax = i;
		ll sec = 0;
		for (int j = i + 1; j <= n + 1; j++)
		{
			if (a[j] >= a[cmax]) 
			{
				if (cmax != i) sec = max(sec, get_best(cmax, j, a[cmax]));
				cmax = j;
			}
		}
		cmax = i;
		for (int j = i - 1; j >= 0; j--)
		{
			if (a[j] >= a[cmax])
			{
				if (cmax != i) sec = max(sec, get_best(j, cmax, a[cmax]));
				cmax = j;
			}
		}
		ans = max(ans, cur + sec);
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