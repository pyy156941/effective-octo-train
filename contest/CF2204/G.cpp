// Problem: G. Grid Path
// Contest: Codeforces - Educational Codeforces Round 188 (Rated for Div. 2)
// URL: https://codeforces.com/contest/2204/problem/G
// Memory Limit: 512 MB
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

bool multi_test = false;

struct Mat
{
	int m, n;
	ull mod;
	ull v[302][302];
	
	Mat (int row = 0, int col = 0, ull _mod = 998244353) 
	{
		m = row, n = col, mod = _mod;
		memset(v, 0, sizeof(v));
	}
	
	Mat operator * (const Mat& a) const
 	{
 		assert(n == a.m);
		int p = a.n;
		Mat res(m, p, mod);
		for (int i = 1; i <= m; i++)
		{
			for (int k = 1; k <= n; k++)
			{
				if (!v[i][k]) continue;
				ull cv = v[i][k];
				for (int j = 1; j <= p; j++)
				{
					if (!a.v[k][j]) continue;
					res.v[i][j] += cv * a.v[k][j];
					if ((k & 15) == 0) res.v[i][j] %= mod;
				}
			}
		}
		for (int i = 1; i <= m; i++) for (int j = 1; j <= p; j++) res.v[i][j] %= mod; 
		return res;
	}

	Mat operator ^ (ll a) const
	{
		assert(m == n);
		Mat ans(n, n, mod), base(n, n, mod);
		for (int i = 1; i <= n; i++) ans.v[i][i] = 1;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				base.v[i][j] = v[i][j];
			}
		}
		while (a)
		{
			if (a & 1) ans = ans * base;
			base = base * base;
			a >>= 1;
		}
		return ans;
	} 
};

void solve()
{
	int n, m;
	ull mod;
	multi_read(n, m, mod);
	Mat s = Mat(1, 2 * m + 1, mod);
	Mat trf = Mat(2 * m + 1, 2 * m + 1, mod);
	s.v[1][1] = m;
	for (int i = 1; i <= m; i++) s.v[1][i + m] = 1;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= i; j++) trf.v[j][i] = (m - i + 1) % mod;
		for (int j = i + 1; j <= m; j++) trf.v[j][i] = (m - j + 1) % mod;
		for (int j = 1; j < i; j++) trf.v[j + m][i] = mod - (m - i + 1) % mod;
		for (int j = i; j <= m; j++) trf.v[j + m][i] = 0;
		for (int j = 1; j < i; j++) trf.v[j + m][i + m] = j % mod;
		for (int j = i; j <= m; j++) trf.v[j + m][i + m] = i % mod;
		for (int j = i + 1; j <= m; j++) trf.v[j][i + m] = mod - i % mod;
		for (int j = 1; j <= i; j++) trf.v[j][i + m] = 0;
	}
	trf.v[2 * m + 1][2 * m + 1] = 1;
	for (int i = 1; i <= m; i++) trf.v[i][2 * m + 1] = 1;
	Mat f = s * (trf ^ (n - 1));
	// for (int i = 1; i <= 2 * m; i++) cerr << s.v[1][i] << ' ';
	// cerr << endl;
	// for (int i = 1; i <= 2 * m; i++) cerr << f.v[1][i] << ' ';
	// cerr << endl;
	ull ans = f.v[1][2 * m + 1] % mod;
	for (int i = 1; i <= m; i++) ans = (ans + f.v[1][i]) % mod;
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