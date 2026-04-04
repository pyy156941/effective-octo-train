// Problem: P6240 好吃的题目
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6240
// Memory Limit: 125 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

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

struct Query
{
	int l, r, id, c;
	
	Query(int l_, int r_, int id_, int c_) : l(l_), r(r_), id(id_), c(c_) {}
};

int n, q;
int w[40001], v[40001];
int ans[200001];
int dp[40001][201];
void Calc(int l, int r, vector <Query>& qs)
{
	if (l == r)
	{
		for (auto [lb, rb, id, c] : qs)
		{
			if (c >= w[lb]) ans[id] = v[lb];
			else ans[id] = 0;
		}
		return;
	}
	int mid = (l + r) >> 1;
	for (int i = 0; i <= 200; i++) 
	{
		if (i >= w[mid]) dp[mid][i] = v[mid];
		else dp[mid][i] = 0;
		if (i >= w[mid + 1]) dp[mid + 1][i] = v[mid + 1];
		else dp[mid + 1][i] = 0;
	}
	for (int i = mid - 1; i >= l; i--)
	{
		for (int j = 0; j <= 200; j++)
		{
			dp[i][j] = dp[i + 1][j];
			if (j >= w[i]) dp[i][j] = max(dp[i][j], dp[i + 1][j - w[i]] + v[i]);
		}
	}
	for (int i = mid + 2; i <= r; i++)
	{
		for (int j = 0; j <= 200; j++)
		{
			dp[i][j] = dp[i - 1][j];
			if (j >= w[i]) dp[i][j] = max(dp[i][j], dp[i - 1][j - w[i]] + v[i]);
		}
	}
	vector <Query> lh, rh;
	for (auto [lb, rb, id, c] : qs)
	{
		// cerr << l << ' ' << r << ' ' << lb << ' ' << rb << endl;
		if (rb < mid) lh.pb(Query(lb, rb, id, c));
		else if (lb > mid + 1) rh.pb(Query(lb, rb, id, c));
		else if (rb == mid) ans[id] = dp[lb][c];
		else if (lb == mid + 1) ans[id] = dp[rb][c];
		else for (int i = 0; i <= c; i++) ans[id] = max(ans[id], dp[lb][i] + dp[rb][c - i]);
	}
	if (lh.size()) Calc(l, mid, lh);
	if (rh.size()) Calc(mid + 1, r, rh);
	return;
}

void Solve()
{
	readInt(n), readInt(q);
	for (int i = 1; i <= n; i++) readInt(w[i]);
	for (int i = 1; i <= n; i++) readInt(v[i]);
	int l, r, c;
	vector <Query> all;
	for (int i = 1; i <= q; i++)
	{
		readInt(l), readInt(r), readInt(c);
		all.pb(Query(l, r, i, c));
	}
	Calc(1, n, all);
	for (int i = 1; i <= q; i++) writeInt(ans[i]), putchar('\n');
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