// Problem: D. Ghostfires
// Contest: Codeforces - Codeforces Round 1087 (Div. 2)
// URL: https://codeforces.com/contest/2209/problem/D
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

void op3(int x, string s)
{
	string ss[3] = {s, {s[1], s[2], s[0]}, {s[2], s[0], s[1]}};
	for (int i = 0; i < x; i++) cout << ss[i % 3];
	return;
}

void solve()
{
	int r, g, b;
	multi_read(r, g, b);
	if (r == g && g == b)
	{
		op3(r, "RGB");
		cout << endl;
		return;
	}
	if (r >= g && g >= b)
	{
		if (r == g)
		{
			for (int i = 1; i <= r - b; i++) cout << "RG";
			op3(b, "RGB");
			cout << endl;
			return;
		}
		int x = 0;
		while (r < g + b + 1) 
		{
			x++;
			r--;
			g--;
			b--;
		}
		for (int i = 1; i <= g; i++) cout << "RG";
		for (int i = 1; i <= b; i++) cout << "RB";
		cout << "R";
		op3(x, "BRG");
		cout << endl;
		return;
	}
	else if (r >= b && b >= g)
	{
		if (r == b)
		{
			for (int i = 1; i <= r - g; i++) cout << "RB";
			op3(g, "GBR");
			cout << endl;
			return;
		}
		int x = 0;
		while (r < b + g + 1) 
		{
			x++;
			r--;
			g--;
			b--;
		}
		for (int i = 1; i <= b; i++) cout << "RB";
		for (int i = 1; i <= g; i++) cout << "RG";
		cout << "R";
		op3(x, "BRG");
		cout << endl;
		return;
	}
	else if (g >= r && r >= b)
	{
		if (g == r)
		{
			for (int i = 1; i <= g - b; i++) cout << "GR";
			op3(b, "BRG");
			cout << endl;
			return;
		}
		int x = 0;
		while (g < r + b + 1) 
		{
			x++;
			r--;
			g--;
			b--;
		}
		for (int i = 1; i <= r; i++) cout << "GR";
		for (int i = 1; i <= b; i++) cout << "GB";
		cout << "G";
		op3(x, "RGB");
		cout << endl;
		return;
	}
	else if (g >= b && b >= r)
	{
		if (g == b)
		{
			for (int i = 1; i <= g - r; i++) cout << "GB";
			op3(r, "GBR");
			cout << endl;
			return;
		}
		int x = 0;
		while (g < b + r + 1) 
		{
			x++;
			r--;
			g--;
			b--;
		}
		for (int i = 1; i <= b; i++) cout << "GB";
		for (int i = 1; i <= r; i++) cout << "GR";
		cout << "G";
		op3(x, "RGB");
		cout << endl;
		return;
	}
	else if (b >= r && r >= g)
	{
		if (b == r)
		{
			for (int i = 1; i <= b - g; i++) cout << "BR";
			op3(g, "BRG");
			cout << endl;
			return;
		}
		int x = 0;
		while (b < r + g + 1) 
		{
			x++;
			r--;
			g--;
			b--;
		}
		for (int i = 1; i <= r; i++) cout << "BR";
		for (int i = 1; i <= g; i++) cout << "BG";
		cout << "B";
		op3(x, "GBR");
		cout << endl;
		return;
	}
	else if (b >= g && g >= r)
	{
		if (b == g)
		{
			for (int i = 1; i <= b - r; i++) cout << "BG";
			op3(r, "RGB");
			cout << endl;
			return;
		}
		int x = 0;
		while (b < g + r + 1) 
		{
			x++;
			r--;
			g--;
			b--;
		}
		for (int i = 1; i <= g; i++) cout << "BG";
		for (int i = 1; i <= r; i++) cout << "BR";
		cout << "B";
		op3(x, "GBR");
		cout << endl;
		return;
	}
	else assert(0);
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