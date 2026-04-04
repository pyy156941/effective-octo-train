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
using ld = long double;

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

pair <ld, ld> p[100001], s, t;

ld Dist(pair <ld, ld> a, pair <ld, ld> b)
{
	ld res = (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
	return sqrtl(res);
}

void Solve()
{
	int n;
	cin >> n;
	cerr << endl;
	for (int i = 1; i <= n; i++) cin >> p[i].first >> p[i].second;
	cin >> s.first >> s.second >> t.first >> t.second;
	for (int i = 1; i <= n; i++) p[i].first -= s.first, p[i].second -= s.second;
	t.first -= s.first;
	t.second -= s.second;
	s.first = s.second = 0;
	ld dis = Dist(s, t);
/*	if (t.first == 0)
	{
		for (int i = 1; i <= n; i++)
		{
			ld ix = 0;
			ld iy = p[i].second;
			ld a = Dist(s, {ix, iy});
			ld td = Dist(t, {ix, iy});
			if (td > dis && td > a) a = -a;
			ld l = Dist(p[i], {ix, iy});
	//		cerr << dis << ' ' << td << ' ' << a << ' ' << l << endl;
			if (a == 0) 
			{
				if (l != 0) continue;
				else 
				{
					ync(0);
					return;
				}
			}
			if (a * dis * 2.0 >= l * l + a * a)
			{
				ync(0);
				return;
			}
		}
		ync(1);
		return;
	}
	if (t.second == 0)
	{
		for (int i = 1; i <= n; i++)
		{
			ld ix = p[i].first;
			ld iy = 0;
			ld a = Dist(s, {ix, iy});
			ld td = Dist(t, {ix, iy});
			if (td > dis && td > a) a = -a;
			ld l = Dist(p[i], {ix, iy});
//			cerr << dis << ' ' << td << ' ' << a << ' ' << l << endl;
			if (a == 0) 
			{
				if (l != 0) continue;
				else 
				{
					ync(0);
					return;
				}
			}
			if (a * dis * 2.0 >= l * l + a * a)
			{
				ync(0);
				return;
			}
		}
		ync(1);
		return;
	}
	ld k = t.second / t.first;
	ld ik = -1.0 / k;
	for (int i = 1; i <= n; i++)
	{
		ld ix = (ik * p[i].first - p[i].second) / (ik - k);
		ld iy = ix * k;
		ld a = Dist(s, {ix, iy});
		ld td = Dist(t, {ix, iy});
		if (td > dis && td > a) a = -a;
		ld l = Dist(p[i], {ix, iy});
		cerr << fixed << setprecision(15) << dis << ' ' << td << ' ' << a << ' ' << l << endl;
		if (a == 0) 
		{
			if (l != 0) continue;
			else 
			{
				ync(0);
				return;
			}
		}
		if (a * dis * 2.0 >= l * l + a * a)
		{
			ync(0);
			return;
		}
	}
	ync(1);*/
	for (int i = 1; i <= n; i++)
	{
		if (Dist(p[i], t) <= dis) 
		{
			ync(0);
			return;
		}
	}
	ync(1);
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