// Problem: E. Computing Machine
// Contest: Codeforces - Codeforces Round 953 (Div. 2)
// URL: https://codeforces.com/contest/1978/problem/E
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

bool a[200001], b[200001], mb[200001], ma[200001];
int pa[200001];

int bsolve(int l, int r)
{
	bool ta[4], tb[4];
	for (int i = l; i <= r; i++) ta[i - l] = a[i], tb[i - l] = b[i];
	for (int i = l + 1; i < r; i++)
	{
		if (!a[i - 1] && !a[i + 1]) tb[i - l] = true;
	}
	for (int i = l + 1; i < r; i++)
	{
		if (tb[i - l - 1] && tb[i - l + 1]) ta[i - l] = true;
	}
	int ans = 0;
	for (int i = l; i <= r; i++) if (ta[i - l]) ans++;
	return ans;
}

void solve()
{
	int n;
	string s, t;
	cin >> n >> s >> t;
	for (int i = 1; i <= n; i++)
	{
		a[i] = (s[i - 1] == '1' ? true : false);
		b[i] = (t[i - 1] == '1' ? true : false);
		mb[i] = b[i];
		ma[i] = a[i];
	}
	for (int i = 2; i < n; i++) 
	{
		if (!a[i - 1] && !a[i + 1]) mb[i] = true;
	}
	pa[1] = 0;
	for (int i = 2; i < n; i++)
	{
		if (mb[i - 1] && mb[i + 1]) ma[i] = true;
		pa[i] = pa[i - 1];
		if (ma[i]) pa[i]++;
	}
	int q, l, r;
	cin >> q;
	for (int i = 1; i <= q; i++)
	{
		cin >> l >> r;
		if (r - l + 1 <= 4) 
		{
			cout << bsolve(l, r) << endl;
			continue;
		}
		int ans = 0;
		if (a[l]) ans++;
		if (a[r]) ans++;
		if (a[l + 1] || (b[l] && mb[l + 2])) ans++;
		if (a[r - 1] || (b[r] && mb[r - 2])) ans++;
		// cerr << ans << endl;
		ans += pa[r - 2] - pa[l + 1];
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