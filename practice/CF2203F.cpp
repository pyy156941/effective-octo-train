// Problem: F. Binary Search with One Swap
// Contest: Codeforces - Educational Codeforces Round 187 (Rated for Div. 2)
// URL: https://codeforces.com/contest/2203/problem/F
// Memory Limit: 512 MB
// Time Limit: 1500 ms
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

bool multiTest = false;

int n;
ll ans[5000001];
void DFS1(int l, int r)
{
	if (l > r) return;
	int mid = (l + r) >> 1;
	int lsz = mid - l, rsz = r - mid;
	ans[n] -= 2;
	ans[n - lsz]++;
	ans[n - rsz]++;
	DFS1(l, mid - 1);
	DFS1(mid + 1, r);
}

pair <unordered_map <int, int>, unordered_map <int, int>> DFS2(int l, int r, int mult)
{
	if (l > r) 
	{
		unordered_map <int, int> lef, rig;
		return {lef, rig};
	}
	int mid = (l + r) >> 1;
	if (mid - l == r - mid)
	{	
		auto [lef, rig] = DFS2(l, mid - 1, mult * 2);
		for (auto [v, c] : lef)
		{
			lef[v] += c;
			for (auto [vl, cl] : rig) 
			{
				ans[n - v - vl - 2] += (ll)c * cl * mult;
			}
		}
		for (auto [v, c] : rig) rig[v] += c;
		lef[mid - l]++;
		rig[r - mid]++;
		return {lef, rig};
	}
	else
	{
		auto [lef, rig] = DFS2(l, mid - 1, mult);
		auto [lefr, rigr] = DFS2(mid + 1, r, mult);
		for (auto [v, c] : lefr)
		{
			lef[v] += c;
			for (auto [vl, cl] : rig) 
			{
				ans[n - v - vl - 2] += (ll)c * cl * mult;
			}
		}
		for (auto [v, c] : rigr) rig[v] += c;
		lef[mid - l]++;
		rig[r - mid]++;
		return {lef, rig};
	}
}

void Solve()
{
	cin >> n;
	DFS1(1, n);
	for (int i = 1; i <= n; i++) ans[i] += ans[i - 1];
	DFS2(1, n, 1);
	for (int i = 0; i <= n; i++) cout << ans[i] << ' ';
	cout << endl;
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