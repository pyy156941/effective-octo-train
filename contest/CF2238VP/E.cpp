// Problem: E. Cake Trial
// Contest: Codeforces - Codeforces Round 1106 (Div. 2)
// URL: https://codeforces.com/contest/2238/problem/E
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

constexpr int INF = INT_MAX / 2;

int t[501];
int dp[2][501][501]; // (current place), count of fake, max suffix sum
void solve()
{
	int n;
	string str;
	cin >> n >> str;
	for (int i = 1; i <= n; i++) 
	{
		if (str[i - 1] == 'F') t[i] = -1;
		else if (str[i - 1] == 'T') t[i] = 1;
		else t[i] = 0;
	}
	for (int i = 0; i <= n; i++) for (int j = 0; j <= n; j++) dp[0][i][j] = dp[1][i][j] = INF;
	dp[1][0][0] = 0;
	int cur = 1;
	for (int i = 1; i <= n; i++)
	{
		cur = 1 - cur;
		for (int s = 0; s <= i; s++)
		{
			for (int ms = 0; ms <= i; ms++) dp[cur][s][ms] = INF; // reset to take min
			for (int ms = 0; ms <= i; ms++)
			{
				if (t[i] != -1) // T or N
				{
					int nms = max(0, ms - 1);
					dp[cur][s][nms] = min(dp[cur][s][nms], dp[1 - cur][s][ms]);
				}
				if (t[i] != 1 && s > 0) // F or N
				{
					int nms = ms + 1;
					if (dp[1 - cur][s - 1][ms] == INF) continue;
					dp[cur][s][nms] = min(dp[cur][s][nms], max(dp[1 - cur][s - 1][ms], nms));
				}
			}
		}
		// for (int s = 0; s <= i; s++)
		// {
			// for (int ms = 0; ms <= i; ms++)
			// {
				// cerr << min(dp[cur][s][ms], 15) << ' ';
			// }
			// cerr << endl;
		// }
	}
	int ans = 0;
	for (int s = 0; s <= n; s++) for (int ms = 0; ms <= n; ms++) ans = max(ans, s - dp[cur][s][ms]);
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