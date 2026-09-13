// Problem: B. Culling Game
// Contest: Codeforces - Codeforces Round 1120 (Div. 1)
// URL: https://codeforces.com/contest/2262/problem/B
// Memory Limit: 256 MB
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

bool multi_test = true;

struct bit
{
	ll val[200001];
	int n;
	
	void clear(int _n)
	{
		n = _n;
		for (int i = 1; i <= n; i++) val[i] = 0;
	}
	
	void update(int p, int x)
	{
		while (p <= n)
		{
			val[p] += (ll)x;
			p += lowbit(p);
		}
	}
	
	ll query(int p)
	{
		ll res = 0;
		while (p)
		{
			res += val[p];
			p -= lowbit(p);
		}
		return res;
	}
}t;

struct c
{
	int l, r;
	
	c(int _l, int _r) : l(_l), r(_r) {}

	bool operator < (const c a) const
	{
		return r < a.r;
	}
};

int a[200001], p[200001];
void solve()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> p[i];
	t.clear(n);
	set <c> S;
	S.insert(c(p[n], p[n]));
	t.update(p[n], a[p[n]]);
	int minp = p[n];
	vector <int> ans;
	ans.pb(0);
	for (int i = n - 1; i >= 1; i--)
	{
		if (minp > p[i])
		{
			vector <set <c> :: iterator> del;
			ll accu = a[p[i]];
			int r = p[i];
			for (auto it = S.begin(); it != S.end(); it++)
			{
				auto cur = *it;
				int curl = a[cur.l];
				ll curs = t.query(cur.r) - t.query(cur.l - 1);
				if (accu >= curl) 
				{
					accu += curs;
					r = cur.r;
					del.pb(it);
				}
				else break;
			}
			for (auto it : del) S.erase(it);
			S.insert(c(p[i], r));
		}
		else
		{
			auto it = S.lower_bound(c(p[i], p[i]));
			if (it == S.end())
			{
				it--;
				auto cur = *it;
				if (t.query(cur.r) - t.query(cur.l - 1) < a[p[i]]) S.insert(c(p[i], p[i]));
				else S.erase(it), S.insert(c(cur.l, p[i]));
			}
			else
			{
				auto cur = *it;
				vector <set <c> :: iterator> del;
				vector <c> ins;
				if (cur.l < p[i])
				{
					ll accu = t.query(p[i] - 1) - t.query(cur.l - 1);
					int l = 0, r = 0;
					del.pb(it);
					if (accu >= a[p[i]]) accu = t.query(cur.r) - t.query(cur.l - 1) + a[p[i]], l = cur.l, r = cur.r;
					else accu = t.query(cur.r) + a[p[i]] - t.query(p[i]), ins.pb(c(cur.l, p[i] - 1)), l = p[i], r = cur.r;
					it++;
					while (it != S.end())
					{
						cur = *it;
						int curl = a[cur.l];
						ll curs = t.query(cur.r) - t.query(cur.l - 1);
						if (accu >= curl) 
						{
							accu += curs;
							r = cur.r;
							del.pb(it);
							it++;
						}
						else break;
					}
					for (auto it : del) S.erase(it);
					for (auto it : ins) S.insert(it);
					S.insert(c(l, r));
				}
				else
				{
					auto lit = --it;
					auto las = *lit;
					ll accu = t.query(las.r) - t.query(las.l - 1);
					int l = 0, r = 0;
					if (accu >= a[p[i]]) accu += a[p[i]], del.pb(lit), l = las.l, r = p[i];
					else accu = a[p[i]], l = p[i], r = p[i];
					it++;
					while (it != S.end())
					{
						cur = *it;
						int curl = a[cur.l];
						ll curs = t.query(cur.r) - t.query(cur.l - 1);
						if (accu >= curl) 
						{
							accu += curs;
							r = cur.r;
							del.pb(it);
							it++;
						}
						else break;
					}
					for (auto it : del) S.erase(it);
					S.insert(c(l, r));
				}
			}
		}
		// cerr << "cur: " << i << ' ' << p[i] << endl;
		// for (auto cur : S) cerr << cur.l << ' ' << cur.r << endl;
		minp = min(minp, p[i]);
		t.update(p[i], a[p[i]]);
		ans.pb(S.size() - 1);
	}
	reverse(ans.begin(), ans.end());
	for (auto x : ans) cout << x << ' ';
	cout << endl;
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