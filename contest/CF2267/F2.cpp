// Problem: F2. XOR Transformations (Hard Version)
// Contest: Codeforces - Codeforces Round 1123 (Div. 2)
// URL: https://codeforces.com/contest/2267/problem/F2
// Memory Limit: 512 MB
// Time Limit: 4000 ms
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

constexpr ll N = 2.5e6;

int n, a[100001];
struct trie
{
	int nxt[N][2], siz[N];
	int nc = 0;
	
	void insert(int x)
	{
		int cur = 0;
		siz[cur]++;
		for (int i = 29; i >= 0; i--) 
		{
			int to = !!(x & (1 << i));
			if (!nxt[cur][to]) nxt[cur][to] = ++nc;
			cur = nxt[cur][to];
			siz[cur]++;
		}
	}
	
	void reset()
	{
		for (int i = 0; i <= nc; i++) nxt[i][0] = nxt[i][1] = siz[i] = 0;
		nc = 0;
	}
	
	int get_k(int x, int k)
	{
		int cur = 0, res = 0;
		for (int i = 29; i >= 0; i--)
		{
			int to = !!(x & (1 << i));
			if (!nxt[cur][to] || siz[nxt[cur][to]] < k)
			{
				if (!to) res += (1 << i);
				if (nxt[cur][to]) k -= siz[nxt[cur][to]];
				cur = nxt[cur][1 - to];
			}
			else 
			{
				if (to) res += (1 << i);
				cur = nxt[cur][to];
			}
		}
		return res;
	}
}t;

struct can
{
	int id, v;
	can (int _id, int _v) : id(_id), v(_v) {}
	
	bool operator < (const can o) const
	{
		if (v == o.v) return id < o.id;
		return v > o.v;
	}
};

int rk[100001];
void trans()
{
	t.reset();
	for (int i = 1; i <= n; i++) t.insert(a[i]);
	priority_queue <can> Q;
	for (int i = 1; i <= n; i++) rk[i] = 2, Q.push(can(i, a[i] ^ t.get_k(a[i], rk[i])));
	vector <int> na;
	// for (int i = 1; i <= n; i++)
	// {
		// cerr << a[i] << endl;
		// for (int j = 1; j <= n; j++) cerr << t.get_k(a[i], j) << ' ';
		// cerr << endl;
	// }
	for (int i = 1; i <= n * 2; i++)
	{
		auto cur = Q.top();
		int id = cur.id, v = cur.v;
		na.pb(v);
		Q.pop();
		rk[id]++;
		if (rk[id] <= n) Q.push(can(id, a[id] ^ t.get_k(a[id], rk[id])));
	}
	for (int i = 1; i <= n; i++) a[i] = na[2 * i - 2];
}

int ans[100001];
pair <int, int> qs[100001];
void solve()
{
	int q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= q; i++) cin >> qs[i].second, qs[i].first = i, ans[i] = 0;
	sort(a + 1, a + n + 1);
	sort(qs + 1, qs + q + 1, [] (pair <int, int> p1, pair <int, int> p2) { return p1.second < p2.second; });
	int p = 1;
	while (p <= q && !qs[p].second) ans[qs[p].first] = a[n] - a[1], p++;
	for (int i = 1; i <= 60; i++)
	{
		trans();
		// for (int j = 1; j <= n; j++) cerr << a[j] << ' ';
		// cerr << endl;
		if (a[n] - a[1] == 0) break;
		while (p <= q && i == qs[p].second) ans[qs[p].first] = a[n] - a[1], p++;
	}
	for (int i = 1; i <= q; i++) cout << ans[i] << endl;
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