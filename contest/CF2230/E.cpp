// Problem: E. Minimum Influence
// Contest: Codeforces - Educational Codeforces Round 190 (Rated for Div. 2)
// URL: https://codeforces.com/contest/2230/problem/E
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

bool multi_test = false;

int l2[200001];
int mp[200001][20], mc[200001][20], ms[200001][20];
int qp(int l, int r)
{
	if (l > r) return 2e6;
	int s = l2[r - l + 1];
	return min(mp[l][s], mp[r - (1 << s) + 1][s]);
}

int qc(int l, int r)
{
	if (l > r) return 2e6;
	int s = l2[r - l + 1];
	return min(mc[l][s], mc[r - (1 << s) + 1][s]);
}

int qs(int l, int r)
{
	if (l > r) return 2e6;
	int s = l2[r - l + 1];
	return min(ms[l][s], ms[r - (1 << s) + 1][s]);
}

pair <int, int> ns[200001]; 
int tp[400001], tc[400001], d[400001];
void solve()
{
	int n, m;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> ns[i].first;
	for (int i = 1; i <= n; i++) cin >> ns[i].second;
	cin >> m;
	for (int i = 1; i <= m; i++) cin >> tp[i];
	for (int i = 1; i <= m; i++) cin >> tc[i];
	for (int i = 1; i <= m; i++) cin >> d[i];
	sort(ns + 1, ns + n + 1, [] (pair <int, int> a, pair <int, int> b)
	{
		if (a.first == b.first) return a.second < b.second;
		return a.first < b.first;
	});
	vector <int> p, c, nc;
	int cp = ns[1].first, cc = ns[1].second;
	p.pb(cp), c.pb(cc), nc.pb(-cc);
	for (int i = 2; i <= n; i++)
	{
		if (ns[i].first >= cp && ns[i].second >= cc) continue;
		cp = ns[i].first, cc = ns[i].second;
		p.pb(cp), c.pb(cc), nc.pb(-cc);
	}
	n = p.size();
	for (int i = 1; i <= n; i++)
	{
		mp[i][0] = p[i - 1];
		mc[i][0] = c[i - 1];
		ms[i][0] = mp[i][0] + mc[i][0];
	}
	l2[1] = 0;
	for (int i = 2; i <= n; i++) l2[i] = l2[i / 2] + 1;
	for (int b = 1; b <= 18; b++)
	{
		for (int i = 1; i <= n; i++)
		{
			mp[i][b] = min(mp[i][b - 1], mp[min(i + (1 << (b - 1)), n)][b - 1]);
			mc[i][b] = min(mc[i][b - 1], mc[min(i + (1 << (b - 1)), n)][b - 1]);
			ms[i][b] = min(ms[i][b - 1], ms[min(i + (1 << (b - 1)), n)][b - 1]);
		}
	}
	for (int i = 1; i <= m; i++)
	{
		int tpd = tp[i] + d[i];
		int tcd = tc[i] + d[i];
		int pv[4] = {1, 0, 0, n + 1}, cv[4] = {1, 0, 0, n + 1};
		pv[1] = lower_bound(p.begin(), p.end(), tp[i]) - p.begin() + 1;
		pv[2] = lower_bound(p.begin(), p.end(), tpd) - p.begin() + 1;
		cv[2] = upper_bound(nc.begin(), nc.end(), -tc[i]) - nc.begin() + 1;
		cv[1] = upper_bound(nc.begin(), nc.end(), -tcd) - nc.begin() + 1;
		// cerr << "places: " << pv[1] << ' ' << pv[2] << ' ' << cv[1] << ' ' << cv[2] << endl;
		int ans = 1e8;
		int hp = 0, hc = 0;
		while (true)
		{
			if (hp < 2 && pv[hp + 1] == pv[hp])
			{
				hp++;
				continue;
			} 
			if (hc < 2 && cv[hc + 1] == cv[hc])
			{
				hc++;
				continue;
			}
			int l = max(pv[hp], cv[hc]), r = min(pv[hp + 1] - 1, cv[hc + 1] - 1);
			if (hp == 1 && hc == 1) ans = min(ans, qs(l, r));
			else
			{
				int cur = 0;
				if (hp == 1) cur += qp(l, r);
				else if (hp == 2) cur += tpd;
				if (hc == 0) cur += tcd;
				else if (hc == 1) cur += qc(l, r);
				ans = min(ans, cur);
			}
			// cerr << hp << ' ' << hc << ' ' << l << ' ' << r << ' ' << ans << endl;
			if (pv[hp + 1] == n + 1 && cv[hc + 1] == n + 1) break;
			if (pv[hp + 1] < cv[hc + 1]) hp++; 
			else if (pv[hp + 1] > cv[hc + 1]) hc++;
			else hc++, hp++;
		}
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