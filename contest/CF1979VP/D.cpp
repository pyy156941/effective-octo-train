// Problem: D. Fixing a Binary String
// Contest: Codeforces - Codeforces Round 951 (Div. 2)
// URL: https://codeforces.com/contest/1979/problem/D
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

bool s[100001];
void solve()
{
	int n, k;
	string str;
	cin >> n >> k >> str;
	for (int i = 0; i < n; i++) s[i + 1] = (str[i] == '1' ? true : false);
	int llen = 1, las = s[n];
	for (int i = n - 1; i >= 1; i--)
	{
		if (s[i] != las) break;
		else llen++;
	}
	if (llen > k) 
	{
		cout << -1 << endl;
		return;
	}
	if (llen == k)
	{
		bool ok = true;
		int curl = 0, cur = -1;
		for (int i = 1; i <= n; i++)
		{
			if (cur < 0)
			{
				curl = 1;
				cur = s[i];
			}
			else if (cur == s[i]) curl++;
			else
			{
				if (curl != k)
				{
					ok = false;
					break;
				}
				curl = 1;
				cur = s[i];
			}
		}
		if (curl != k) ok = false;
		if (ok)
		{
			cout << n << endl;
			return;
		}
		curl = 0, cur = -1;
		int ans = 0;
		for (int i = 1; i <= n - llen + 1; i++)
		{
			if (cur < 0)
			{
				curl = 1;
				cur = s[i];
			}
			else if (cur == s[i]) curl++;
			else
			{
				if (curl != k)
				{
					if (ans || cur == las || curl != 2 * k) 
					{
						cout << -1 << endl;
						return;
					}
					ans = i - k - 1;
				}
				curl = 1;
				cur = s[i];
			}
			// cerr << i << ' ' << s[i] << ' ' << curl << endl;
		}
		cout << ans << endl;
		return;
	}
	else
	{
		int curl = 0, cur = -1;
		int ans = 0;
		for (int i = 1; i <= n - llen + 1; i++)
		{
			if (cur < 0)
			{
				curl = 1;
				cur = s[i];
			}
			else if (cur == s[i]) curl++;
			else
			{
				if (curl != k)
				{
					if (ans || cur != las || curl > 2 * k || curl % k != k - llen) // cur -> curl for the 3rd condition
					{
						cout << -1 << endl;
						return;
					}
					if (curl < k) ans = i - 1;
					else ans = i - k - 1;
				}
				curl = 1;
				cur = s[i];
			}
			// cerr << i << ' ' << s[i] << ' ' << curl << endl;
		}
		cout << ans << endl;
		return;
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