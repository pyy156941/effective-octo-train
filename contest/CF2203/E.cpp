// Problem: E. Probabilistic Card Game
// Contest: Codeforces - Educational Codeforces Round 187 (Rated for Div. 2)
// URL: https://codeforces.com/contest/2203/problem/E
// Memory Limit: 512 MB
// Time Limit: 4000 ms
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

bool multiTest = false;

constexpr ll mod = 998244353;
struct Node
{
	ll sum; 
	int cnt;
}tree[1000001];

void Pushup(int cur)
{
	tree[cur].cnt = tree[ls(cur)].cnt + tree[rs(cur)].cnt;
	tree[cur].sum = tree[ls(cur)].sum + tree[rs(cur)].sum;
}

void Update(int cur, int p, int s, int t, ll val)
{
	if (s == t)
	{
		tree[cur].cnt = 1;
		tree[cur].sum = val;
		return;
	}
	int mid = (s + t) >> 1;
	if (p <= mid) Update(ls(cur), p, s, mid, val);
	if (p > mid) Update(rs(cur), p, mid + 1, t, val);
	Pushup(cur);
}

ll Sum_K(int cur, int s, int t, int k)
{
	if (!k) return 0;
	if (s == t) return tree[cur].sum;
	int lsc = tree[ls(cur)].cnt;
	int mid = (s + t) >> 1;
	if (k > lsc) return tree[ls(cur)].sum + Sum_K(rs(cur), mid + 1, t, k - lsc);
	else return Sum_K(ls(cur), s, mid, k);
}

ll a[200001];
ll tmp[200001], tc = 0;

pair <ll, ll> Get_Bob(int k, int cm) // first is descending, second is increasing
{
	ll first_k_minus_1 = Sum_K(1, 1, tc, k - 1);
	ll first_k_minus_2 = Sum_K(1, 1, tc, k - 2);
	ll k_minus_1 = first_k_minus_1 - first_k_minus_2;
	ll all_sum = Sum_K(1, 1, tc, cm);
	ll from_k_plus_2 = all_sum - Sum_K(1, 1, tc, k + 1);
	ll from_k_plus_1 = all_sum - Sum_K(1, 1, tc, k);
	ll k_plus_1 = from_k_plus_1 - from_k_plus_2;
	ll choose_before = (ll)(k - 2) * k_minus_1 - first_k_minus_2; // ascending
	ll choose_after = from_k_plus_2 - (ll)(cm - k - 1) * k_plus_1; // descending
	return {choose_after, choose_before};
}

void Solve()
{
	int m;
	cin >> m;
	for (int i = 1; i <= m; i++) cin >> a[i], tmp[++tc] = a[i];
	sort(tmp + 1, tmp + tc + 1);
	for (int i = 1; i <= m; i++) a[i] = lower_bound(tmp + 1, tmp + tc + 1, a[i]) - tmp;
	for (int i = 1; i <= m; i++)
	{
		Update(1, a[i], 1, tc, tmp[a[i]]);
		if (i < 3) continue;
		if (i == 3)
		{
			cout << 0 << endl;
			continue;
		}
		int l = 2, r = i - 1, first_before_large = 0;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			auto [after, before] = Get_Bob(mid, i);
			if (before >= after) first_before_large = mid, r = mid - 1;
			else l = mid + 1;
		}
		// cerr << first_before_large << endl;
		auto [after, before] = Get_Bob(first_before_large, i);
		auto [after1, before1] = Get_Bob(first_before_large - 1, i);
		ll ans = min(max(after, before), max(after1, before1));
		cout << ans % mod * Inv((ll)i - 2, mod) % mod << endl; 
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