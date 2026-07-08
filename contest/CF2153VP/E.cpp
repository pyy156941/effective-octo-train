// Problem: E. Zero Trailing Factorial
// Contest: Codeforces - Codeforces Round 1057 (Div. 2)
// URL: https://codeforces.com/contest/2153/problem/E
// Memory Limit: 512 MB
// Time Limit: 3000 ms
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

constexpr int N = 10001000;
bool np[N + 1];
vector <int> prime;
void init()
{
	for (int i = 2; i <= N; i++)
	{
		if (np[i]) continue;
		prime.pb(i);
		for (int j = i + i; j <= N; j += i) np[j] = true;
	}
	// int md = 0;
	// for (int i = 1; i < prime.size(); i++) md = max(md, prime[i] - prime[i - 1]);
	// md = 154
}

map <int, int> cnt; // cnt of prime factors of n!/x!
void update(int x)
{
	int sq = sqrt(x);
	for (auto it : prime)
	{
		if (it > sq + 1 || it > x) break;
		if (x % it) continue;
		while (x % it == 0) x /= it, cnt[it]++; 
	}
	if (x > 1) cnt[x]++; 
}

int floorlog(int p, int x)
{
	ll test = 1;
	int res = 0;
	while (test * (ll)p <= x) res++, test *= p;
	return res;
}

int getfactor(int n, int p)
{
	ll base = p;
	int res = 0;
	while (base <= n)
	{
		res += n / base;
		base *= (ll)p;
	}
	return res;
}

void solve()
{
	int n, m;
	cin >> n >> m;
	int mpid = upper_bound(prime.begin(), prime.end(), n) - prime.begin() - 1;
	int mp = prime[mpid]; // for x < mp, f is 0 (choose k = mp)
	cnt.clear();
	int ans = 0;
	for (int i = n; i > mp; i--)
	{
		update(i);
		int cur = 1e9;
		for (auto [p, c] : cnt)
		{
			int fp = getfactor(i - 1, p);
			int fpn = getfactor(n, p);
			int num = min(floorlog(p, m), fpn);
			for (int i = num; i >= 1; i--)
			{
				if (fpn / i != fp / i)
				{
					cur = min(cur, fp / i);
					break;
				}
			}
		}
		ans += cur;
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
	init();
	while (_--) solve();
	return 0;
}