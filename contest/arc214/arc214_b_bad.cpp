// Problem: B - Missing Number in Graph
// Contest: AtCoder - AtCoder Regular Contest 214
// URL: https://atcoder.jp/contests/arc214/tasks/arc214_b
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

bool multiTest = true;

vector <pair <int, int>> adj[200001];
int val[200001], cal[32], h[32];
bool vis[200001];

void Solve()
{
	int n, m;
	multiRead(n, m);
	for (int i = 1; i <= n; i++) adj[i].clear(), val[i] = -1, vis[i] = false;
	vis[0] = false;
	int a, b, x;
	for (int i = 1; i <= m; i++) 
	{
		multiRead(a, b, x);
		adj[a].pb({b, x});
		adj[b].pb({a, x});
	}
	if (n % 2)
	{
		cout << "-1\n";
		return;
	}
	val[1] = n;
	for (int i = 0; i <= 20; i++) cal[i] = 0, h[i] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= 20; j++) 
		{
			if (i & (1 << j)) cal[j]++;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (val[i] != -1)
		{
			for (auto [to, x] : adj[i]) val[to] = x ^ val[i];
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= 20; j++)
		{
			if (val[i] & (1 << j)) h[j]++;
		}
	}
	int change = 0, change2 = 0;
	// for (int i = 1; i <= n; i++) cerr << val[i] << ' ';
	// cerr << endl;
	for (int j = 0; j <= 20; j++)
	{
		if (h[j] < cal[j] - 1 || h[j] > cal[j]) change += (1 << j), change2 += (1 << j);
		else if (1 << (j + 1) > n)
		{
			if (n - h[j] >= cal[j] - 1 && n - h[j] <= cal[j]) change2 += (1 << j);
		}
	}
	bool use_change2 = false;
	for (int i = 1; i <= n; i++) 
	{
		val[i] ^= change;
		vis[val[i]] = true;
		if (val[i] > n) use_change2 = true;
	}
	if (use_change2)
	{
		for (int i = 0; i <= n; i++) vis[i] = false;
		for (int i = 1; i <= n; i++) val[i] ^= change, val[i] ^= change2, vis[val[i]] = true;
	}
	// cerr << change << endl;
	// for (int i = 1; i <= n; i++) cerr << val[i] << ' ';
	// cerr << endl;
	for (int i = 0; i <= n; i++) 
	{
		if (!vis[i])
		{
			cout << i << endl;
			return;
		}
	}
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