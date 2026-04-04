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
pair <int, int> c[200001];
int tmpx[200001], tmpy[200001], cntx = 0, cnty = 0;
vector <int> lis[200001];

struct SGT
{
	int tree[800001];

	void Pushup(int cur)
	{
		tree[cur] = tree[ls(cur)] + tree[rs(cur)];
	}
	
	void Build(int cur, int s, int t)
	{
		if (s == t)
		{
			tree[cur] = 0;
			return;
		}
		int mid = (s + t) >> 1;
		Build(ls(cur), s, mid);
		Build(rs(cur), mid + 1, t);
		Pushup(cur);
	}
	
	void Add(int cur, int p, int s, int t, int x)
	{
		if (s == t)
		{
			tree[cur] += x;
			return;
		}
		int mid = (s + t) >> 1;
		if (p <= mid) Add(ls(cur), p, s, mid, x);
		if (p > mid) Add(rs(cur), p, mid + 1, t, x);
		Pushup(cur);
	}
	
	int Query(int cur, int s, int t, int sum)
	{
		if (s == t) return s;
		int mid = (s + t) >> 1;
		if (tree[ls(cur)] >= sum) return Query(ls(cur), s, mid, sum);
		else return Query(rs(cur), mid + 1, t, sum - tree[ls(cur)]);
	}
	
}sl, sr;

pair <int, int> Check(int x)
{
	sl.Build(1, 1, cnty);
	sr.Build(1, 1, cnty);
	for (int i = 1; i <= cntx; i++)
	{
		for (auto it : lis[i]) sr.Add(1, it, 1, cnty, 1);
	}
	int tot = 0;
	for (int i = 1; i < cntx; i++)
	{
		for (auto it : lis[i]) 
		{
			sl.Add(1, it, 1, cnty, 1);
			tot++;
			sr.Add(1, it, 1, cnty, -1);
		}
		if (tot < 2 * x || tot > n - 2 * x) continue;
		int ld = sl.Query(1, 1, cnty, x);
		int lu = sl.Query(1, 1, cnty, tot - x + 1) - 1; 
		int rd = sr.Query(1, 1, cnty, x);
		int ru = sr.Query(1, 1, cnty, n - tot - x + 1) - 1;
//		cerr << x << ' ' << i << ' ' << tot << ' ' << ld << ' ' << lu << ' ' << rd << ' ' << ru << endl;
		if (lu < ld || ru < rd) continue;
		if (max(ld, rd) > min(lu, ru)) continue;
		return {i + 1, max(ld, rd) + 1};
	}
	return {0, 0};
}

void Solve()
{
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> c[i].first >> c[i].second;
	cntx = cnty = 0;
	for (int i = 1; i <= n; i++) tmpx[++cntx] = c[i].first;
	sort(tmpx + 1, tmpx + cntx + 1);
	cntx = unique(tmpx + 1, tmpx + cntx + 1) - tmpx - 1;
	for (int i = 1; i <= n; i++) c[i].first = lower_bound(tmpx + 1, tmpx + cntx + 1, c[i].first) - tmpx;
	for (int i = 1; i <= n; i++) tmpy[++cnty] = c[i].second;
	sort(tmpy + 1, tmpy + cnty + 1);
	cnty = unique(tmpy + 1, tmpy + cnty + 1) - tmpy - 1;
	for (int i = 1; i <= n; i++) c[i].second = lower_bound(tmpy + 1, tmpy + cnty + 1, c[i].second) - tmpy;
	for (int i = 1; i <= cntx; i++) lis[i].clear();
	for (int i = 1; i <= n; i++) lis[c[i].first].push_back(c[i].second);
	for (int i = 1; i <= cntx; i++) sort(lis[i].begin(), lis[i].end());
	int l = 0, r = n / 4;
	pair <int, pair <int, int>> ans;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		auto res = Check(mid);
		cerr << mid << ' ' << res.first << ' ' << res.second << endl;
		if (res.first == 0 && res.second == 0) r = mid - 1;
		else l = mid + 1, ans.first = mid, ans.second = res;
	}
	cout << ans.first << '\n';
	cout << tmpx[ans.second.first] << ' ' << tmpy[ans.second.second] << '\n';
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