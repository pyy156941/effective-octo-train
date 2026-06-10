// Problem: F. Shortest GCD Paths
// Contest: Codeforces - Educational Codeforces Round 191 (Rated for Div. 2)
// URL: https://codeforces.com/contest/2233/problem/F
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
// #pragma GCC optimize("O3,Ofast,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

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

bool multi_test = false;

vector <int> da, db;
int dp[1345][1345];
vector <int> das[1345], dbs[1345]; // indices of divisors of divisors of a, b
vector <int> tra[1345], trb[1345]; // transfer multipliers

int n, a, b;
void solve()
{
	cin >> n >> a >> b;
	int g = gcd(a, b);
	n /= g;
	a /= g;
	b /= g;
	da.clear(), db.clear();
	for (int i = 1; i * i <= a; i++)
	{
		if (a % i) continue;
		da.pb(i);
		if (i * i != a) da.pb(a / i);
	}
	sort(da.begin(), da.end());
	for (int i = 1; i * i <= b; i++)
	{
		if (b % i) continue;
		db.pb(i);
		if (i * i != b) db.pb(b / i);
	}
	sort(db.begin(), db.end());
	for (int i = 0; i < da.size(); i++)
	{
		das[i].clear();
		tra[i].clear();
		for (int j = 0; j <= i; j++)
		{
			if (da[i] % da[j] == 0) das[i].pb(j), tra[i].pb(da[i] / da[j]);
		}
	}
	for (int i = 0; i < db.size(); i++)
	{
		dbs[i].clear();
		trb[i].clear();
		for (int j = 0; j <= i; j++)
		{
			if (db[i] % db[j] == 0) dbs[i].pb(j), trb[i].pb(db[i] / db[j]);
		}
	}
	dp[0][0] = 0;
	// cerr << da.size() << ' ' << db.size() << endl;
	for (int i = 0; i < da.size(); i++)
	{
		for (int j = 0; j < db.size(); j++)
		{
			if (!i && !j) continue;
			dp[i][j] = 1e9;
			for (int k = 0; k < das[i].size(); k++)
			{
				for (int l = 0; l < dbs[j].size(); l++)
				{
					int ri = das[i][k], rj = dbs[j][l];
					if (ri == i && rj == j) continue;
					// cerr << i << ' ' << j << ' ' << ri << ' ' << rj << endl;
					dp[i][j] = min(dp[i][j], dp[ri][rj] + max(tra[i][k], trb[j][l]));
				}
			}
		}
		// cerr << i << endl;
	}
	cout << dp[da.size() - 1][db.size() - 1] << endl;
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