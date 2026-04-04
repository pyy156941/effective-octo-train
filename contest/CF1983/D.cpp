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
int a[100001], b[100001];
set <int> S;
map <int, int> mp;

int tree[100001];

void Add(int x, int p)
{
	while (p <= n)
	{
		tree[p] += x;
		p += lowbit(p);
	}
}

int Query(int p)
{
	int ans = 0;
	while (p)
	{
		ans += tree[p];
		p -= lowbit(p);
	}
	return ans;
}

void Solve()
{
	cin >> n;
	S.clear();
	mp.clear();
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		mp[a[i]] = i;
		S.insert(a[i]);
//		cerr << a[i] << ' ';
	}
//	cerr << endl;
//	for (auto it : S) cerr << it << ' ';
//	cerr << endl;
	bool flag = true;
	for (int i = 1; i <= n; i++)
	{
		cin >> b[i];
		if (S.find(b[i]) == S.end()) flag = false;
		if (flag) S.erase(S.find(b[i]));
	}
	if (!flag)
	{
		ync(0);
		return;
	}
	ll binv = 0;
	for (int i = n; i >= 1; i--)
	{
		b[i] = mp[b[i]];
		binv += (ll)Query(b[i] - 1);
		Add(1, b[i]);
	}
//	cerr << binv << endl;
	for (int i = 1; i <= n; i++) Add(-1, b[i]);
	if (binv % 2 == 0) ync(1);
	else ync(0);
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