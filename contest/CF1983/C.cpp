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
int a[200001], b[200001], c[200001];
ll pra[200001], prb[200001], prc[200001];
ll sua[200001], sub[200001], suc[200001];
void Solve()
{
	cin >> n;
	ll tot = 0; 
	for (int i = 1; i <= n; i++) cin >> a[i], tot += (ll)a[i], pra[i] = pra[i - 1] + (ll)a[i];
	for (int i = 1; i <= n; i++) cin >> b[i], prb[i] = prb[i - 1] + (ll)b[i];
	for (int i = 1; i <= n; i++) cin >> c[i], prc[i] = prc[i - 1] + (ll)c[i];
	ll lim = (tot + 2ll) / 3ll;
	ll cur = 0;
	sua[n + 1] = sub[n + 1] = suc[n + 1] = 0;
	for (int i = n; i >= 1; i--)
	{
		sua[i] = sua[i + 1] + (ll)a[i];
		sub[i] = sub[i + 1] + (ll)b[i];
		suc[i] = suc[i + 1] + (ll)c[i];
	}
	for (int i = 1; i <= n; i++)
	{
		int p = upper_bound(pra + 1, pra + i + 1, pra[i] - lim) - pra - 1;
		if ((prb[p] >= lim && suc[i + 1] >= lim))
		{
			cout << p + 1 << ' ' << i << ' ' << 1 << ' ' << p << ' ' << i + 1 << ' ' << n << endl;
			return;
		}
		if ((prc[p] >= lim && sub[i + 1] >= lim))
		{
			cout << p + 1 << ' ' << i << ' ' << i + 1 << ' ' << n << ' ' << 1 << ' ' << p << endl;
			return;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		int p = upper_bound(prb + 1, prb + i + 1, prb[i] - lim) - prb - 1;
		if ((pra[p] >= lim && suc[i + 1] >= lim))
		{
			cout << 1 << ' ' << p << ' ' << p + 1 << ' ' << i << ' ' << i + 1 << ' ' << n << endl;
			return;
		}
		if ((prc[p] >= lim && sua[i + 1] >= lim))
		{
			cout << i + 1 << ' ' << n << ' ' << p + 1 << ' ' << i << ' ' << 1 << ' ' << p << endl;
			return;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		int p = upper_bound(prc + 1, prc + i + 1, prc[i] - lim) - prc - 1;
		if ((pra[p] >= lim && sub[i + 1] >= lim))
		{
			cout << 1 << ' ' << p << ' ' << i + 1 << ' ' << n << ' ' << p + 1 << ' ' << i << endl;
			return;
		}
		if ((prb[p] >= lim && sua[i + 1] >= lim))
		{
			cout << i + 1 << ' ' << n << ' ' << 1 << ' ' << p << ' ' << p + 1 << ' ' << i << endl;
			return;
		}
	}
	cout << "-1\n";
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