#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

const long long mod = 1000000007ll;
int n, m;
long long seed, vmax;
long long a[100001];

long long Rnd()
{
	long long ret = seed;
	seed = (seed * 7ll + 13ll) % mod;
	return ret;
}

struct Node
{
	int l, r;
	mutable long long v;
	Node(int _l = 0, int _r = 0, long long _v = 0)
	{
		l = _l, r = _r, v = _v;
	}
	bool operator < (const Node a) const // strange
	{
		return l < a.l;
	}
};

bool CMP(Node a, Node b)
{
	return a.v < b.v;
}

set <Node> ODT;
auto Split(int x)
{
	 auto it = --ODT.upper_bound(Node(x, 0, 0));
//	 cout << it -> l << ' ' << it -> r << ' ' << it -> v << endl;
	 if (it -> l == x) return it;
	 int l = it -> l, r = it -> r;
	 long long v = it -> v; // problem here. int -> long long to avoid WA #3 101st
	 ODT.erase(it);
	 ODT.insert(Node(l, x - 1, v));
	 auto res = ODT.insert(Node(x, r, v)).first;
//	 for (auto iter : ODT) cout << iter.l << ' ' << iter.r << ' ' << iter.v << endl;
	 return res;
}

void Assign(int l, int r, long long x)
{
	auto itr = Split(r + 1);
	auto itl = Split(l);
	ODT.erase(itl, itr);
	ODT.insert(Node(l, r, x));
}

void Add(int l, int r, long long x)
{
	auto itr = Split(r + 1);
	auto itl = Split(l);
	while (itl != itr)
	{
		itl -> v += x;
		itl++;
	}
}

Node tmp[100001];
int cnt = 0;
long long QueryKth(int l, int r, int k)
{
	cnt = 0;
	auto itr = Split(r + 1);
	auto itl = Split(l);
	while (itl != itr)
	{
		tmp[++cnt] = (*itl);
		itl++;
	}
	sort(tmp + 1, tmp + cnt + 1, CMP);
	int cur = 1;
	while (k > tmp[cur].r - tmp[cur].l + 1)
	{
		k -= tmp[cur].r - tmp[cur].l + 1;
		cur++;
	}
	return tmp[cur].v;
}

long long QPow(long long a, long long b, long long p)
{
	long long ans = 1;
	a %= p;
	while (b)
	{
		if (b % 2) ans = (ans * a) % p;
		a = (a * a) % p;
		b >>= 1;
	}
	return ans;
}

long long QueryPow(int l, int r, long long x, long long y)
{
	long long ans = 0;
	auto itr = Split(r + 1);
	auto itl = Split(l);
	while (itl != itr)
	{
		ans = (ans + (itl -> r - itl -> l + 1) * QPow(itl -> v, x, y) % y) % y;
		itl++;
	}
	return ans;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int mode, l, r;
	long long x, y;
	cin >> n >> m >> seed >> vmax;
	for (int i = 1; i <= n; i++)
	{
		a[i] = (Rnd() % vmax) + 1ll;
		ODT.insert(Node(i, i, a[i]));
	}
	for (int i = 1; i <= m; i++)
	{
		mode = (Rnd() % 4) + 1ll;
		l = (Rnd() % n) + 1ll;
		r = (Rnd() % n) + 1ll;
		if (l > r) swap(l, r);
		if (mode == 3) x = (Rnd() % (r - l + 1)) + 1ll;
		else x = (Rnd() % vmax) + 1ll;
		if (mode == 4) y = (Rnd() % vmax) + 1ll;
		if (mode == 1)
		{
//			cout << "1 " << l << ' ' << r << ' ' << x << endl;
			Add(l, r, x);
		}
		else if (mode == 2)
		{
//			cout << "2 " << l << ' ' << r << ' ' << x << endl;
			Assign(l, r, x);
		}
		else if (mode == 3)
		{
//			cout << "3 " << l << ' ' << r << ' ' << x << endl;
			cout << QueryKth(l, r, x) << endl;
		}
		else 
		{
//			cout << "4 " << l << ' ' << r << ' ' << x << ' ' << y << endl;
			cout << QueryPow(l, r, x, y) << endl;
		}
//		cout << endl;
//		for (auto iter : ODT) cout << iter.l << ' ' << iter.r << ' ' << iter.v << endl;
//		cout << endl;
	}
	return 0;
}