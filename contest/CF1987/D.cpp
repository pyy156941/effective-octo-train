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

int n;
map <int, int> mp;
vector <int> freq; 
int dp[5001][5001];

void Solve()
{
	mp.clear();
	freq.clear();
	int a;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a, mp[a]++;
	freq.pb(0);
	for (auto it : mp) 
	{
//		cerr << it.second << ' ';
		freq.pb(it.second);
	}
//	cerr << endl;
	dp[1][0] = 0;
	dp[1][1] = 1e7;
//	cerr << freq.size() << endl;
	for (int i = 2; i < freq.size(); i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if (j <= i - 1) dp[i][j] = dp[i - 1][j];
			else dp[i][j] = 1e7;
			if (j)
			{
				if (dp[i - 1][j - 1] + freq[i] <= i - j) dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + freq[i]);
			}
//			cerr << dp[i][j] << ' ';
		}
//		cerr << endl;
	}
	for (int i = freq.size() - 1; i >= 0; i--)
	{
		if (dp[freq.size() - 1][i] < 1e7) 
		{
			cout << freq.size() - 1 - i << endl;
			return;
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