// Problem: F - K-th Largest Triplet
// Contest: AtCoder - AtCoder Beginner Contest 391
// URL: https://atcoder.jp/contests/abc391/tasks/abc391_f
// Memory Limit: 1024 MB
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

ll a[200001], b[200001], c[200001];
struct Quartet
{
	int i, j, k;
	ll val;
	
	Quartet(int i_, int j_, int k_) : i(i_), j(j_), k(k_), val(a[i_] * b[j_] + b[j_] * c[k_] + c[k_] * a[i_]) {}
	bool operator < (const Quartet _) const
	{
		if (val == _.val) 
		{
			if (i == _.i)
			{
				if (j == _.j) return k < _.k;
				return j < _.j;
			}
			return i < _.i;
		} // bruh I must uniquely determine if val is equal
		return val < _.val;
	}
	
	bool operator == (const Quartet _) const
	{
		return i == _.i && j == _.j && k == _.k && val == _.val;
	} 
};

priority_queue <Quartet> Q;
void Solve()
{
	int n, k;
	multiRead(n, k);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	for (int i = 1; i <= n; i++) cin >> c[i];
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	sort(c + 1, c + n + 1);
	Q.push(Quartet(n, n, n));
	int cnt = 0;
	Quartet las = Quartet(0, 0, 0);
	while (cnt < k)
	{
		auto cur = Q.top();
		Q.pop();
		if (cur == las) continue;
		if (cur.i > 1) Q.push(Quartet(cur.i - 1, cur.j, cur.k));
		if (cur.j > 1) Q.push(Quartet(cur.i, cur.j - 1, cur.k));
		if (cur.k > 1) Q.push(Quartet(cur.i, cur.j, cur.k - 1));
		las = cur;
		cnt++;
	}
	cout << las.val << endl;
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