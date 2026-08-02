// Problem: F - Pyramid Alignment
// Contest: AtCoder - AtCoder Beginner Contest 428
// URL: https://atcoder.jp/contests/abc428/tasks/abc428_f
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
#define isdigit(x) (x >= '0' && x <= '9')
#define least2p(x) ((x == 1) ? 0 : __lg(x) + ((x & (x - 1)) != 0))
#define debug(x) cerr << #x << " : " << x << endl;

#define yn(x) \
do \
{ \
    cout << (x ? 'Y' : 'N'); \
    cout << (x ? 'e' : 'o'); \
    cout << (x ? 's' : '\n'); \
    if (!x) cout << '\n'; \
} while(0)

#define ync(x) \
do \
{ \
    cout << (x ? 'Y' : 'N'); \
    cout << (x ? 'E' : 'O'); \
    cout << (x ? 'S' : '\n'); \
    if (!x) cout << '\n'; \
} while(0)

#define ynl(x) \
do \
{ \
    cout << (x ? 'y' : 'n'); \
    cout << (x ? 'e' : 'o'); \
    cout << (x ? 's' : '\n'); \
    if (!x) cout << '\n'; \
} while(0)

istream& operator >> (istream& cin, i128& x)
{
    x = 0;
    int f = 1;
    char ch;
    ch = cin.get();
    while (ch == ' ' || ch == '\n' || ch == '\t') ch = cin.get();
    if (ch == '-')
    {
        f = -1;
        ch = cin.get();
    }
    while (isdigit(ch))
    {
        x = x * 10 + (ch - '0');
        ch = cin.get();
    }
    cin.putback(ch);
    x *= f;
    return cin;
}

ostream& operator << (ostream& cout, i128 x)
{
    if (x == 0)
    {
        cout << '0';
        return cout;
    }
    if (x < 0)
    {
        cout << '-';
        x = -x;
    }
    if (x >= 10) cout << (x / 10);
    cout << (char)('0' + (x % 10));
    return cout;
}

template <typename ... Args>
void multi_read(Args& ... args)
{
    ((cin >> args), ...);
}

template <typename ... Args>
void multi_write(Args ... args)
{
    ((cout << args << " "), ...);
}

template <typename ... Args>
void multi_write_endl(Args ... args)
{
    ((cout << args << " "), ...);
    cout << endl;
}

template <typename T>
T fastgcd(T a, T b) // unsigned only, requires C++20
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
T mod_inv(T a, T p)
{
	T x, y;
	exgcd(a, p, x, y);
	return (x + p) % p;
}

template <typename T>
T qpow(T a, T b, T mod)
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

bool multi_test = false;

struct seg
{
	int l, r;
	bool type; // false left true right
	int align;
	
	seg (int _l, int _r, bool _type, int _align) : l(_l), r(_r), type(_type), align(_align) {}
};

int w[200001];
vector <seg> segs;

bool checkseg(int s, int x)
{
	auto [l, r, type, align] = segs[s];
	if (type)
	{
		int el = align - w[r], er = align;
		if (el <= x && x < er) return true;
		return false; 
	}
	else
	{
		int el = align, er = align + w[r];
		if (el <= x && x < er) return true;
		return false;
	}
}

void solve()
{
	int n, q;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> w[i];
	segs.clear();
	segs.pb(seg(1, n, false, 0));
	cin >> q;
	int mode, x;
	for (int i = 1; i <= q; i++) 
	{
		cin >> mode >> x;
		if (mode == 1)
		{
			while (segs.back().r < x) segs.pop_back();
			int lef_x = segs.back().align;
			if (segs.back().type) lef_x -= w[x];
			while (segs.size() && segs.back().r <= x) segs.pop_back();
			if (segs.size() && segs.back().l <= x) segs.back().l = x + 1;
			segs.push_back(seg(1, x, false, lef_x));
		}
		else if (mode == 2)
		{
			while (segs.back().r < x) segs.pop_back();
			int rig_x = segs.back().align;
			if (!segs.back().type) rig_x += w[x];
			while (segs.size() && segs.back().r <= x) segs.pop_back();
			if (segs.size() && segs.back().l <= x) segs.back().l = x + 1;
			segs.push_back(seg(1, x, true, rig_x));
		}
		else
		{
			int ls = 0, rs = segs.size() - 1, s = -1;
			while (ls <= rs)
			{
				int mid = (ls + rs) >> 1;
				if (checkseg(mid, x)) s = mid, ls = mid + 1;
				else rs = mid - 1;
			}
			if (s == -1)
			{
				cout << 0 << endl;
				continue;
			}
			auto [l, r, type, align] = segs[s];
			int ans = 0;
			while (l <= r)
			{
				int mid = (l + r) >> 1;
				int ml = align, mr = align;
				if (type) ml -= w[mid];
				else mr += w[mid];
				if (ml <= x && x < mr) ans = mid, r = mid - 1;
				else l = mid + 1;
			}
			cout << n + 1 - ans << endl;
		}
	}
	return;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr);
	int _ = 1;
	if (multi_test) cin >> _;
	while (_--) solve();
	return 0;
}