// Problem: B. Wishing Cards
// Contest: Codeforces - Codeforces Round 1069 (Div. 1)
// URL: https://codeforces.com/contest/2174/problem/B
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

int a[100001], nxt[100001];
int dp[2][361][361];
int pre[2][361][361];
void solve()
{
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 0; i <= k; i++) for (int j = 0; j <= k; j++) dp[0][i][j] = dp[1][i][j] = pre[0][i][j] = pre[1][i][j] = -1e8;
	int c = 0;
	vector <int> use;
	for (int i = 1; i <= n; i++)
	{
		if (a[i] <= c) continue;
		c = a[i];
		use.pb(i);
	}
	if (!use.size()) 
	{
		cout << 0 << endl;
		return;
	}
	nxt[0] = use[0];
	for (int i = 0; i < use.size() - 1; i++) nxt[use[i]] = use[i + 1];
	bool cd = 0;
	dp[0][0][0] = pre[0][0][0] = 0;
	for (int i = 1; i <= k; i++) pre[0][0][i] = 0;
	for (auto i : use)
	{
		cd ^= 1;
		for (int s = 0; s <= k; s++) for (int j = 0; j <= k; j++) dp[cd][s][j] = dp[cd ^ 1][s][j]; 
		for (int j = 1; j <= a[i]; j++)
		{
			for (int s = j; s <= k; s++)
			{
				dp[cd][s][j] = max(dp[cd ^ 1][s][j], pre[cd ^ 1][s - j][j - 1] + j * (n - i + 1));
				// cerr << i << ' ' << s << ' ' << j << ' ' << dp[cd][s][j] << endl;
			}
		}
		for (int s = 0; s <= k; s++) 
		{
			pre[cd][s][0] = 0;
			for (int j = 1; j <= k; j++) 
			{
				pre[cd][s][j] = pre[cd][s][j - 1];
				if (dp[cd][s][j] - j * (n - nxt[i] + 1) > pre[cd][s][j]) pre[cd][s][j] = dp[cd][s][j] - j * (n - nxt[i] + 1);
			}
		}
	}
	int ans = 0;
	for (int i = 0; i <= k; i++) for (int j = 0; j <= k; j++) ans = max(ans, dp[cd][i][j]);
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