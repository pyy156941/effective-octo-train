// Problem: F. Simons and Reconstructing His Roads
// Contest: Codeforces - Codeforces Round 1083 (Div. 2)
// URL: https://codeforces.com/contest/2205/problem/F
// Memory Limit: 512 MB
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

int n, m;
int fa[400001];
ll val[400001];
vector <vector <int>> w, v; 

int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
	int fx = find(x), fy = find(y);
	if (fx == fy) return;
	if (fx < fy) swap(fx, fy);
	fa[fx] = fy;
	val[fy] += val[fx];
}

int get_id(int x, int y)
{
	return (x - 1) * (m - 1) + y;
}

void solve()
{
	cin >> n >> m;
	w.clear(), v.clear();
	for (int i = 0; i <= (n - 1) * (m - 1); i++) fa[i] = i, val[i] = 0;
	for (int i = 1; i < n; i++)
	{
		vector <int> t;
		int x;
		for (int j = 1; j <= m; j++)
		{
			cin >> x;
			t.pb(x);
		}
		w.pb(t);
	}
	for (int i = 1; i <= n; i++)
	{
		vector <int> t;
		int x;
		for (int j = 1; j < m; j++)
		{
			cin >> x;
			t.pb(x);
		}
		v.pb(t);
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < m; j++)
		{
			val[get_id(i, j)] = (ll)w[i - 1][j - 1] + v[i - 1][j - 1] - w[i - 1][j] - v[i][j - 1];
		}
	}
	string s;
	for (int i = 1; i < n; i++)
	{
		cin >> s;
		if (s[0] == '0') merge(get_id(i, 1), 0);
		if (s[m - 1] == '0') merge(get_id(i, m - 1), 0);
		for (int j = 2; j < m; j++) if (s[j - 1] == '0') merge(get_id(i, j - 1), get_id(i, j));
	}
	for (int i = 1; i <= n; i++)
	{
		cin >> s;
		if (i == 1)
		{
			for (int j = 1; j < m; j++) if (s[j - 1] == '0') merge(get_id(1, j), 0);
		}
		else if (i == n)
		{
			for (int j = 1; j < m; j++) if (s[j - 1] == '0') merge(get_id(i - 1, j), 0);
		}
		else
		{
			for (int j = 1; j < m; j++) if (s[j - 1] == '0') merge(get_id(i - 1, j), get_id(i, j));
		}
	}
	ll ans = 0;
	for (int i = 1; i <= (n - 1) * (m - 1); i++) if (find(i) == i) ans += max(val[i], 0ll); 
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