// Problem: E. Zhily and Signpost
// Contest: Codeforces - Codeforces Round 1097 (Div. 2,  Based on Zhili Cup 2026)
// URL: https://codeforces.com/contest/2224/problem/E
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

constexpr ll bound = 1000000000000000000;

int fa[500001], d[500001];
vector <int> son[500001];

ll l[500001], dis[500001], m[500001], r[500001];
bool e[500001]; // m exceeds 1e18
int to[500001]; // lowest vertex must go to

void dfs(int cur)
{
	if (!d[cur]) return;
	for (auto it : son[cur]) dis[it] = dis[cur] + l[it];
	if (e[cur])
	{
		int nxt = son[cur][r[cur] % d[cur]];
		r[nxt] = r[cur] + l[nxt];
		e[nxt] = true;
		dfs(nxt);
		to[cur] = to[nxt];
		return;
	}
	if (m[cur] % d[cur] == 0)
	{
		int nxt = son[cur][r[cur] % d[cur]];
		r[nxt] = (r[cur] + l[nxt]) % m[cur];
		m[nxt] = m[cur];
		dfs(nxt);
		to[cur] = to[nxt];
		return;
	}
	ll g = gcd(m[cur], (ll)d[cur]);
	i128 m_nxt = (i128)m[cur] * d[cur] / g;
	if (m_nxt > bound)
	{
		for (auto it : son[cur]) e[it] = true; 
		for (int i = 0; i < d[cur] / g; i++)
		{
			ll nr = m[cur] * i + r[cur];
			if (nr > bound) break;
			int nxt = son[cur][nr % d[cur]];
			r[nxt] = nr + l[nxt];
			dfs(nxt);
		}
	}
	else
	{
		for (auto it : son[cur]) m[it] = m_nxt;
		for (int i = 0; i < d[cur] / g; i++)
		{
			ll nr = m[cur] * i + r[cur];
			if (nr > bound) break;
			int nxt = son[cur][nr % d[cur]];
			r[nxt] = (nr + l[nxt]) % m[nxt];
			dfs(nxt);
		}
	}
}

int query(ll x)
{
	int cur = 1;
	ll cx = 0;
	while (d[cur])
	{
		cur = to[cur];
		if (!d[cur]) break;
		cx = x + dis[cur];
		cur = son[cur][cx % d[cur]];
	}
	return cur;
}

void solve()
{
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
	{
		fa[i] = l[i] = dis[i] = d[i] = m[i] = r[i] = 0;
		to[i] = i;
		e[i] = false;
		son[i].clear();
	}
	for (int i = 2; i <= n; i++)
	{
		cin >> fa[i];
		son[fa[i]].pb(i);
	}
	for (int i = 1; i <= n; i++) sort(son[i].begin(), son[i].end()), d[i] = son[i].size();
	for (int i = 2; i <= n; i++) cin >> l[i];
	m[1] = 1; 
	dfs(1);
	ll x;
	// for (int i = 1; i <= n; i++) cerr << i << ' ' << m[i] << ' ' << r[i] << ' ' << to[i] << endl;
	for (int i = 1; i <= q; i++) 
	{
		cin >> x;
		cout << query(x) << ' ';
	}
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