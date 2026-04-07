// Problem: D. Flip the Bit (Hard Version)
// Contest: Codeforces - Codeforces Round 1091 (Div. 2) and CodeCraft 26
// URL: https://codeforces.com/contest/2217/problem/D
// Memory Limit: 256 MB
// Time Limit: 1500 ms
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

int a[200001], sa[200002], pa[200001], cp[200001], cs[200001];
bool f[200001];
void solve()
{
	int n, k, p;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i], f[i] = false;
	int g = 0;
	for (int i = 1; i <= k; i++) cin >> p, f[p] = true, g = a[p];
	pa[0] = sa[n + 1] = cp[0] = cs[n + 1] = 0;
	int lb = 0, rb = 0;
	bool found = false;
	int cur = 0;
	for (int i = 1; i <= n; i++)
	{
		pa[i] = pa[i - 1];
		cp[i] = cp[i - 1];
		if (f[i]) 
		{
			if (cp[i] % 2) pa[i]++, cp[i]++;
			if (!found) found = true, lb = i;
			cur = cp[i];
		}
		else
		{
			if (!cp[i]) 
			{
				if (a[i] != g) pa[i]++, cp[i]++;
			}
			else
			{
				if ((a[i] ^ (cp[i] % 2)) != g)
				{
					if (cur) cur--, cp[i]--;
					else pa[i]++, cp[i]++;
				}
			}
		}
	}
	found = false;
	cur = 0;
	for (int i = n; i >= 1; i--)
	{
		sa[i] = sa[i + 1];
		cs[i] = cs[i + 1];
		if (f[i])
		{
			if (cs[i] % 2) sa[i]++, cs[i]++;
			if (!found) found = true, rb = i;
			cur = cs[i];
		}
		else
		{
			if (!cs[i]) 
			{
				if (a[i] != g) sa[i]++, cs[i]++;
			}
			else
			{
				if ((a[i] ^ (cs[i] % 2)) != g) 
				{
					if (cur) cur--, cs[i]--;
					else sa[i]++, cs[i]++;
				}
			}
		}
	}
	int ans = 1e9;
	for (int i = lb; i <= rb; i++) 
	{
		cerr << i << ' ' << pa[i] << ' ' << cp[i] << ' ' << sa[i] << ' ' << cs[i] << endl;
		if (f[i])
		{
			int cur = cp[i] + cs[i] - min(cp[i], cs[i]);
			if (cur % 2) ans = min(pa[i] + sa[i] - min(cp[i], cs[i]) + 1, ans); 
			else ans = min(pa[i] + sa[i] - min(cp[i], cs[i]), ans);
		}
	}
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