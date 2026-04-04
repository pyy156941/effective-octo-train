// Problem: F - Must Buy
// Contest: AtCoder - AtCoder Beginner Contest 441 (Promotion of Engineer Guild Fes)
// URL: https://atcoder.jp/contests/abc441/tasks/abc441_f
// Memory Limit: 1024 MB
// Time Limit: 2500 ms
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
#define debug(x) cerr << #x << " : " << x << endl;
#define isdigit(x) (x >= '0' && x <= '9')
#define least2p(x) ((x == 1) ? 0 : __lg(x) + ((x & (x - 1)) != 0))

#define yn(x) pc(x ? 'Y' : 'N'), pc(x ? 'e' : 'o'), x ? (pc('s'), pc('\n')) : pc('\n')
#define ync(x) pc(x ? 'Y' : 'N'), pc(x ? 'E' : 'O'), x ? (pc('S'), pc('\n')) : pc('\n')
#define ynl(x) pc(x ? 'y' : 'n'), pc(x ? 'e' : 'o'), x ? (pc('s'), pc('\n')) : pc('\n')

template <typename T>
T readInt() 
{
    T x = 0;
    int f = 1;
    char ch = getchar();
    while (!isdigit(ch)) 
    {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) 
    {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    return x * f;
}

template <typename T>
void readInt(T &x) {
    x = 0;
    int f = 1;
    char ch = getchar();
    while (!isdigit(ch)) 
    {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) 
    {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    x *= f;
}

template <typename T>
void writeInt(T x) 
{
    if (x < 0) 
    {
        putchar('-');
        x = -x;
    }
    if (x > 9) writeInt(x / 10);
    putchar(x % 10 + '0');
}

template <typename ... Args>
void multiRead(Args& ... args)
{
    ((cin >> args), ...);
}

template <typename ... Args>
void multiWrite(Args ... args)
{
    ((cout << args << " "), ...);
}


template <typename T>
void fastgcd(T a, T b) // unsigned only
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
	auto za = countr_zero(a);
	auto zb = countr_zero(b);
	a >>= za;
	b >>= zb;
	do 
	{
		T dif = a - b;
		if (a > b) a = b, b = dif;
		else b = b - a;
		b >>= countr_zero(dif);
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
T Inv(T a, T p)
{
	T x, y;
	exgcd(a, p, x, y);
	return (x + p) % p;
}

template <typename T>
T QPow(T a, T b, T mod)
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

bool multiTest = false;

int n, m;
ll dpf[1001][50001], dps[50001];
int p[1001], v[1001];
char ans[1001];
void Solve()
{
	readInt(n), readInt(m);
	for (int i = 1; i <= n; i++) readInt(p[i]), readInt(v[i]);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < p[i]; j++) dpf[i][j] = dpf[i - 1][j];
		for (int j = p[i]; j <= m; j++) dpf[i][j] = max(dpf[i - 1][j], dpf[i - 1][j - p[i]] + (ll)v[i]);
	}
	ll get_n = dpf[n - 1][m - p[n]] + (ll)v[n], exc_n = dpf[n - 1][m];
	if (get_n < exc_n) ans[n] = 'C';
	else if (get_n > exc_n) ans[n] = 'A';
	else ans[n] = 'B';
	for (int i = n; i > 1; i--)
	{
		for (int j = m; j >= p[i]; j--) dps[j] = max(dps[j], dps[j - p[i]] + (ll)v[i]);
		ll get_i1 = 0, exc_i1 = 0;
		for (int j = 0; j <= m - p[i - 1]; j++) get_i1 = max(get_i1, dpf[i - 2][j] + dps[m - p[i - 1] - j]);
		for (int j = 0; j <= m; j++) exc_i1 = max(exc_i1, dpf[i - 2][j] + dps[m - j]);
		get_i1 += (ll)v[i - 1];
		if (get_i1 < exc_i1) ans[i - 1] = 'C';
		else if (get_i1 > exc_i1) ans[i - 1] = 'A';
		else ans[i - 1] = 'B';
	}
	for (int i = 1; i <= n; i++) putchar(ans[i]);
	putchar('\n');
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr);
	int _ = 1;
	if (multiTest) cin >> _;
	while (_--) Solve();
	return 0;
}