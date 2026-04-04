// Problem: F. Dynamic Values And Maximum Sum
// Contest: Codeforces - Codeforces Round 1087 (Div. 2)
// URL: https://codeforces.com/contest/2209/problem/F
// Memory Limit: 256 MB
// Time Limit: 5000 ms
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

int n, k;
vector <int> adj[300001];
int a[300001];
int fa[300001], dep[300001], md[300001];
pair <int, int> of[300001]; // of is maximum depth node outside i's subtree to i
pair <int, int> dson[300001]; // subtree with first / second largest md (max depth)

void dfs1(int cur)
{
	md[cur] = cur;
	for (auto it : adj[cur])
	{
		if (it == fa[cur]) continue;
		fa[it] = cur;
		dep[it] = dep[cur] + 1;
		dfs1(it);
		if (dep[md[it]] > dep[md[cur]] || (dep[md[it]] == dep[md[cur]] && md[it] < md[cur])) md[cur] = md[it];
		if (!dson[cur].first || dep[md[it]] > dep[md[dson[cur].first]] || (dep[md[it]] == dep[md[dson[cur].first]] && md[it] < md[dson[cur].first])) dson[cur].second = dson[cur].first, dson[cur].first = it;
		else if (!dson[cur].second || dep[md[it]] > dep[md[dson[cur].second]] || (dep[md[it]] == dep[md[dson[cur].second]] && md[it] < md[dson[cur].second])) dson[cur].second = it;
	}
}

ll ca[300001];
ll ans[300001];
multiset <ll> f, s;
ll curfs = 0;

void clear()
{
	f.clear(), s.clear();
	curfs = 0;
}

void maintain()
{
	while (f.size() >= k) 
	{
		s.insert(*f.begin());
		curfs -= *f.begin();
		f.erase(f.begin());
	}
	while (f.size() && s.size() && *f.begin() < *s.rbegin())
	{
		auto fb = f.begin();
		auto sr = prev(s.end());
		ll tf = *fb, ts = *sr; // fix 1: int -> ll
		curfs -= tf;
		curfs += ts;
		f.erase(fb), s.erase(sr);
		f.insert(ts), s.insert(tf);
	}
}

void del(ll x)
{
	auto fi = f.find(x);
	auto si = s.find(x);
	if (fi != f.end()) f.erase(fi), curfs -= x;
	else if (si != s.end()) s.erase(si);
	maintain();
}

void ins(ll x)
{
	curfs += x;
	f.insert(x);
	maintain();
}

void dfs2(int cur)
{
	if (cur != 1) ca[md[cur]] += (ll)a[cur];
	if (cur != 1 && adj[cur].size() == 1) 
	{
		ins(ca[cur]);
		return;
	}
	for (auto it : adj[cur])
	{
		if (it == fa[cur]) continue;
		dfs2(it);
	}
}

void dfs3(int cur)
{
	ans[cur] = curfs + (ll)a[cur];
	// cerr << cur << ' ' << curfs << ' ' << ans[cur] << ' ' << of[cur].first << ' ' << of[cur].second << endl;
	if (cur != 1)
	{
		for (auto it : adj[cur])
		{
			if (it == fa[cur]) continue;
			int nm = 0;
			if (it == dson[cur].first) nm = md[dson[cur].second]; 
			else nm = md[dson[cur].first];
			int nmd;
			if (!nm) nmd = 0;
			else nmd = dep[nm] - dep[cur];
			if (nmd < of[cur].second || (nmd == of[cur].second && nm > of[cur].first)) 
			{
				del(ca[of[cur].first]);
				ins(ca[of[cur].first] + (ll)a[cur]);
				del(ca[md[it]]);
				ins(ca[md[it]] - (ll)a[it]);
				ca[of[cur].first] += (ll)a[cur];
				ca[md[it]] -= (ll)a[it];
				of[it] = {of[cur].first, of[cur].second + 1};
				dfs3(it);
				ca[of[cur].first] -= (ll)a[cur];
				ca[md[it]] += (ll)a[it];
				del(ca[of[cur].first] + (ll)a[cur]);
				ins(ca[of[cur].first]);
				del(ca[md[it]] - (ll)a[it]);
				ins(ca[md[it]]);
			}
			else
			{
				del(ca[nm]);
				ins(ca[nm] + (ll)a[cur]);
				del(ca[md[it]]);
				ins(ca[md[it]] - (ll)a[it]);
				ca[nm] += (ll)a[cur];
				ca[md[it]] -= (ll)a[it];
				of[it] = {nm, nmd + 1};
				dfs3(it);
				ca[nm] -= (ll)a[cur];
				ca[md[it]] += (ll)a[it];
				del(ca[nm] + (ll)a[cur]);
				ins(ca[nm]);
				del(ca[md[it]] - (ll)a[it]);
				ins(ca[md[it]]);
			}
		}
	}
	else
	{
		for (auto it : adj[cur])
		{
			if (it == fa[cur]) continue;
			int nm = 0;
			if (it == dson[cur].first) nm = md[dson[cur].second]; 
			else nm = md[dson[cur].first];
			int nmd;
			if (!nm) nmd = 0;
			else nmd = dep[nm] - dep[cur];
			if (!nm)
			{
				ins((ll)a[cur]); // 1 is leaf
				del(ca[md[it]]);
				ins(ca[md[it]] - (ll)a[it]);
				ca[cur] += (ll)a[cur];
				ca[md[it]] -= (ll)a[it];
				of[it] = {1, 1};
				dfs3(it);
				ca[cur] -= (ll)a[cur];
				ca[md[it]] += (ll)a[it];
				del((ll)a[cur]);
				del(ca[md[it]] - (ll)a[it]);
				ins(ca[md[it]]);
			}
			else
			{
				del(ca[nm]);
				ins(ca[nm] + (ll)a[cur]);
				del(ca[md[it]]);
				ins(ca[md[it]] - (ll)a[it]);
				ca[nm] += (ll)a[cur];
				ca[md[it]] -= (ll)a[it];
				of[it] = {nm, nmd + 1};
				dfs3(it);
				ca[nm] -= (ll)a[cur];
				ca[md[it]] += (ll)a[it];
				del(ca[nm] + (ll)a[cur]);
				ins(ca[nm]);
				del(ca[md[it]] - (ll)a[it]);
				ins(ca[md[it]]);
			}
		}	
	}
}

void solve()
{
	multi_read(n, k);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) 
	{
		ca[i] = fa[i] = dep[i] = md[i] = 0;
		of[i] = {0, 0};
		dson[i] = {0, 0};
		adj[i].clear();
		ans[i] = (ll)a[i];
	}
	clear();
	int u, v;
	for (int i = 1; i < n; i++) 
	{
		multi_read(u, v);
		adj[u].pb(v);
		adj[v].pb(u);
	}
	dfs1(1);
	dfs2(1);
	dfs3(1);
	ll fans = 0;
	for (int i = 1; i <= n; i++) fans = max(fans, ans[i]);
	cout << fans << endl;
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