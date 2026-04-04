// Problem: A2. Lost Civilization (Hard Version)
// Contest: Codeforces - Codeforces Round 1082 (Div. 1)
// URL: https://codeforces.com/contest/2201/problem/A2
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
#define debug(x) cerr << #x << " : " << x << endl;
#define isdigit(x) (x >= '0' && x <= '9')
#define least2p(x) ((x == 1) ? 0 : __lg(x) + ((x & (x - 1)) != 0))

#define yn(x) pc(x ? 'Y' : 'N'), pc(x ? 'e' : 'o'), x ? (pc('s'), pc('\n')) : pc('\n')
#define ync(x) pc(x ? 'Y' : 'N'), pc(x ? 'E' : 'O'), x ? (pc('S'), pc('\n')) : pc('\n')
#define ynl(x) pc(x ? 'y' : 'n'), pc(x ? 'e' : 'o'), x ? (pc('s'), pc('\n')) : pc('\n')

template <typename T>
T readInt() 
{
    T x = 0;
    int f = 1;
    char ch = getchar();
    while (!isdigit(ch)) 
    {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) 
    {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    return x * f;
}

template <typename T>
void readInt(T &x) {
    x = 0;
    int f = 1;
    char ch = getchar();
    while (!isdigit(ch)) 
    {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) 
    {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    x *= f;
}

template <typename T>
void writeInt(T x) 
{
    if (x < 0) 
    {
        putchar('-');
        x = -x;
    }
    if (x > 9) writeInt(x / 10);
    putchar(x % 10 + '0');
}

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

bool multiTest = true;

int a[300001];
void Solve()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	vector <int> st;
	st.pb(1);
	int base = a[1], mx = a[1];
	for (int i = 2; i <= n; i++)
	{
		if (a[i] <= base || a[i] > mx + 1) 
		{
			base = mx = a[i];
			st.pb(i);
		}
		else mx = a[i];
	}
	ll ans = 0;
	for (auto it : st) ans += (ll)it * (ll)(n - it + 1);
	int lst = n + 1;
	stack <int> stk;
	int sz = 0;
	ll sum = 0; 
	for (int i = st.size() - 1; i >= 0; i--)
	{
		int stp = st[i];
		for (int j = lst - 1; j > stp; j--)
		{
			ans += (ll)(n - j + 1);
			while (!stk.empty() && a[stk.top()] > a[j]) sz--, sum -= (ll)stk.top(), stk.pop();
			ans += (ll)n * sz;
			ans += (ll)sz;
			ans -= sum; 
			stk.push(j);
			sz++, sum += (ll)j;
		}
		while (!stk.empty()) stk.pop();
		sz = 0;
		sum = 0;
		lst = stp;
	}
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