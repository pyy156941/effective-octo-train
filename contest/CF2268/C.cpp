// Problem: C. KiaKio and Energy Intervals
// Contest: Codeforces - Codeforces Round 1124 (Div. 1)
// URL: https://codeforces.com/contest/2268/problem/C
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

constexpr ll N = 5.0e6;
struct trie
{
	int nxt[N][2], id[N];
	int nc = 0;
	
	void insert(int x, int p)
	{
		int cur = 0;
		for (int i = 17; i >= 0; i--)
		{
			int to = !!(x & (1 << i));
			if (!nxt[cur][to]) nxt[cur][to] = ++nc;
			cur = nxt[cur][to];
		}
		id[cur] = p;
	}
	
	void reset()
	{
		for (int i = 0; i <= nc; i++) nxt[i][0] = nxt[i][1] = id[i] = 0;
		nc = 0;
	}
	
	int find(int x)
	{
		int cur = 0;
		for (int i = 17; i >= 0; i--)
		{
			int to = !!(x & (1 << i));
			if (!nxt[cur][1 - to]) cur = nxt[cur][to];
			else cur = nxt[cur][1 - to];
		}
		return id[cur];
	}
}t;

int n, a[200001], ta[200001], pre[200001];
int st[20][200001], rn[200001];
void init_st()
{
	rn[0] = rn[1] = 0;
	rn[2] = 1;
	for (int i = 3; i <= n; i++) rn[i] = rn[i / 2] + 1;
	for (int i = 1; i <= n; i++) st[0][i] = i;
	for (int b = 1; b < 20; b++)
	{
		for (int i = 1; i <= n; i++)
		{
			int c1 = st[b - 1][i];
			if (i + (1 << (b - 1)) <= n)
			{
				int c2 = st[b - 1][i + (1 << (b - 1))];
				if (a[c1] > a[c2]) st[b][i] = c1;
				else st[b][i] = c2;
			}
			else st[b][i] = c1;
		}
	}
}

int query(int l, int r)
{
	int s = rn[r - l + 1];
	int c1 = st[s][l];
	int c2 = st[s][r - (1 << s) + 1];
	if (a[c1] > a[c2]) return c1;
	else return c2;
}

int ans = 0;
void solve(int l, int r)
{
	if (l == r) return;
	int p = query(l, r);
	if (a[p] <= ans) return;
	t.reset();
	for (int i = l; i <= r; i++) ta[i] = a[p] & a[i];
	pre[l - 1] = 0;
	for (int i = l; i <= r; i++) pre[i] = pre[i - 1] ^ ta[i];
	for (int i = l - 1; i < p - 1; i++) t.insert(pre[i], i);
	if (p > l) ans = max(ans, pre[p] ^ pre[t.find(pre[p])]);
	t.insert(pre[p - 1], p - 1);
	for (int i = p + 1; i <= r; i++) ans = max(ans, pre[i] ^ pre[t.find(pre[i])]);
	if (p > l) solve(l, p - 1);
	if (p < r) solve(p + 1, r);
}

void solve()
{
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	init_st();
	ans = 0;
	solve(1, n);
	cout << ans << endl;
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