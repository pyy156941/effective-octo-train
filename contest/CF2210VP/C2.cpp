// Problem: C2. A Simple GCD Problem (Hard Version)
// Contest: Codeforces - Codeforces Round 1089 (Div. 2)
// URL: https://codeforces.com/contest/2210/problem/C2
// Memory Limit: 512 MB
// Time Limit: 6000 ms
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

constexpr int bound = 17, inf = 0x1f1f1f1f;
constexpr int p[bound] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
ll a[50001], b[50001], l[50001], g[50001];
int dp[50001][bound];
void solve()
{
	int n;
	cin >> n;
	for (int i = 0; i <= n; i++) for (int j = 0; j < bound; j++) dp[i][j] = -inf;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	for (int i = 1; i < n; i++) g[i] = gcd(a[i], a[i + 1]);
	l[1] = g[1];
	l[n] = g[n - 1];
	for (int i = 2; i < n; i++) l[i] = g[i - 1] * g[i] / gcd(g[i - 1], g[i]);
	a[0] = g[0] = a[1];
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++)
	{
		ll rg = g[i - 1];
		if (l[i] < a[i] && b[i] >= l[i]) 
		{
			a[i] = l[i];
			for (int k = 0; k < bound; k++)
			{
				if (dp[i - 1][k] < 0) continue;
				if (i == 1 || gcd(a[i - 1] * p[k], a[i]) == rg) dp[i][0] = max(dp[i][0], dp[i - 1][k] + 1);
			}
		}
		else if (l[i] < a[i] && b[i] < l[i])
		{
			for (int k = 0; k < bound; k++)
			{
				if (dp[i - 1][k] < 0) continue;
				if (i == 1 || gcd(a[i - 1] * p[k], a[i]) == rg) dp[i][0] = max(dp[i][0], dp[i - 1][k]);
			}
		}
		else
		{
			dp[i][0] = dp[i - 1][0];
			for (int k = 1; k < bound; k++) 
			{
				if (dp[i - 1][k] < 0) continue;
				if (i == 1 || gcd(a[i - 1] * p[k], a[i]) == rg) dp[i][0] = max(dp[i][0], dp[i - 1][k]); 
			}
			for (int j = 1; j < bound; j++)
			{
				if (b[i] < l[i] * p[j]) break;
				if (i == 1 || gcd(a[i - 1], a[i] * p[j]) == rg) dp[i][j] = max(dp[i][j], dp[i - 1][0] + 1);
				for (int k = 1; k < bound; k++) 
				{
					if (dp[i - 1][k] < 0) continue;
					if (i == 1 || gcd(a[i - 1] * p[k], a[i] * p[j]) == rg) dp[i][j] = max(dp[i][j], dp[i - 1][k] + 1);
				}
			}
		}
		// for (int j = 0; j < bound; j++) cerr << dp[i][j] << ' ';
		// cerr << endl;
	}
	int ans = 0;
	for (int j = 0; j < bound; j++) ans = max(ans, dp[n][j]);
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