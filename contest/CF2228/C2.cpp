// Problem: C2. Cirno and Number (Hard Version)
// Contest: Codeforces - Codeforces Round 1098 (Div. 2)
// URL: https://codeforces.com/contest/2228/problem/C2
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

ll p10[18];
ll as(int d, int l)
{
	ll res = 0;
	for (int i = 1; i <= l; i++) res *= 10ll, res += d;
	return res;
}

int ds[11];
void solve()
{
	p10[0] = 1;
	for (int i = 1; i < 18; i++) p10[i] = p10[i - 1] * 10ll;
	ll a;
	int n;
	cin >> a >> n;
	for (int i = 1; i <= n; i++) cin >> ds[i];
	if (n == 1 && !ds[1]) 
	{
		cout << a << endl;
		return;
	}
	int d = 0;
	ll tmp = a;
	vector <int> da;
	while (tmp)
	{
		da.pb(tmp % 10);
		tmp /= 10;
		d++;
	}
	reverse(da.begin(), da.end());
	ll ans = 1e18;
	ll up = 0;
	if (!ds[1]) up += ds[2];
	else up += ds[1];
	for (int i = 1; i <= d; i++) up *= 10ll, up += ds[1];
	ans = min(ans, up - a);
	if (!ds[1]) ans = min(ans, a);
	if (d > 1)
	{
		ll low = as(ds[n], d - 1);
		ans = min(ans, a - low);
	}
	// cerr << ans << ' ' << up << ' ' << low << endl;
	ll cs = 0;
	for (int i = 0; i < d; i++)
	{
		int cur = da[i];
		int rest = d - i - 1;
		cs *= 10ll;
		int has = 0;
		for (int j = 1; j <= n; j++)
		{
			if (ds[j] == cur)
			{
				has = j;
				break;
			}
		}
		for (int j = 1; j <= n; j++)
		{
			if (!i && !ds[j]) continue;
			if (j == has) continue;
			else
			{
				if (ds[j] > cur) ans = min(ans, (cs + ds[j]) * p10[rest] + as(ds[1], rest) - a);
				else ans = min(ans, a - (cs + ds[j]) * p10[rest] - as(ds[n], rest));
			}
		}
		if (!has) break;
		else
		{
			for (int j = 1; j <= n; j++) ans = min(ans, abs((cs + ds[has]) * p10[rest] + as(ds[j], rest) - a));
			cs += ds[has];
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