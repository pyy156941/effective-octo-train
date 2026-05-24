// Problem: F. Quadratic Jumps
// Contest: Codeforces - Codeforces Round 1099 (Div. 2)
// URL: https://codeforces.com/contest/2231/problem/F
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

int n;
bitset <200001> s1, s2, s3; // can/cannot be represented as the sum of 1/2/3 perfect squares
int m1[200001]; // m1: min x^2 that exists x^2-y^2=i

bool check2(int u, int v)
{
	if (u > v) swap(u, v);
	int dif = v - u;
	if (s2[dif]) return true;
	int mxd = max(v - 1, n - u);
	if (m1[dif] <= mxd) return true;
	return false;
}

void solve()
{
	int q;
	cin >> n >> q;
	int u, v;
	for (int i = 1; i <= n; i++) 
	{
		m1[i] = n + 1;
		s1.reset(i);
		s2.reset(i);
		s3.reset(i);
	}
	for (int i = 1; i <= sqrt(n); i++) s1[i * i] = true;
	for (int i = 1; i <= sqrt(n); i++) for (int j = 1; j <= sqrt(n); j++) if (i * i + j * j <= n) s2[i * i + j * j] = true;
	for (int i = 1; i <= n; i++)
	{
		if (!s1[i]) continue;
		s3 |= (s2 << i);
	}
	for (int i = 1; i <= sqrt(n); i++) for (int j = 1; j < i; j++) m1[i * i - j * j] = min(m1[i * i - j * j], i * i);
	for (int i = 1; i <= q; i++)
	{
		cin >> u >> v;
		int dif = v - u;
		if (s1[dif]) 
		{
			cout << 1 << endl;
			continue;
		}
		if (check2(u, v)) 
		{
			cout << 2 << endl;
			continue;
		}
		if (s3[dif])
		{
			cout << 3 << endl;
			continue;
		}
		bool ok = false;
		for (int j = 1; j * j < u; j++)
		{
			if (check2(u - j * j, v))
			{
				cout << 3 << endl;
				ok = true;
				break;
			}
		}
		if (ok) continue;
		for (int j = 1; u + j * j <= n; j++)
		{
			if (check2(u + j * j, v))
			{
				cout << 3 << endl;
				ok = true;
				break;
			}
		}
		if (ok) continue;
		cout << 4 << endl;
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