// Problem: D. Path Split
// Contest: Codeforces - Codeforces Round 1064 (Div. 1)
// URL: https://codeforces.com/contest/2165/problem/D
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

set <int> plf[2000001], pls[2000001];
vector <int> pl[2000001];
bool ocf[1000001], ocs[1000001];
void solve()
{
	int n, a;
	cin >> n;
	for (int i = 1; i <= 2 * n; i++) pl[i].clear(), plf[i].clear(), pls[i].clear();
	for (int i = 1; i <= n; i++) ocf[i] = ocs[i] = false;
	for (int i = 1; i <= n; i++) 
	{
		cin >> a;
		pl[a].pb(i);
		plf[a].insert(i);
		pls[a].insert(i);
	}
	int ans = n;
	for (int i = 1; i < 2 * n; i++)
	{
		for (auto p : pl[i])
		{
			if (!(plf[i + 1].size() + pls[i + 1].size())) break;
			if (!ocf[p] && pls[i + 1].size()) 
			{
				auto it = pls[i + 1].lower_bound(p);
				// cerr << i << ' ' << p << ' ' << *it << endl;
				if (it != pls[i + 1].begin()) 
				{
					auto it2 = prev(it);
					ans--;
					ocs[*it2] = true;
					ocf[p] = true; 
					pls[i + 1].erase(it2);
					plf[i].erase(plf[i].find(p));
				}
			}
			if (!ocs[p] && plf[i + 1].size())
			{
				auto it = plf[i + 1].lower_bound(p);
				// cerr << i << ' ' << p << ' ' << *it << endl;
				if (it != plf[i + 1].end())
				{
					ans--;
					ocs[p] = true;
					ocf[*it] = true;
					pls[i].erase(pls[i].find(p));
					plf[i + 1].erase(it);
				}
			}
		}
		// cerr << i << ' ' << ans << endl;
	}
	cout << ans << endl;
	return;
}
/*
hack1:
5
5 3 4 2 1
hack2:
5
1 2 3 4 3
*/

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr);
	int _ = 1;
	if (multi_test) cin >> _;
	while (_--) solve();
	return 0;
}