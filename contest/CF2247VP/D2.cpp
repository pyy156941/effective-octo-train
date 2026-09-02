// Problem: D2. XOR Sorting (Hard Version)
// Contest: Codeforces - Codeforces Round 1111 (Div. 2)
// URL: https://codeforces.com/contest/2247/problem/D2
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

constexpr int thres = 2;

int a[1000000], wc[21];
void solve()
{
	int n, q, p, x;
	cin >> n >> q;
	for (int i = 0; i < n; i++) cin >> a[i];
	vector <int> lst[21];
	vector <multiset <int>> ss[21];
	for (int i = 0; i < 21; i++)
	{
		int blk = 1 << i;
		if (blk > n) break;
		ss[i].clear();
		lst[i].clear();
		for (int l = 0; l < n; l += blk)
		{
			int r = min(l + blk, n);
			multiset <int> s;
			int mn = 1e9 + 1, mx = 0;
			for (int j = l; j < r; j++) 
			{
				if (i > thres) s.insert(a[j]);
				mn = min(mn, a[j]);
				mx = max(mx, a[j]);
			}
			lst[i].pb(mn);
			lst[i].pb(mx);
			if (i > thres) ss[i].pb(s);
		}
		lst[i].pb(1e9 + 1);
		wc[i] = 0;
		for (int j = 1; j < lst[i].size(); j++) if (lst[i][j] < lst[i][j - 1]) wc[i]++;
	}
	int ans = 0;
	for (int i = 20; i >= 0; i--)
	{
		if ((1 << i) >= n * 2) continue;
		if (wc[i])
		{
			ans = (1 << i);
			break;
		}
	}
	cout << ans << endl;
	for (int _ = 1; _ <= q; _++)
	{
		cin >> p >> x;
		int rap = a[p];
		a[p] = x;
		ans = 0;
		for (int i = 20; i >= 0; i--)
		{
			int blk = 1 << i;
			if (blk > n) continue;
			int id = p / blk;
			int l = id * blk;
			int r = min(l + blk, n);
			if (id > 0 && lst[i][id * 2] < lst[i][id * 2 - 1]) wc[i]--;
			if (lst[i][id * 2 + 1] < lst[i][id * 2]) wc[i]--;
			if (lst[i][id * 2 + 2] < lst[i][id * 2 + 1]) wc[i]--;
			if (i > thres) 
			{
				ss[i][id].erase(ss[i][id].find(rap));
				ss[i][id].insert(a[p]);
				lst[i][id * 2] = *ss[i][id].begin();
				lst[i][id * 2 + 1] = *(--ss[i][id].end());
			}
			else
			{
				int mn = 1e9 + 1, mx = 0;
				for (int j = l; j < r; j++) 
				{
					mn = min(mn, a[j]);
					mx = max(mx, a[j]);
				}
				lst[i][id * 2] = mn;
				lst[i][id * 2 + 1] = mx;
			}
			if (id > 0 && lst[i][id * 2] < lst[i][id * 2 - 1]) wc[i]++;
			if (lst[i][id * 2 + 1] < lst[i][id * 2]) wc[i]++;
			if (lst[i][id * 2 + 2] < lst[i][id * 2 + 1]) wc[i]++;
		}
		for (int i = 20; i >= 0; i--)
		{
			if ((1 << i) > n) continue;
			if (wc[i])
			{
				ans = (1 << i);
				break;
			}
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