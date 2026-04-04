// Problem: H. Remove the Grail Tree
// Contest: Codeforces - Codeforces Round 1076 (Div. 3)
// URL: https://codeforces.com/contest/2193/problem/H
// Memory Limit: 256 MB
// Time Limit: 3000 ms
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

bool a[200001], dp[200001][2];
int fa[200001];
vector <int> adj[200001], ans[200001][2];

void DFS1(int cur)
{
	if (adj[cur].size() == 1 && adj[cur][0] == fa[cur])
	{
		ans[cur][0].pb(cur);
		ans[cur][1].pb(cur);
		dp[cur][!a[cur]] = true;
		dp[cur][a[cur]] = false;
		return;
	}
	vector <int> must0, must1, both;
	int sum_of_child = 0;
	for (auto it : adj[cur])
	{
		if (it == fa[cur]) continue;
		fa[it] = cur;
		sum_of_child += a[it];
		DFS1(it);
		if (!dp[it][0] && !dp[it][1]) 
		{
			dp[cur][0] = dp[cur][1] = false;
			return;
		}
		if (a[cur])
		{
			if (dp[it][0] && dp[it][1]) both.pb(it);
			else if (dp[it][0]) must0.pb(it);
			else must1.pb(it); // automatic exclusive
		}
		else
		{
			if (!dp[it][0])
			{
				dp[cur][0] = dp[cur][1] = false;
				return;
			}
			must0.pb(it); // could be both, but we can't turn a[cur] to 1, so don't matter
		}
	}
	bool cur_placed_0 = false, cur_placed_1 = false;
	if (a[cur])
	{
		for (auto it : must1) 
		{
			ans[cur][0].pb(it);
			ans[cur][1].pb(it);
			sum_of_child -= a[it];
		}
		if (sum_of_child % 2 == 0) cur_placed_0 = true, ans[cur][0].pb(cur), dp[cur][0] = true;
		else cur_placed_1 = true, ans[cur][1].pb(cur), dp[cur][1] = true;
		for (auto it : both)
		{
			ans[cur][0].pb(it);
			ans[cur][1].pb(it);
			sum_of_child -= a[it];
			if (!cur_placed_0 && sum_of_child % 2 == 0)
			{
				cur_placed_0 = true;
				ans[cur][0].pb(cur);
				dp[cur][0] = true;
			}
			if (!cur_placed_1 && sum_of_child % 2)
			{
				cur_placed_1 = true;
				ans[cur][1].pb(cur);
				dp[cur][1] = true;
			}
		}
		for (auto it : must0)
		{
			ans[cur][0].pb(it);
			ans[cur][1].pb(it);
		}
	}
	else
	{
		if (sum_of_child % 2) cur_placed_0 = true, ans[cur][0].pb(cur), dp[cur][0] = true;
		else cur_placed_1 = true, ans[cur][1].pb(cur), dp[cur][1] = true;
		for (auto it : must0)
		{
			ans[cur][0].pb(it);
			ans[cur][1].pb(it);
			sum_of_child -= a[it];
			if (!cur_placed_0 && sum_of_child % 2)
			{
				cur_placed_0 = true;
				ans[cur][0].pb(cur);
				dp[cur][0] = true;
			}
			if (!cur_placed_1 && sum_of_child % 2 == 0)
			{
				cur_placed_1 = true;
				ans[cur][1].pb(cur);
				dp[cur][1] = true;
			}
		}
	}
}

void DFS2(int cur, bool cura) // output answer
{
	bool cur_used = false;
	for (auto it : ans[cur][cura]) 
	{
		if (it == cur) cout << cur << ' ', cur_used = true;
		else 
		{
			if (cur_used && a[cur]) DFS2(it, !a[cur]);
			else DFS2(it, a[cur]);
		}
	}
}

void Solve()
{
	int n, u, v;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> v, a[i] = (v % 2 ? true : false);
	for (int i = 1; i <= n; i++) dp[i][0] = dp[i][1] = false, fa[i] = 0, adj[i].clear(), ans[i][0].clear(), ans[i][1].clear();
	for (int i = 1; i < n; i++)
	{
		multiRead(u, v);
		adj[u].pb(v);
		adj[v].pb(u);
	}
	DFS1(1);
	// for (int i = 1; i <= n; i++) cerr << dp[i][0] << ' ' << dp[i][1] << endl;
	// for (int i = 1; i <= n; i++) 
	// {
		// cerr << "ans " << i << " 0:" << endl;
		// for (auto it : ans[i][0]) cerr << it << ' ';
		// cerr << endl;
	// }
	// cerr << endl;
	// for (int i = 1; i <= n; i++) 
	// {
		// cerr << "ans " << i << " 1:" << endl;
		// for (auto it : ans[i][1]) cerr << it << ' ';
		// cerr << endl;
	// }
	if (dp[1][0]) 
	{
		cout << "YES" << endl;
		DFS2(1, 0);
		cout << endl;
	}
	else cout << "NO" << endl;
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