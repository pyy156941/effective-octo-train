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

bool multiTest = false;

int n, m, q;
int lim;
int t[200001], p[200001];
vector <int> ts[200001], tsi[200001];
map <int, int> lmp;
bool mark[200001];
int ans[470][200001];
int pref[200001];

int BruteSolve(int a, int b)
{
	int pa = 0, pb = 0;
	bool ca = false, cb = false;
	int lst = 0, res = 0;
	while (pa < ts[a].size() || pb < ts[b].size())
	{
		if (pb >= ts[b].size() || (pa < ts[a].size() && ts[a][pa] < ts[b][pb]))
		{
//			cerr << "A : " << ts[a][pa] << endl; 
			if (ca && cb) res += ts[a][pa] - lst;
			lst = ts[a][pa];
			ca ^= true;
			pa++;
		}
		else
		{
//			cerr << "B : " << ts[b][pb] << endl;
			if (ca && cb) res += ts[b][pb] - lst;
			lst = ts[b][pb];
			cb ^= true;
			pb++;
		}
	}
	return res;
}

void Solve()
{
	cin >> n >> m;
	lim = sqrt(m);
	for (int i = 1; i <= m; i++)
	{
		cin >> t[i] >> p[i];
		ts[p[i]].pb(t[i]);
		tsi[p[i]].pb(i);
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		if (ts[i].size() > lim)
		{
			mark[i] = true;
			lmp[i] = ++cnt;
			bool in = false;
			for (int j = 1; j <= m; j++)
			{
				pref[j] = pref[j - 1];
				if (in) pref[j] += t[j] - t[j - 1];
				if (p[j] == i) in ^= true;
//				cerr << pref[j] << ' ';
			}
//			cerr << endl;
			for (int j = 1; j <= n; j++)
			{
				if (j == i) continue;
				for (int k = 0; k < tsi[j].size(); k++)
				{
					if (k % 2) ans[cnt][j] += pref[tsi[j][k]];
					else ans[cnt][j] -= pref[tsi[j][k]];
				}
			}
		}
	}
	cin >> q;
	int a, b;
	for (int i = 1; i <= q; i++)
	{
		cin >> a >> b;
		if (!mark[a] && !mark[b]) 
		{
			cout << BruteSolve(a, b) << '\n';
			continue;
		}
		if (mark[a])
		{
			cout << ans[lmp[a]][b] << '\n';
			continue;
		}
		if (mark[b])
		{
			cout << ans[lmp[b]][a] << '\n';
			continue;
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