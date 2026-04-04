// Problem: G - Sum of Min of XOR
// Contest: AtCoder - UNIQUE VISION Programming Contest 2025 Autumn (AtCoder Beginner Contest 425)
// URL: https://atcoder.jp/contests/abc425/tasks/abc425_g
// Memory Limit: 1024 MB
// Time Limit: 2500 ms
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
#define debug(x) cerr << #x << " : " << x << endl;
#define isdigit(x) (x >= '0' && x <= '9')
#define least2p(x) ((x == 1) ? 0 : __lg(x) + ((x & (x - 1)) != 0))s

#define yn(x) pc(x ? 'Y' : 'N'), pc(x ? 'e' : 'o'), x ? (pc('s'), pc('\n')) : pc('\n')
#define ync(x) pc(x ? 'Y' : 'N'), pc(x ? 'E' : 'O'), x ? (pc('S'), pc('\n')) : pc('\n')
#define ynl(x) pc(x ? 'y' : 'n'), pc(x ? 'e' : 'o'), x ? (pc('s'), pc('\n')) : pc('\n')

template <typename ... Args>
void multiRead(Args& ... args)
{
    ((cin >> args), ...);
}

template <typename ... Args>
void multiWrite(Args ... args)
{
    ((cout << args << " "), ...);
}

template <typename T>
void fastgcd(T a, T b) // unsigned only
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
	auto za = countr_zero(a);
	auto zb = countr_zero(b);
	a >>= za;
	b >>= zb;
	do 
	{
		T dif = a - b;
		if (a > b) a = b, b = dif;
		else b = b - a;
		b >>= countr_zero(dif);
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
T Inv(T a, T p)
{
	T x, y;
	exgcd(a, p, x, y);
	return (x + p) % p;
}

template <typename T>
T QPow(T a, T b, T mod)
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

bool multiTest = false;

vector <int> new_a; 
// intuition: a higher bit supers all lower ones, so greedy, separate the numbers according to highest bit, then recurse
ll Calc(int m, vector <int> a)
{
	int n = a.size();
	ll res = 0;
	vector <int> ex, nex;
	// cerr << "m: " << m << endl << "a: ";
	// for (auto it : a) cerr << it << ' ';
	// cerr << endl;
	if (!m)
	{
		res = 1e9;
		for (auto it : a) res = min(res, (ll)it);
		return res;
	}
	for (int bit = 30; bit >= 0; bit--)
	{
		if (m < (1 << bit))
		{
			int a_exceed = 0;
			new_a.clear();
			for (auto it : a)
			{
				if (it & (1 << bit)) a_exceed++;
				else new_a.pb(it);
			}
			if (!a_exceed);
			else if (a_exceed == n) 
			{
				res += (ll)(m + 1) * (1 << bit); // there are m + 1 numbers, not m
				for (auto& it : a) it -= (1 << bit); // special case when all elements in a are greater than m
			}
			else a = move(new_a), n = a.size();
		}
		else
		{
			int a_exceed = 0;
			for (auto it : a)
			{
				if (it & (1 << bit)) a_exceed++, ex.pb(it - (1 << bit));
				else nex.pb(it);
			}
			if (!a_exceed)
			{
				res += (ll)(m - (1 << bit) + 1) * (1 << bit);
				if (m - (1 << bit) == (1 << bit) - 1) res += 2ll * Calc(m - (1 << bit), a);
				else
				{
					res += Calc(m - (1 << bit), a);
					res += Calc((1 << bit) - 1, a);
				}
			}
			else if (a_exceed == n)
			{
				res += (ll)(1 << bit) * (1 << bit);
				if (m - (1 << bit) == (1 << bit) - 1) res += 2ll * Calc(m - (1 << bit), ex);
				else
				{
					res += Calc(m - (1 << bit), ex);
					res += Calc((1 << bit) - 1, ex);
				}
			}
			else
			{
				// cerr << m << ' ' << bit << ' ';
				// for (auto it : a) cerr << it << ' ';
				// cerr << endl;
				// for (auto it : ex) cerr << it << ' ';
				// cerr << endl;
				// for (auto it : nex) cerr << it << ' ';
				// cerr << endl;
				// cerr << endl;
				res += Calc(m - (1 << bit), ex);
				res += Calc((1 << bit) - 1, nex);
			}
			break;
		}
	}
	return res;
}

vector <int> a;
void Solve()
{
	int n, m;
	multiRead(n, m);
	int _;
	for (int i = 1; i <= n; i++) cin >> _, a.pb(_);
	ll ans = Calc(m - 1, a);
	cout << ans << endl;
	return;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr);
	int _ = 1;
	if (multiTest) cin >> _;
	while (_--) Solve();
	return 0;
}