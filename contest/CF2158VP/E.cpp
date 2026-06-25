// Problem: E. Sink
// Contest: Codeforces - Codeforces Round 1067 (Div. 2)
// URL: https://codeforces.com/contest/2158/problem/E
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

int fa[400001];
bool nsink[400001];

int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
	int fx = find(x), fy = find(y);
	if (fx == fy) return;
	fa[fx] = fy;
	nsink[fy] |= nsink[fx];
	nsink[fx] = false;
}

constexpr int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};

vector <vector <int>> g, id;
int n, m, N;

int to_id(int r, int c)
{
	return id[r - 1][c - 1];
}

void solve()
{
	int q, r, c, x;
	cin >> n >> m;
	N = n * m;
	g.clear(), id.clear();
	for (int i = 1; i <= n; i++)
	{
		vector <int> row, rid;
		int v;
		for (int j = 1; j <= m; j++)
		{
			cin >> v;
			row.pb(v);
			rid.pb((i - 1) * m + j);
		}
		g.pb(row);
		id.pb(rid);
	}
	cin >> q;
	for (int i = 1; i <= N + q; i++) fa[i] = i, nsink[i] = false;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				int ai = i + dr[k], aj = j + dc[k];
				if (ai < 1 || aj < 1 || ai > n || aj > m) continue;
				if (g[ai - 1][aj - 1] < g[i - 1][j - 1]) 
				{
					nsink[to_id(i, j)] = true;
					break;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				int ai = i + dr[k], aj = j + dc[k];
				if (ai < 1 || aj < 1 || ai > n || aj > m) continue;
				if (g[i - 1][j - 1] == g[ai - 1][aj - 1]) merge(to_id(i, j), to_id(ai, aj));
			}
		}
	}
	int ans = 0, cur = N;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (!nsink[to_id(i, j)] && find(to_id(i, j)) == to_id(i, j)) ans++; // non-sink tag applies to only roots
		}
	}
	cout << ans << endl;
	for (int i = 1; i <= q; i++)
	{
		cin >> r >> c >> x;
		g[r - 1][c - 1] -= x;
		int nv = g[r - 1][c - 1];
		if (!nsink[find(to_id(r, c))]) nsink[find(to_id(r, c))] = true, ans--; // delete sink from old value
		id[r - 1][c - 1] = ++cur; // nsink of new node is false (it is root)
		for (int k = 0; k < 4; k++)
		{
			int ar = r + dr[k], ac = c + dc[k];
			if (ar < 1 || ac < 1 || ar > n || ac > m) continue;
			if (g[ar - 1][ac - 1] < nv) 
			{
				nsink[to_id(r, c)] = true;
				break;
			}
		}
		for (int k = 0; k < 4; k++)
		{
			int ar = r + dr[k], ac = c + dc[k];
			if (ar < 1 || ac < 1 || ar > n || ac > m) continue;
			if (g[ar - 1][ac - 1] < nv) continue;
			else if (g[ar - 1][ac - 1] == nv)
			{
				int af = find(to_id(ar, ac));
				if (af == find(to_id(r, c))) continue; // dont merge multiple times
				if (!nsink[af]) ans--;
				merge(to_id(r, c), to_id(ar, ac)); // (r, c) is merged into (ar, ac)
			}
			else 
			{
				int af = find(to_id(ar, ac));
				if (!nsink[af]) nsink[af] = true, ans--;
			}
		}
		// cerr << nsink[find(to_id(r,c ))] << ' ' << ans << endl;
		if (!nsink[find(to_id(r, c))]) ans++; // update (r, c) here in case it is never merged
		cout << ans << endl;
	}
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