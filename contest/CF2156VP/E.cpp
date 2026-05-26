// Problem: E. Best Time to Buy and Sell Stock
// Contest: Codeforces - Codeforces Round 1061 (Div. 2)
// URL: https://codeforces.com/contest/2156/problem/E
// Memory Limit: 256 MB
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

bool multi_test = true;

struct bit
{
	int n;
	int tree[100001];
	
	void clear(int _n)
	{
		n = _n;
		for (int i = 0; i <= n; i++) tree[i] = 0;
	}
	
	void update(int p, int x)
	{
		while (p <= n)
		{
			tree[p] += x;
			p += lowbit(p);
		}
	}
	
	int query(int p)
	{
		int res = 0;
		while (p)
		{
			res += tree[p];
			p -= lowbit(p);
		}
		return res;
	}
}t;

int n;
ll a[100001], mp[100001], acnt = 0;
int deg[100001], cnt[4];

bool check(ll x)
{
	t.clear(acnt);
	cnt[0] = cnt[1] = cnt[2] = cnt[3] = 0;
	for (int i = 1; i <= n; i++) deg[i] = 0;
	for (int i = 1; i <= n; i++)
	{
		int li = upper_bound(mp + 1, mp + acnt + 1, mp[a[i]] - x) - mp - 1;
		deg[i] += t.query(li);
		t.update(a[i], 1);
	}
	t.clear(acnt);
	for (int i = n; i >= 1; i--)
	{
		int ri = lower_bound(mp + 1, mp + acnt + 1, mp[a[i]] + x) - mp - 1;
		deg[i] += t.query(acnt) - t.query(ri);
		t.update(a[i], 1);
	}
	for (int i = 1; i <= n; i++) 
	{
		if (!deg[i]) cnt[0]++;
		else if (deg[i] == 1) cnt[1]++;
		else if (deg[i] == 2) cnt[2]++;
		else cnt[3]++;
		// cerr << deg[i] << ' ';
	}
	// cerr << endl;
	// cerr << x << ' ' << cnt[0] << ' ' << cnt[1] << ' ' << cnt[2] << ' ' << cnt[3] << endl;
	if (cnt[3] > 1) return true;
	if (cnt[2] + cnt[3] < 2) return false;
	for (int i = 1; i <= n; i++) 
	{
		int rest = cnt[2] + cnt[3];
		if (deg[i] >= 2) rest--;
		if (deg[i] >= rest) 
		{
			bool ok = true;
			for (int j = 1; j <= n; j++)
			{
				if (i == j || deg[j] < 2) continue;
				if (deg[j] > 2)
				{
					ok = false;
					break;
				}
				if (j < i)
				{
					if (mp[a[i]] - mp[a[j]] < x) 
					{
						ok = false;
						break;
					}
				}
				else
				{
					if (mp[a[j]] - mp[a[i]] < x)
					{
						ok = false;
						break;
					}
				}
			}
			if (ok) return false;
		}
	}
	return true;
}

void solve()
{
	cin >> n;
	acnt = 0;
	ll mx = 0, mn = 2e9;
	for (int i = 1; i <= n; i++) 
	{
		cin >> a[i];
		mp[++acnt] = a[i];
		mx = max(mx, a[i]);
		mn = min(mn, a[i]);
	}
	sort(mp + 1, mp + acnt + 1);
	acnt = unique(mp + 1, mp + acnt + 1) - mp - 1;
	for (int i = 1; i <= n; i++) a[i] = lower_bound(mp + 1, mp + acnt + 1, a[i]) - mp;
	int l = mn - mx, r = mx - mn, ans = 0;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (check(mid)) l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	cout << ans << endl;
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