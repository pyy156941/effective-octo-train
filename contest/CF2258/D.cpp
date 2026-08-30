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

struct seq
{
	vector <ll> val;
	
	seq(vector <ll> _val) : val(_val) {}
	
	bool operator < (const seq a) const
	{
		for (int i = 0; i < max(val.size(), a.val.size()); i++)
		{
			if (i >= val.size()) return true;
			if (i >= a.val.size()) return false;
			if (val[i] < a.val[i]) return true;
			if (val[i] > a.val[i]) return false;
		}
		return false;
	}
};

seq add(seq a, ll ext)
{
	auto it = lower_bound(a.val.begin(), a.val.end(), ext, greater <ll> ());
	a.val.insert(it, ext);
	return a;
}

bool cmp(pair <pair <ll, ll>, bool> a, pair <pair <ll, ll>, bool> b)
{
	return a.first.first < b.first.first;
}

vector <ll> cords;
ll le[12000];
void solve()
{
	ll il, ir;
	cin >> n >> m;
	sl.clear();
	sr.clear();
	sl.reserve(n);
	sr.reserve(m);
	cords.clear();
	for (int i = 1; i <= n; i++) 
	{
		cin >> il >> ir;
		il--;
		sl.pb({il, ir});
	}
	for (int i = 1; i <= m; i++) 
	{
		cin >> il >> ir;
		il--;
		sr.pb({il, ir});
	}
	vector <pair <ll, ll>> nsl, nsr;
	for (auto [l, r] : sl)
	{
		bool ok = true;
		for (auto [nl, nr] : sr)
		{
			if (nl <= l && r <= nr)
			{
				ok = false;
				break;
			}
		}
		if (ok) nsl.pb({l, r});
	}
	sl = move(nsl);
	for (auto [l, r] : sr)
	{
		bool ok = true;
		for (auto [nl, nr] : sl)
		{
			if (nl <= l && r <= nr)
			{
				ok = false;
				break;
			}
		}
		if (ok) nsr.pb({l, r});
	}
	sr = move(nsr);
	for (auto [l, r] : sl) cords.pb(l), cords.pb(r);
	for (auto [l, r] : sr) cords.pb(l), cords.pb(r);
	sort(cords.begin(), cords.end());
	cords.erase(unique(cords.begin(), cords.end()), cords.end());
	for (int i = 0; i < cords.size(); i++) le[i] = 12000;
	for (auto &[l, r] : sl) 
	{
		l = lower_bound(cords.begin(), cords.end(), l) - cords.begin();
		r = lower_bound(cords.begin(), cords.end(), r) - cords.begin();
		for (int i = l + 1; i <= r; i++) le[i] = min(le[i], l);
	}
	for (auto &[l, r] : sr) 
	{
		l = lower_bound(cords.begin(), cords.end(), l) - cords.begin();
		r = lower_bound(cords.begin(), cords.end(), r) - cords.begin();
		for (int i = l + 1; i <= r; i++) le[i] = min(le[i], l);
	}
	vector <seq> dp;
	vector <pair <pair <ll, ll>, bool>> seg;
	for (auto [l, r] : sl) seg.pb({{l, r}, false});
	for (auto [l, r] : sr) seg.pb({{l, r}, true});
	sort(seg.begin(), seg.end(), cmp);
	int ps = 0;
	for (int i = 0; i < cords.size(); i++)
	{
		if (le[i] == 12000) 
		{
			if (!i) dp.pb(seq({}));
			else dp.pb(dp.back());
			continue;
		}
		auto cur = seq({});
		if (i) cur = dp.back();
		for (int j = le[i]; j < i; j++)
		{
			auto cand = add(dp[j], cords[i] - cords[j]);
			if (cur < cand) cur = cand;
		}
		dp.pb(cur);
	}
	auto ans = dp.back().val;
	cout << ans.size() << endl;
	sort(ans.begin(), ans.end(), greater <ll> ());
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