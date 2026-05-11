// Problem: D. Palindrome Flipping
// Contest: Codeforces - Codeforces Round 1067 (Div. 2)
// URL: https://codeforces.com/contest/2158/problem/D
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

bool s[101], t[101];
void solve()
{
	int n;
	string s1, t1;
	cin >> n >> s1 >> t1;
	for (int i = 1; i <= n; i++)
	{
		if (s1[i - 1] == '0') s[i] = false;
		else s[i] = true;
		if (t1[i - 1] == '0') t[i] = false;
		else t[i] = true;
	}
	vector <pair <int, int>> ans;
	bool has = false;
	for (int i = 2; i <= n; i++)
	{
		if (s[i] == s[i - 1]) 
		{
			has = true;
			break;
		}
	}
	if (!has) 
	{
		ans.pb({1, 3});
		s[1] ^= 1, s[2] ^= 1, s[3] ^= 1;
	}
	bool hat = false;
	{
		for (int i = 2; i <= n; i++)
		{
			if (t[i] == t[i - 1]) 
			{
				hat = true;
				break;
			}
		}
		if (!hat) t[1] ^= 1, t[2] ^= 1, t[3] ^= 1;
	}
	bool e = false;
	while (1)
	{
		int cur = s[1], curl = 1;
		for (int i = 2; i <= n; i++)
		{
			if (cur != s[i])
			{
				if (curl > 1 && cur != e) 
				{
					ans.pb({i - curl, i - 1});
					for (int j = i - curl; j < i; j++) s[j] ^= 1;
				}
				curl = 1;
				cur = s[i];
			}
			else curl++;
		}
		if (curl > 1 && cur != e)
		{
			ans.pb({n + 1 - curl, n});
			for (int j = n + 1 - curl; j <= n; j++) s[j] ^= 1;
		}
		bool ok = true;
		for (int i = 1; i <= n; i++)
		{
			if (s[i] != e) 
			{
				ok = false;
				break;
			}
		}
		if (ok) break;
		e ^= 1;
	}
	int tl = 0, tr = 0;
	bool tv = false;
	int cur = t[1], curl = 1;
	for (int i = 2; i <= n; i++)
	{
		if (cur != t[i])
		{
			if (curl > 1)
			{
				tv = cur;
				tl = i - curl;
				tr = i - 1;
			} 
			curl = 1;
			cur = t[i];
		}
		else curl++;
	}
	if (curl > 1) 
	{
		tv = cur;
		tl = n + 1 - curl;
		tr = n;
	}
	if (tv != e)
	{
		ans.pb({1, n});
		for (int i = 1; i <= n; i++) s[i] ^= 1;
	}
	// cerr << tl << ' ' << tr << endl;
	for (int i = 1; i < tl; i++)
	{
		if (s[i] != t[i]) 
		{
			ans.pb({i, tr});
			for (int j = i; j <= tr; j++) s[j] ^= 1;
		}
	}
	if (s[tl] != t[tl]) 
	{
		ans.pb({tl, tr});
		for (int j = tl; j <= tr; j++) s[j] ^= 1;
	}
	for (int i = n; i > tr; i--)
	{
		if (s[i] != t[i]) 
		{
			ans.pb({tl, i});
			for (int j = tl; j <= i; j++) s[j] ^= 1;
		}
	}
	if (s[tl] != t[tl]) 
	{
		ans.pb({tl, tr});
		for (int j = tl; j <= tr; j++) s[j] ^= 1;
	}
	if (!hat) ans.pb({1, 3});
	cout << ans.size() << endl;
	for (auto [l, r] : ans) cout << l << ' ' << r << endl;
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