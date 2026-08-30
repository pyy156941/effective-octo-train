// Problem: D. Magic Tiles
// Contest: Codeforces - Codeforces Round 1118 (Div. 2)
// URL: https://codeforces.com/contest/2258/problem/D
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

int n, m;
vector <pair <ll, ll>> sl, sr;
vector <pair <pair <ll, ll>, int>> dmp, sel;
vector <ll> tdmpl, tdmpr;
void solve()
{
	ll il, ir;
	cin >> n >> m;
	sl.clear();
	sr.clear();
	sl.reserve(n);
	sr.reserve(m);
	for (int i = 1; i <= n; i++) cin >> il >> ir, sl.pb({il, ir});
	for (int i = 1; i <= m; i++) cin >> il >> ir, sr.pb({il, ir});
	vector <ll> ans;
	while (sl.size() || sr.size())
	{
		dmp.clear();
		sel.clear();
		tdmpl.clear();
		tdmpr.clear();
		ll ml = 0;
		for (auto [l, r] : sl) ml = max(ml, r - l + 1);
		for (auto [l, r] : sr) ml = max(ml, r - l + 1);
		for (auto [l, r] : sl) if (r - l + 1 == ml) tdmpl.pb(l);
		for (auto [l, r] : sr) if (r - l + 1 == ml) tdmpr.pb(l);
		int pl = 0, pr = 0;
		while (pl < tdmpl.size() && pr < tdmpr.size())
		{
		    if (tdmpl[pl] <= tdmpr[pr])
		    {
		        dmp.pb({{tdmpl[pl], tdmpl[pl] + ml - 1}, 0});
		        pl++;
		    }
		    else
		    {
		        dmp.pb({{tdmpr[pr], tdmpr[pr] + ml - 1}, 1});
		        pr++;
		    }
		}
		while (pl < tdmpl.size())
		{
		    dmp.pb({{tdmpl[pl], tdmpl[pl] + ml - 1}, 0});
		    pl++;
		}
		while (pr < tdmpr.size())
		{
		    dmp.pb({{tdmpr[pr], tdmpr[pr] + ml - 1}, 1});
		    pr++;
		}
		bool chosen = false;
		for (auto x : dmp)
		{
			auto seg = x.first;
			auto type = x.second;
			if (!chosen) 
			{
				chosen = true;
				sel.pb({seg, type});
			}
			else
			{
				auto lst = sel.back();
				auto segl = lst.first;
				auto typel = lst.second;
				if (type != typel && segl.second >= seg.first) chosen = false;
				else sel.pb({seg, type});
			}
		}
		for (int i = 0; i < sel.size(); i++) ans.pb(ml);
		int ps = 0;
		vector <pair <ll, ll>> nsl, nsr;
		for (auto [l, r] : sl)
		{
			while (ps < sel.size() && sel[ps].first.second < l) ps++;
			if (ps >= sel.size()) 
			{
				nsl.pb({l, r});
				continue;
			}
			auto cur = sel[ps];
			ll nl = cur.first.first, nr = cur.first.second;
			bool nt = cur.second;
			if (!nt) 
			{
				if (nl == l && nr == r) continue;
				else nsl.pb({l, r});
			}
			else 
			{
				if (nr >= r)
				{
					if (nl <= l) continue;
					else if (nl <= r) nsl.pb({l, nl - 1});
					else nsl.pb({l, r});
				}
				else
				{
					ll rr = nr + 1;
					ps++;
					if (ps >= sel.size()) 
					{
						nsl.pb({rr, r});
						continue;
					}
					cur = sel[ps];
					nl = cur.first.first, nr = cur.first.second;
					nt = cur.second;
					if (nl <= r) nsl.pb({rr, nl - 1});
					else if (nl == l && nr == r && !nt) continue;
					else nsl.pb({rr, r});
				}
			}
		}
		ps = 0;
		for (auto [l, r] : sr)
		{
			while (ps < sel.size() && sel[ps].first.second < l) ps++;
			if (ps >= sel.size()) 
			{
				nsr.pb({l, r});
				continue;
			}
			auto cur = sel[ps];
			ll nl = cur.first.first, nr = cur.first.second;
			bool nt = cur.second;
			if (nt) 
			{
				if (nl == l && nr == r) continue;
				else nsr.pb({l, r});
			}
			else 
			{
				if (nr >= r)
				{
					if (nl <= l) continue;
					else if (nl <= r) nsr.pb({l, nl - 1});
					else nsr.pb({l, r});
				}
				else
				{
					ll rr = nr + 1;
					ps++;
					if (ps >= sel.size()) 
					{
						nsr.pb({rr, r});
						continue;
					}
					cur = sel[ps];
					nl = cur.first.first, nr = cur.first.second;
					nt = cur.second;
					if (nl <= r) nsr.pb({rr, nl - 1});
					else if (nl == l && nr == r && nt) continue;
					else nsr.pb({rr, r});
				}
			}
		}
		sl = move(nsl);
		sr = move(nsr);
		// for (auto [seg, _] : sel) cerr << seg.first << ' ' << seg.second << ' ' << _ << endl;
		// cerr << "SL: \n";
		// for (auto [l, r] : sl) cerr << l << ' ' << r << endl;
		// cerr << "SR: \n";
		// for (auto [l, r] : sr) cerr << l << ' ' << r << endl;
	}
	cout << ans.size() << endl;
	for (auto x : ans) cout << x << ' ';
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