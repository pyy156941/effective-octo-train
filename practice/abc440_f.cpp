// Problem: F - Egoism
// Contest: AtCoder - AtCoder Beginner Contest 440
// URL: https://atcoder.jp/contests/abc440/tasks/abc440_f
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

int tmp_dit[400001], ditc = 0;
// use value segtree to query k-largest
struct Node
{
	int cnt, cnt_2;
	ll sum;
}tree[1600001];

void Pushup(int cur)
{
	tree[cur].cnt = tree[ls(cur)].cnt + tree[rs(cur)].cnt;
	tree[cur].sum = tree[ls(cur)].sum + tree[rs(cur)].sum; 
	tree[cur].cnt_2 = tree[ls(cur)].cnt_2 + tree[rs(cur)].cnt_2;
}

void Update(int cur, int p, int s, int t, int d, int y)
{
	if (s == t)
	{
		tree[cur].cnt += d;
		tree[cur].sum += (ll)d * tmp_dit[s];
		if (y == 2) tree[cur].cnt_2 += d;
		return;
	}
	int mid = (s + t) >> 1;
	if (p <= mid) Update(ls(cur), p, s, mid, d, y);
	if (p > mid) Update(rs(cur), p, mid + 1, t, d, y);
	Pushup(cur);
}

int Get_K(int cur, int s, int t, int k)
{
	if (s == t) return tmp_dit[s];
	int lsc = tree[ls(cur)].cnt;
	int mid = (s + t) >> 1;
	if (k > lsc) return Get_K(rs(cur), mid + 1, t, k - lsc);
	else return Get_K(ls(cur), s, mid, k);
}

ll Sum_K(int cur, int s, int t, int k)
{
	if (s == t) return (ll)k * tmp_dit[s];
	int lsc = tree[ls(cur)].cnt;
	int mid = (s + t) >> 1;
	if (k > lsc) return tree[ls(cur)].sum + Sum_K(rs(cur), mid + 1, t, k - lsc);
	else return Sum_K(ls(cur), s, mid, k);
}

int Count_2(int cur, int s, int t, int k)
{
	if (s == t)
	{
		if (k > (tree[cur].cnt - tree[cur].cnt_2)) return k - (tree[cur].cnt - tree[cur].cnt_2);
		else return 0;
	}
	int lsc = tree[ls(cur)].cnt;
	int mid = (s + t) >> 1;
	if (k > lsc) return tree[ls(cur)].cnt_2 + Count_2(rs(cur), mid + 1, t, k - lsc);
	else return Count_2(ls(cur), s, mid, k);
}

void ItTree(int cur, int l, int r)
{
	cerr << tree[cur].cnt << ' ' << tree[cur].sum << ' ' << tree[cur].cnt_2 << ' ' << tmp_dit[l] << ' ' << tmp_dit[r] << endl;
	if (l == r) return;
	int mid = (l + r) >> 1;
	ItTree(ls(cur), l, mid);
	ItTree(rs(cur), mid + 1, r);
}

int n, q;
int x[200001], y[200001];
int qw[200001], qx[200001], qy[200001];
void Solve()
{
	multiRead(n, q);
	for (int i = 1; i <= n; i++) multiRead(x[i], y[i]), tmp_dit[++ditc] = x[i];
	for (int i = 1; i <= q; i++) multiRead(qw[i], qx[i], qy[i]), tmp_dit[++ditc] = qx[i];
	sort(tmp_dit + 1, tmp_dit + ditc + 1);
	ditc = unique(tmp_dit + 1, tmp_dit + ditc + 1) - tmp_dit - 1;
	for (int i = 1; i <= n; i++) 
	{
		x[i] = lower_bound(tmp_dit + 1, tmp_dit + ditc + 1, x[i]) - tmp_dit;
		Update(1, x[i], 1, ditc, 1, y[i]);
	}
	for (int i = 1; i <= q; i++) 
	{
		qx[i] = lower_bound(tmp_dit + 1, tmp_dit + ditc + 1, qx[i]) - tmp_dit;
		Update(1, x[qw[i]], 1, ditc, -1, y[qw[i]]);
		x[qw[i]] = qx[i];
		y[qw[i]] = qy[i];
		Update(1, x[qw[i]], 1, ditc, 1, y[qw[i]]);
		int k = tree[1].cnt_2;
		// ItTree(1, 1, ditc), cerr << "\n";
		ll sum = Sum_K(1, 1, ditc, n);
		if (k == n)
		{
			ll ans = sum * 2ll;
			ans -= (ll)Get_K(1, 1, ditc, 1);
			cout << ans << endl;
		}
		else if (!k)
		{
			ll ans = sum;
			cout << ans << endl;
		}
		else
		{
			ll in_k = k - Count_2(1, 1, ditc, n - k);
			ll ans = sum;
			if (in_k == k)
			{
				// cerr << i << ' ' << k << ' ' << "ink=k" << endl;
				ans += sum - Sum_K(1, 1, ditc, n - k + 1);
				ans += Get_K(1, 1, ditc, n - k);
			}
			else ans += sum - Sum_K(1, 1, ditc, n - k);
			cout << ans << endl;
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