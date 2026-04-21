// Problem: E. Left is Always Right
// Contest: Codeforces - Pinely Round 5 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/2161/problem/E
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

int s[100001];
ll fact[100001], invf[100001];

constexpr ll mod = 998244353;

ll binom(int n, int m)
{
	if (m > n) return 0;
	return fact[n] * invf[m] % mod * invf[n - m] % mod;
}

int n, k;
ll get_balanced(int c0, int c1)
{
	int mid = (k - 1) / 2;
	if (c0 > mid || c1 > mid) return 0;
	return binom(k - 1 - c0 - c1, mid - c0);
}

ll dp[100001][2];
void solve()
{
	string str;
	cin >> n >> k >> str;
	fact[0] = fact[1] = invf[0] = invf[1] = 1;
	for (int i = 2; i <= n; i++) fact[i] = (fact[i - 1] * (ll)i) % mod, invf[i] = mod_inv(fact[i], mod);
	reverse(str.begin(), str.end());
	for (int i = 1; i <= n; i++)
	{
		if (str[i - 1] == '?') s[i] = -1;
		else if (str[i - 1] == '0') s[i] = 0;
		else s[i] = 1;
	}
	int c0 = 0, c1 = 0, lef0 = 0, lef1 = 0;
	for (int i = 1; i < k; i++)
	{
		if (s[i] == 1) c1++;
		else if (s[i] == 0) c0++; 
	}
	for (int i = k; i <= n; i++) 
	{
		if (s[i] == 1) lef1++;
		else if (s[i] == 0) lef0++;
	}
	for (int i = k; i <= n; i++) dp[i][0] = dp[i][1] = 0;
	if (!lef0)
	{
		dp[k][1] = get_balanced(c0, c1);
		for (int i = max(k / 2 + 1, c1); i < k - c0; i++) dp[k][1] = (dp[k][1] + binom(k - 1 - c1 - c0, i - c1)) % mod;
	}
	if (!lef1)
	{
		dp[k][0] = get_balanced(c0, c1);
		for (int i = max(k / 2 + 1, c0); i < k - c1; i++) dp[k][0] = (dp[k][0] + binom(k - 1 - c1 - c0, i - c0)) % mod;
	}
	for (int i = k; i < n; i++)
	{
		if (s[i] == 1) lef1--;
		else if (s[i] == 0) lef0--;
		int p = (i - 1) % (k - 1) + 1;
		if (s[p] != -1 && s[i] != -1)
		{
			if (s[p] != s[i]) break;
		}
		else if (s[p] == -1 && s[i] == -1);
		else
		{
			if (s[i] != -1)
			{
				s[p] = s[i];
				if (s[p] == 1) c1++;
				else c0++;
			}
			else s[i] = s[p];
		}
		if (s[i] == -1)
		{
			if (!lef1) dp[i + 1][0] = get_balanced(c0, c1 + 1);
			if (!lef0) dp[i + 1][1] = get_balanced(c0 + 1, c1);
			// cerr << c0 << ' ' << c1 << ' ' << dp[k + 1][0] << ' ' << dp[k + 1][1] << endl;
		}
		else if (s[i] == 1) 
		{
			if (!lef1) dp[i + 1][0] = get_balanced(c0, c1);
		}
		else 
		{
			if (!lef0) dp[i + 1][1] = get_balanced(c0, c1);
		}
	}
	ll ans = 0;
	// for (int i = k; i <= n; i++) cerr << dp[i][0] << ' ' << dp[i][1] << endl;
	for (int i = k; i <= n; i++) ans = (ans + dp[i][0] + dp[i][1]) % mod;
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