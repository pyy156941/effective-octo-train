// Problem: F2. Distinct GCDs (Hard Version)
// Contest: Codeforces - Codeforces Round 1067 (Div. 2)
// URL: https://codeforces.com/contest/2158/problem/F2
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

ll p3[11], p5[11], p7[11], p11[11];
int r[105];
ll use[111];
vector <int> adj[105];
int vis[105][105], reach[105];
vector <ll> ans;

void dfs(int cur)
{
	ans.pb(use[cur]);
	if (!reach[cur]) 
	{
		reach[cur] = true;
		ans.pb(use[cur]);
	}
	for (auto it : adj[cur])
	{
		if (!vis[it][cur]) 
		{
			vis[it][cur] = vis[cur][it] = true;
			dfs(it);
		}
	}
}

void solve()
{
	int n;
	for (int i = 1; i <= 103; i++)
	{
		r[i] = i * (i + 1) / 2;
		if (i % 2 == 0) r[i] -= (i / 2 - 1);
	}
	p3[0] = p5[0] = p7[0] = p11[0] = 1;
	for (int i = 1; i <= 10; i++)
	{
		p3[i] = p3[i - 1] * 3ll;
		p5[i] = p5[i - 1] * 5ll;
		p7[i] = p7[i - 1] * 7ll;
		p11[i] = p11[i - 1] * 11ll;
	}
	cin >> n;
	int lim = lower_bound(r + 1, r + 104, n - 1) - r - 1;
	if (r[lim] != n) lim++;
	for (int i = 0; i < 11; i++) 
	{
		for (int j = 0; j < 10; j++)
		{
			use[i * 10 + j + 1] = (p3[i] * p5[10 - i] * p7[j] * p11[9 - j]);
			use[i * 10 + j + 1] <<= (i + j);
		}
	}
	sort(use + 1, use + 110);
	for (int i = 1; i <= lim; i++) adj[i].clear();
	for (int i = 1; i <= lim; i++)
	{
		reach[i] = false;
		for (int j = i + 1; j <= lim; j++)
		{
			if (j != i + 1 || j % 2 || j == lim || lim % 2)
			{
				adj[i].pb(j);
				adj[j].pb(i);
			}
			vis[i][j] = vis[j][i] = false;
		}
	}
	ans.clear();
	dfs(lim);
	for (int i = 0; i < n; i++) cout << ans[i] << ' ';
	cout << endl;
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