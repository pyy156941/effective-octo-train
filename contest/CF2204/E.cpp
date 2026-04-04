// Problem: E. Sum of Digits (and Again)
// Contest: Codeforces - Educational Codeforces Round 188 (Rated for Div. 2)
// URL: https://codeforces.com/contest/2204/problem/E
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

bool multi_test = true;

int cnt[10], cc[10];
void solve()
{
	string str;
	multi_read(str);
	int n = str.length(), sum = 0;
	if (n == 1)
	{
		cout << str << endl;
		return;
	}
	for (int i = 0; i < 10; i++) cnt[i] = 0;
	for (int i = 1; i <= n; i++) cnt[(int)(str[i - 1] - '0')]++, sum += (int)(str[i - 1] - '0');
	vector <int> ans;
	for (int i = max(1, sum - 500); i <= sum; i++) 
	{
		int k = i, t = i, nk = 0, als = 0;
		bool ok = true;
		for (int _ = 0; _ < 10; _++) cc[_] = 0;
		while (k > 9)
		{
			t = k;
			nk = 0;
			while (t) 
			{
				cc[t % 10]++;
				if (cc[t % 10] > cnt[t % 10]) 
				{
					ok = false;
					break;
				}
				nk += t % 10;
				t /= 10;
			}
			if (!ok) break;
			k = nk;
			als += k;
		}
		if (!ok) continue;
		cc[k]++;
		if (cc[k] > cnt[k]) ok = false;
		als += k;
		// cerr << als << ' ' << k << endl;
		// debug(i);
		// for (int i = 0; i < 10; i++) cerr << cnt[i] << ' ';
		// cerr << endl;
		if (ok && i + als == sum) 
		{
			k = i, t = i;
			nk = 0;
			while (k > 9)
			{
				t = k;
				nk = 0;
				ans.pb(k);
				while (t) 
				{
					// debug(cnt[t % 10]);
					cnt[t % 10]--;
					// debug(t % 10);
					// debug(cnt[t % 10]);
					nk += t % 10;
					t /= 10;
				}
				k = nk;
			}
			cnt[k]--;
			ans.pb(k);
			break;
		}
	}
	for (int i = 9; i >= 0; i--) 
	{
		for (int _ = 1; _ <= cnt[i]; _++) cout << i;
	}
	for (auto it : ans) cout << it;
	cout << endl;
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