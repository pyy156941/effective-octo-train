// Problem: E. Coloring a Red Black Tree
// Contest: Codeforces - Codeforces Round 1093 (Div. 2)
// URL: https://codeforces.com/contest/2220/problem/E
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

constexpr double inf = 1e14;
double dp[200001][2];
bool h1[200001]; // has 1 in subtree
vector <int> adj[200001];
bool s[200001];
int fa[200001];

void dfs(int cur)
{
	h1[cur] = s[cur];
	int c1 = 0, cs = 0;
	double sum1 = 0;
	for (auto it : adj[cur])
	{
		if (it == fa[cur]) continue;
		fa[it] = cur;
		dfs(it);
		cs++;
		if (s[it]) c1++;
		h1[cur] |= h1[it];
		sum1 += dp[it][1];
	}
	dp[cur][0] = dp[cur][1] = sum1;
	if (!h1[cur])
	{
		dp[cur][1] += (double)(cs + 1);
		return;
	}
	if (s[cur]) return;
	vector <double> difs; // dp[it][0] - dp[it][1]
	for (auto it : adj[cur])
	{
		if (it == fa[cur]) continue;
		if (!h1[it]) continue;
		else if (s[it]) continue;
		else difs.pb(dp[it][0] - dp[it][1]);
	}
	sort(difs.begin(), difs.end());
	double ps = 0; // prefix sum of sorted difs
	dp[cur][0] += (double)(cs + 1) / max((double)c1, 1e-7);
	dp[cur][1] += (double)(cs + 1) / (c1 + 1);
	for (int i = 0; i < (int)difs.size(); i++)
	{
		ps += difs[i];
		dp[cur][0] = min(dp[cur][0], sum1 + ps + (double)(cs + 1) / (c1 + i + 1));
		dp[cur][1] = min(dp[cur][1], sum1 + ps + (double)(cs + 1) / (c1 + i + 2));
	}
	// cerr << cur << ' ' << dp[cur][0] << ' ' << dp[cur][1] << endl;
	return;
}

void solve()
{
	int n;
	string str;
	cin >> n >> str;
	for (int i = 1; i <= n; i++) s[i] = (str[i - 1] == '1' ? true : false);
	for (int i = 1; i <= n; i++) dp[i][0] = dp[i][1] = 0.0, adj[i].clear(), fa[i] = 0;
	int u, v;
	for (int i = 1; i < n; i++)
	{
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	double ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (s[i]) 
		{
			dfs(i);
			ans = dp[i][0];
			break;
		}
	}
	cout << fixed << setprecision(20) << ans << endl;
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