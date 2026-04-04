// Problem: C - Strong Surname
// Contest: AtCoder - AtCoder Regular Contest 215
// URL: https://atcoder.jp/contests/arc215/tasks/arc215_c
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

struct p
{
	int x, y, z;
	
	bool operator < (const p _) const
	{
		return x > _.x;
	}
}a[200001];

bool vis[200001];
vector <int> xv[200001], yv[200001], zv[200001];
void Solve()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) vis[i] = false, xv[i].clear(), yv[i].clear(), zv[i].clear();
	for (int i = 1; i <= n; i++) 
	{
		multiRead(a[i].x, a[i].y, a[i].z);
		xv[a[i].x].pb(i);
		yv[a[i].y].pb(i);
		zv[a[i].z].pb(i);
	}
	queue <int> Q;
	int mx = 0, my = 0, mz = 0;
	for (int i = n; i >= 1; i--)
	{
		if (xv[i].size())
		{
			for (auto it : xv[i]) 
			{
				if (!vis[it])
				{
					Q.push(it);
					vis[it] = true;
				}
			}
			mx = i - 1;
			break;
		} 
	}
	for (int i = n; i >= 1; i--)
	{
		if (yv[i].size())
		{
			for (auto it : yv[i]) 
			{
				if (!vis[it])
				{
					Q.push(it);
					vis[it] = true;
				}
			}
			my = i - 1;
			break;
		} 
	}
	for (int i = n; i >= 1; i--)
	{
		if (zv[i].size())
		{
			for (auto it : zv[i]) 
			{
				if (!vis[it])
				{
					Q.push(it);
					vis[it] = true;
				}
			}
			mz = i - 1;
			break;
		} 
	}
	while (!Q.empty())
	{
		int cur = Q.front();
		Q.pop();
		int cx = a[cur].x, cy = a[cur].y, cz = a[cur].z;
		for (int i = cx; i <= mx; i++) 
		{
			for (auto it : xv[i])
			{
				if (!vis[it])
				{
					Q.push(it);
					vis[it] = true;
				}
			}
		}
		mx = min(mx, cx - 1);
		for (int i = cy; i <= my; i++) 
		{
			for (auto it : yv[i])
			{
				if (!vis[it])
				{
					Q.push(it);
					vis[it] = true;
				}
			}
		}
		my = min(my, cy - 1);
		for (int i = cz; i <= mz; i++) 
		{
			for (auto it : zv[i])
			{
				if (!vis[it])
				{
					Q.push(it);
					vis[it] = true;
				}
			}
		}
		mz = min(mz, cz - 1);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) if (vis[i]) ans++;
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