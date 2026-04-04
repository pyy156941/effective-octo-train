// Problem: C1. Interactive Graph (Simple Version)
// Contest: Codeforces - Codeforces Round 1079 (Div. 1)
// URL: https://codeforces.com/contest/2196/problem/C1
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

bool multiTest = true;

pair <int, vector <int>> Query(int k)
{
	cout << "? " << k << endl;
	int l, x;
	cin >> l;
	if (l == -1) exit(0);
	vector <int> res;
	for (int i = 1; i <= l; i++) cin >> x, res.pb(x);
	return {l, res};
}

int st[31], l[31];
void Solve()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) st[i] = l[i] = 0;
	st[1] = 1;
	int cur_k = 2;
	vector <pair <int, int>> ans;
	pair <int, vector <int>> las = {1, {1}};
	while (true)
	{
		auto cur = Query(cur_k);
		if (!cur.first) break;
		if (cur.first > 1) ans.pb({cur.second[cur.first - 2], cur.second[cur.first - 1]});
		if (cur.first <= las.first) // something ended
		{
			// cerr << "CUR: " << cur_k << endl << "DELETE: ";
			for (int i = cur.first - 1; i < las.first; i++) if (!l[las.second[i]]) l[las.second[i]] = cur_k - st[las.second[i]];
			// cerr << endl;
		} 
		int las_of_cur = cur.second[cur.first - 1];
		if (!st[las_of_cur]) st[las_of_cur] = cur_k;
		if (l[las_of_cur]) cur_k += l[las_of_cur]; 
		else cur_k++;
		las = cur;
		bool ok = true;
		for (int i = 1; i <= n; i++) 
		{
			if (!l[i]) 
			{
				ok = false;
				break;
			}
		}
		if (ok) break;
	}
	// cerr << "ST L\n";
	// for (int i = 1; i <= n; i++) cerr << st[i] << ' ' << l[i] << endl;
	// cerr << "ST L\n";
	cout << "! " << ans.size() << endl;
	for (auto [fi, se] : ans) cout << fi << ' ' << se << endl;
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