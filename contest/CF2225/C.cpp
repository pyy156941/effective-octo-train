// Problem: C. Red-Black Pairs
// Contest: Codeforces - Educational Codeforces Round 189 (Rated for Div. 2)
// URL: https://codeforces.com/contest/2225/problem/C
// Memory Limit: 512 MB
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

int s[200001], dp[200001][4];

int getcost(int a, int d)
{
	int c1 = a ^ d;
	int res = 0;
	if (c1 == 3) res += 2;
	else if (c1 == 0);
	else res++;
	return res;
}

void solve()
{
	int n;
	cin >> n;
	string str;
	cin >> str;
	for (int i = 1; i <= n; i++) s[i] = 0;
	for (int i = 1; i <= n; i++) if (str[i - 1] == 'R') s[i] += 1;
	cin >> str;
	for (int i = 1; i <= n; i++) if (str[i - 1] == 'R') s[i] += 2;
	dp[0][0] = dp[0][1] = dp[0][2] = dp[0][3] = 0;
	dp[1][1] = dp[1][2] = 1e6;
	if (s[1] == 1 || s[1] == 2) dp[1][0] = dp[1][3] = 1;
	else if (s[1] == 0) dp[1][0] = 0, dp[1][3] = 2;
	else if (s[1] == 3) dp[1][0] = 2, dp[1][3] = 0;
	if (n == 1)
	{
		cout << min(dp[1][0], dp[1][3]) << endl;
		return;
	}
	for (int i = 2; i <= n; i++)
	{
		int ml = min(min(dp[i - 1][0], dp[i - 1][1]), min(dp[i - 1][2], dp[i - 1][3]));
		int mll = min(min(dp[i - 2][0], dp[i - 2][1]), min(dp[i - 2][2], dp[i - 2][3]));
		dp[i][0] = dp[i][3] = ml;
		dp[i][1] = mll + getcost(s[i - 1], 1);
		dp[i][2] = mll + getcost(s[i - 1], 2);
		for (int j = 0; j < 4; j++) dp[i][j] += getcost(s[i], j);
		// cerr << dp[i][0] << ' ' << dp[i][1] << ' ' << dp[i][2] << ' ' << dp[i][3] << endl;
	}
	int ans = min(min(dp[n][0], dp[n][1]), min(dp[n][2], dp[n][3]));
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