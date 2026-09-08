// Problem: E. Cyclic Balance
// Contest: Codeforces - Educational Codeforces Round 194 (Rated for Div. 2)
// URL: https://codeforces.com/contest/2260/problem/E
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

bool multi_test = false;

int get_ans(int c00, int c11, int c01)
{
	int l = c01, r = c01 + c00 + c11, mc01 = r;
	int lef = min(c00, c11), bef = max(c00, c11);
	int dif = bef - lef;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		int ad = mid - c01;
		int mc = 0;
		if (ad <= dif) mc = bef - ad;
		else mc = lef - ((ad - dif) / 2);
		if (mc <= mid) mc01 = mid, r = mid - 1;
		else l = mid + 1;
	}
	// cerr << mc01 << endl;
	return 2 * (mc01 - c01) + mc01 * 2 - (c00 + c11);
}

bool s[300001];
int typ[300000];
int pre[300000][4]; // 00, 11, 01, 10
void solve()
{
	int n, q;
	string str;
	cin >> n >> q >> str;
	for (int i = 1; i <= n; i++) s[i] = (str[i - 1] == '0' ? false : true);
	for (int i = 1; i < n; i++)
	{
		if (!s[i])
		{
			if (!s[i + 1]) typ[i] = 0;
			else typ[i] = 2;
		}
		else
		{
			if (!s[i + 1]) typ[i] = 3;
			else typ[i] = 1;
		}
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (j == typ[i]) pre[i][j] = pre[i - 1][j] + 1;
			else pre[i][j] = pre[i - 1][j];
		}
	}
	int l, r;
	for (int i = 1; i <= q; i++)
	{
		cin >> l >> r;
		int c00 = pre[r - 1][0] - pre[l - 1][0];
		int c11 = pre[r - 1][1] - pre[l - 1][1];
		int c01 = pre[r - 1][2] - pre[l - 1][2];
		int c10 = pre[r - 1][3] - pre[l - 1][3];
		if (!s[r])
		{
			if (!s[l]) c00++;
			else c01++;
		}
		else
		{
			if (!s[l]) c10++;
			else c11++;
		}
		// cerr << l << ' ' << r << ' ' << c00 << ' ' << c11 << ' ' << c01 << ' ' << c10 << endl;
		cout << get_ans(c00, c11, c01) << endl;
	}
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