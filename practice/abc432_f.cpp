// Problem: F - Candy Redistribution
// Contest: AtCoder - OMRON Corporation Programming Contest 2025 #2 (AtCoder Beginner Contest 432)
// URL: https://atcoder.jp/contests/abc432/tasks/abc432_f
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

int a[20]; 
int sum[1048576], dp[1048576], pre[1048576];
stack <int, vector<int>> pos, neg;
void Solve()
{
	int n;
	cin >> n;
	int tot = 0;
	for (int i = 0; i < n; i++) cin >> a[i], tot += a[i];
	if (tot % n)
	{
		cout << "-1\n";
		return;
	}
	for (int i = 0; i < n; i++) a[i] -= tot / n;
	for (int i = 1; i < (1 << n); i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i & (1 << j)) sum[i] += a[j];
		}
	}
	dp[0] = 0;
	for (int i = 1; i < (1 << n); i++)
	{
		dp[i] = 1000;
		for (int j = 0; j < n; j++)
		{
			if (!(i & (1 << j))) continue;
			if (!sum[i]) 
			{
				if (dp[i ^ (1 << j)] < dp[i]) 
				{
					pre[i] = j;
					dp[i] = dp[i ^ (1 << j)];
				}
			}
			else 
			{
				if (dp[i ^ (1 << j)] + 1 < dp[i])
				{
					pre[i] = j;
					dp[i] = dp[i ^ (1 << j)] + 1;
				}
			}
		}
	}
	cout << dp[(1 << n) - 1] << endl;
	int curp = (1 << n) - 1;
	while (curp)
	{
		int curpre = pre[curp];
		// cerr << curpre << endl;
		if (a[curpre] < 0) neg.push(curpre);
		else if (a[curpre] > 0) pos.push(curpre);
		curp ^= (1 << curpre);
	}
	for (int i = 1; i <= dp[(1 << n) - 1]; i++)
	{
		int tneg = neg.top(), tpos = pos.top();
		// cerr << tneg << ' ' << tpos << ' ' << a[tneg] << ' ' << a[tpos] << endl;
		int dif = a[tneg] + a[tpos];
		cout << tpos + 1 << ' ' << tneg + 1 << ' ';
		if (a[tneg] + a[tpos] < 0)
		{
			cout << a[tpos] << endl;
			a[tneg] = dif;
			a[tpos] = 0;
			pos.pop();
		}
		else if (a[tneg] + a[tpos] > 0)
		{
			cout << -a[tneg] << endl;
			a[tneg] = 0;
			a[tpos] = dif;
			neg.pop();
		}
		else 
		{
			cout << a[tpos] << endl;
			a[tneg] = a[tpos] = 0;
			neg.pop();
			pos.pop();
		}
	}
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