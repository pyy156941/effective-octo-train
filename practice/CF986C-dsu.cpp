// Problem: C. AND Graph
// Contest: Codeforces - Codeforces Round 485 (Div. 1)
// URL: https://codeforces.com/contest/986/problem/C
// Memory Limit: 256 MB
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

bool multiTest = false;

int a[4194305], fullmask;
int fa[4194305], siz[4194305];
int inv[4194305];
bool vis[4194305]; // exists some a[i] is as a subset of the index 
int ind[4194305]; // i that a[i] equal to index

void clear(int n)
{
	for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
}

int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
	int fx = find(x), fy = find(y);
	if (fx == fy) return;
	if (siz[fx] > siz[fy]) swap(fx, fy);
	siz[fy] += siz[fx];
	fa[fx] = fy;
}

void Solve()
{
	int n, m;
	multiRead(n, m);
	fullmask = (1 << n) - 1;
	clear(m);
	for (int i = 0; i <= fullmask; i++) vis[i] = false, ind[i] = 0;  
	for (int i = 1; i <= m; i++) cin >> a[i], vis[a[i]] = true, ind[a[i]] = i, inv[fullmask ^ a[i]] = i;
	for (int i = 0; i <= fullmask; i++)
	{
		for (int j = 0; j < n; j++) if (i & (1 << j)) vis[i] |= vis[i ^ (1 << j)];
	}
	for (int i = fullmask; i >= 0; i--)
	{
		if (inv[i] && ind[i]) merge(inv[i], ind[i]);
		if (!vis[i]) continue; // no a[i] as a subset of i, no new connection in any subset of i
		if (!inv[i]) continue; // nothing to update to subsets of i
		for (int j = 0; j < n; j++) 
		{
			if (i & (1 << j))
			{
				int mask = i ^ (1 << j);
				if (inv[mask] && vis[mask]) merge(inv[mask], inv[i]); // inv[mask] and inv[i] are connected through an a[i] in the subset of mask, as vis[mask] is true
				else inv[mask] = inv[i]; // if vis[mask] is false, then we will not process mask, no matter what it is
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= m; i++) if (fa[i] == i) ans++;
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