// Problem: D - AtCoder Wallpaper
// Contest: AtCoder - Panasonic Programming Contest 2024（AtCoder Beginner Contest 354）
// URL: https://atcoder.jp/contests/abc354/tasks/abc354_d
// Memory Limit: 1024 MB
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
#define debug(x) cerr << #x << " : " << x << endl;
#define isdigit(x) (x >= '0' && x <= '9')

#define yn(x) pc(x ? 'Y' : 'N'), pc(x ? 'e' : 'o'), x ? (pc('s'), pc('\n')) : pc('\n')
#define ync(x) pc(x ? 'Y' : 'N'), pc(x ? 'E' : 'O'), x ? (pc('S'), pc('\n')) : pc('\n')
#define ynl(x) pc(x ? 'y' : 'n'), pc(x ? 'e' : 'o'), x ? (pc('s'), pc('\n')) : pc('\n')

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

ll GetCol(int x, int ub, int lb)
{
	if (x % 4 == 0)
	{
		ll ans = 0;
		if (ub % 2) ans += 2, ub--;
		if (lb % 2) ans -= 2, lb--;
		ans += 3 * (ll)(ub - lb) / 2;
		return ans;
	}
	else if (x % 4 == 1)
	{
		ll ans = 0;
		if (ub % 2) ans++, ub--;
		if (lb % 2) ans--, lb--;
		ans += 3 * (ll)(ub - lb) / 2;
		return ans;
	}
	else if (x % 4 == 2)
	{
		ll ans = 0;
		if (ub % 2) ub--;
		if (lb % 2) lb--;
		ans += (ll)(ub - lb) / 2;
		return ans;
	}
	else
	{
		ll ans = 0;
		if (ub % 2) ans++, ub--;
		if (lb % 2) ans--, lb--;
		ans += (ll)(ub - lb) / 2;
		return ans;
	}
}

int Gs(int x)
{
	if (x >= 0) return x / 4;
	if (x % 4 == 0) return -Gs(-x);
	return -Gs(-x) - 1;
}

void Solve()
{
	int a, b, c, d;
	cin >> a >> b >> c >> d; // a - c horizontal
	ll b0 = GetCol(0, d, b), b1 = GetCol(1, d, b), b2 = GetCol(2, d, b), b3 = GetCol(3, d, b);
	int c0 = Gs(c), c1 = Gs(c), c2 = Gs(c), c3 = Gs(c);
	if ((c % 4 + 4) % 4 > 0) c0++;
	if ((c % 4 + 4) % 4 > 1) c1++;
	if ((c % 4 + 4) % 4 > 2) c2++;
	int a0 = Gs(a), a1 = Gs(a), a2 = Gs(a), a3 = Gs(a);
	if ((a % 4 + 4) % 4 > 0) a0++;
	if ((a % 4 + 4) % 4 > 1) a1++;
	if ((a % 4 + 4) % 4 > 2) a2++;
//	cerr << a0 << ' ' << a1 << ' ' << a2 << ' ' << a3 << ' ' << endl;
//	cerr << b0 << ' ' << b1 << ' ' << b2 << ' ' << b3 << ' ' << endl;
//	cerr << c0 << ' ' << c1 << ' ' << c2 << ' ' << c3 << ' ' << endl;
	cout << b0 * (ll)(c0 - a0) + b1 * (ll)(c1 - a1) + b2 * (ll)(c2 - a2) + b3 * (ll)(c3 - a3) << endl;
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