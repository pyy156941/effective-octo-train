// Problem: F - Half and Median
// Contest: AtCoder - AtCoder Beginner Contest 444
// URL: https://atcoder.jp/contests/abc444/tasks/abc444_f
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
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

bool multiTest = true;

int n;
ll m;
int a[100001], p2[100001];
bool check(int mid)
{
	if (mid == 1) return true;
	ll alrs = 0; // sum of a[i] - 1 for all i that a[i] < mid
	ll smc = 0; // current count of numbers < mid
	ll lef = n + m; // count of numbers to be added
	ll tot = n + m; // total count of numbers
	ll m2c = 0; // count of 2 * mid - 1 after first loop
	map <int, ll> mp; // count of each number after first loop (exclude 2 * mid - 1)
	for (int i = 1; i <= n; i++)
	{
		if (a[i] < mid) 
		{
			p2[i] = 0;
			alrs += (ll)(a[i] - 1);
			smc++, lef--;
		}
		else
		{
			p2[i] = 1;
			while (a[i] / p2[i] >= mid)
			{
				if (a[i] / (p2[i] * 2) < mid) break;
				p2[i] *= 2;
			} 
			int q = a[i] / p2[i];
			int rem = a[i] % p2[i];
			mp[q] += (ll)(p2[i] - rem);
			if (q + 1 != 2 * mid) mp[q + 1] += (ll)rem;
			else mp[mid] += (ll)rem * 2;
		}
	}
	for (auto [v, c] : mp) lef -= c;
	m2c = mp[2 * mid - 1];
	if (lef <= 0) return smc <= tot / 2; // only smc numbers < mid that cannot be avoided
	if (lef <= alrs)
	{
		smc += lef;
		return smc <= tot / 2;
	}
	lef -= alrs;
	smc += alrs;
	if (m2c * (mid - 1) >= lef) 
	{
		smc += lef;
		return smc <= tot / 2;
	}
	lef -= m2c * (mid - 1);
	smc += m2c * (mid - 1);
	mp[mid] += m2c;
	for (auto it = mp.rbegin(); it != mp.rend(); it++)
	{
		int v = it -> first;
		ll c = it -> second;
		if (v == 2 * mid - 1) continue;
		if (lef <= (ll)(v - 1) * c)
		{
			smc += lef;
			ll use = (lef + (ll)v - 2) / (v - 1);
			smc += use;
			return smc <= tot / 2;
		}
		lef -= (ll)(v - 1) * c;
		smc += (ll)v * c;
	}
	return false;
}

void Solve()
{
	multiRead(n, m);
	int mx = 0;
	for (int i = 1; i <= n; i++) cin >> a[i], mx = max(mx, a[i]);
	int l = 1, r = mx, ans = 1;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (check(mid)) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	cout << ans << endl;
	return;
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