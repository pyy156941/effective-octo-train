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

struct bind
{
	int val;
	bool ch;
	
	bool operator < (const bind b) const
	{
		return val < b.val;
	}
	
}a[200001];

vector <pair <int, int>> tmp;

int n, k;
bool Check(int x)
{
	int cnt = 0;
	int lef = k;
//	cerr << x << endl;
	for (auto [val, ch] : tmp)
	{
		if (val >= x) cnt++;
		else if (ch) 
		{
			if (lef >= x - val) lef -= x - val, cnt++;
		}
	}
	return (cnt >= ((n - 1) / 2 + 1));
}

void Solve()
{
	cin >> n >> k;
	tmp.clear();
	for (int i = 1; i <= n; i++) cin >> a[i].val;
	for (int i = 1; i <= n; i++) cin >> a[i].ch;
	sort(a + 1, a + n + 1);
	int med = (n + 1) / 2;
	ll ans = 0;
	int mxd = 0;
	for (int i = 1; i <= n; i++)
	{
		if (!a[i].ch)
		{
			if (!mxd || a[i].val > a[mxd].val) mxd = i;
			continue;
		}
		if (n % 2)
		{
			if (i < med) ans = max(ans, (ll)a[med].val + a[i].val + k);
			else ans = max(ans, (ll)a[med - 1].val + a[i].val + k);
		}
		else
		{
			if (i <= med) ans = max(ans, (ll)a[med + 1].val + a[i].val + k);
			else ans = max(ans, (ll)a[med].val + a[i].val + k);
		}
	}
	for (int i = n; i >= 1; i--)
	{
		if (i != mxd) tmp.pb({a[i].val, a[i].ch});
	}
//	cerr << a[mxd].val << endl;
	ll l = 1, r = 2e9 + 1, res;
	while (l <= r)
	{
		ll mid = (l + r) >> 1;
		if (Check(mid)) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	ans = max(ans, res + a[mxd].val);
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