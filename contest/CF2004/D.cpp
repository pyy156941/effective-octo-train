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
vector <int> col[6]; // bg, br, by, gr, gy, ry
string pt[200001];
int cv[200001];
void Solve()
{
	int q, x, y;
	cin >> n >> q;
	for (int i = 0; i < 6; i++) col[i].clear();
	for (int i = 1; i <= n; i++)
	{
		cin >> pt[i];
		if (pt[i] == "BG") col[0].pb(i), cv[i] = 0;
		else if (pt[i] == "BR") col[1].pb(i), cv[i] = 1;
		else if (pt[i] == "BY") col[2].pb(i), cv[i] = 2;
		else if (pt[i] == "GR") col[3].pb(i), cv[i] = 3;
		else if (pt[i] == "GY") col[4].pb(i), cv[i] = 4;
		else col[5].pb(i), cv[i] = 5;
	}
	for (int _ = 1; _ <= q; _++)
	{
		cin >> x >> y;
		if (y < x) swap(x, y);
		if (pt[x][0] == pt[y][0] || pt[x][0] == pt[y][1] || pt[x][1] == pt[y][0] || pt[x][1] == pt[y][1]) 
		{
			cout << y - x << '\n';
			continue;
		}
		int ans = 1e9;
		for (int i = 0; i < 6; i++)
		{
			if (i == cv[x] || i == cv[y]) continue;
			auto it = lower_bound(col[i].begin(), col[i].end(), x);
			if (it != col[i].end())
			{
				int it_ = it - col[i].begin();
//				cerr << it_ << endl;
				if (col[i][it_] < y) 
				{
					ans = 0;
					break;
				}
				if (it_) ans = min(ans, x - col[i][it_ - 1]);
			}
			else
			{
				if (col[i].size()) ans = min(ans, x - col[i].back());
			}
			it = lower_bound(col[i].begin(), col[i].end(), y);
			if (it != col[i].end()) 
			{
				int it_ = it - col[i].begin();
				ans = min(ans, col[i][it_] - y);
			}
		}
		if (ans == 1e9) cout << "-1\n";
		else cout << y - x + 2 * ans << '\n';
	}
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