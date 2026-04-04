// Problem: F - Useless for LIS
// Contest: AtCoder - Panasonic Programming Contest 2024（AtCoder Beginner Contest 354）
// URL: https://atcoder.jp/contests/abc354/tasks/abc354_f
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
int tree[200001];

void Clear()
{
	for (int i = 1; i <= n; i++) tree[i] = 0;
}

void Update(int p, int x)
{
	while (p <= n) 
	{
		tree[p] = max(tree[p], x);
		p += lowbit(p);
	}
}

int Query(int x)
{
	int ans = 0;
	while (x)
	{
		ans = max(ans, tree[x]);
		x -= lowbit(x);
	}
	return ans;
}

int tmp[200001], a[200001], cnt = 0;
int p[200001], s[200001];
void Solve()
{
	cin >> n;
	Clear();
	cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		tmp[++cnt] = a[i];
	}
	sort(tmp + 1, tmp + cnt + 1);
	cnt = unique(tmp + 1, tmp + cnt + 1) - tmp - 1;
	for (int i = 1; i <= n; i++) a[i] = lower_bound(tmp + 1, tmp + cnt + 1, a[i]) - tmp;
	int le = 0;
	for (int i = 1; i <= n; i++)
	{
		p[i] = Query(a[i] - 1) + 1;
		Update(a[i], p[i]);
		le = max(le, p[i]);
	}
	Clear();
	for (int i = n; i >= 1; i--)
	{
		s[i] = Query(cnt - a[i]) + 1;
		Update(cnt + 1 - a[i], s[i]);
	}
	vector <int> ans;
	for (int i = 1; i <= n; i++)
	{
//		cerr << a[i] << ' ' << p[i] << ' ' << s[i] << endl;
		if (s[i] + p[i] - 1 == le) ans.pb(i);
	}
	cout << ans.size() << '\n';
	for (auto it : ans) cout << it << ' ';
	cout << '\n';
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