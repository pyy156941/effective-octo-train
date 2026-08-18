// Problem: G - Domino Arrangement
// Contest: AtCoder - AtCoder Beginner Contest 435
// URL: https://atcoder.jp/contests/abc435/tasks/abc435_g
// Memory Limit: 1024 MB
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

constexpr ll mod = 998244353;

int n, m;
int l[500001], r[500001];
vector <int> li[500001], ri[500001];
ll laso[500001], lase[500001];
ll S[500001], sl[500001];
void solve()
{
	cin >> n >> m;
	for (int i = 1; i <= m; i++) 
	{
		cin >> l[i] >> r[i], l[i]++;
		if (r[i] >= l[i]) li[l[i]].pb(i), ri[r[i]].pb(i); 
	}
	for (int i = 1; i <= m; i++) laso[i] = lase[i] = sl[i] = 0;
	S[0] = S[1] = 1;
	int curo = 0, cure = 0;
	ll biaso = 0, multo = 1, biase = 0, multe = 1;
	for (int i = 2; i <= n; i++)
	{
		if (i % 2)
		{
			sl[i] = sl[i - 2];
			for (auto ca : li[i - 1]) 
			{
				if (r[ca] >= i) 
				{
					laso[ca] = (-biaso * multo + mod) % mod;
					sl[i] = (sl[i] + laso[ca]) % mod;
				}
				curo++; // count should be updated since that we will remove this color later
			}
			for (auto ca : li[i]) 
			{
				laso[ca] = (-biaso * multo + mod) % mod, curo++;
				sl[i] = (sl[i] + laso[ca]) % mod;
			}
			for (auto cr : ri[i - 2]) sl[i] = (sl[i] - laso[cr] + mod) % mod, laso[cr] = 0, curo--;
			for (auto cr : ri[i - 1]) sl[i] = (sl[i] - laso[cr] + mod) % mod, laso[cr] = 0, curo--;
			multo *= -1;
			biaso *= -1;
			biaso = (biaso % mod + mod) % mod;
			biaso = (biaso + S[i - 2]) % mod;
			S[i] = (S[i - 1] + biaso * curo % mod) % mod;
			S[i] = (S[i] + (multo * sl[i] % mod + mod) % mod) % mod;
		}
		else
		{
			sl[i] = sl[i - 2];
			for (auto ca : li[i - 1]) 
			{
				if (r[ca] >= i) 
				{
					lase[ca] = (-biase * multe + mod) % mod;
					sl[i] = (sl[i] + lase[ca]) % mod;
				}
				cure++;
			}
			for (auto ca : li[i]) 
			{
				lase[ca] = (-biase * multe + mod) % mod, cure++;
				sl[i] = (sl[i] + lase[ca]) % mod;
			}
			for (auto cr : ri[i - 2]) sl[i] = (sl[i] - lase[cr] + mod) % mod, lase[cr] = 0, cure--;
			for (auto cr : ri[i - 1]) sl[i] = (sl[i] - lase[cr] + mod) % mod, lase[cr] = 0, cure--;
			multe *= -1;
			biase *= -1;
			biase = (biase % mod + mod) % mod;
			biase = (biase + S[i - 2]) % mod;
			S[i] = (S[i - 1] + biase * cure % mod) % mod;
			S[i] = (S[i] + (multe * sl[i] % mod + mod) % mod) % mod;
		}
	}
	// for (int i = 1; i <= n; i++) cerr << S[i] << endl;
	cout << S[n] << endl;
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