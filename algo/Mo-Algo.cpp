#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int n, m;
int blocksiz; // belong: ceil(i / blocksiz)
int l[50001], r[50001], a[50001];
int cl, cr;

int getBlock(int p)
{
	return ceil((double)p / blocksiz);
}

struct Query
{
	int l, r, id;
	const bool operator < (const Query a) const
	{
		if (getBlock(l) != getBlock(a.l)) return l < a.l;
		return (getBlock(l) & 1) ? r < a.r : r > a.r;
	}
}Q[50001];
long long cnt[50001];
long long nom[50001], den[50001];
long long sum = 0;

void Add(int pos)
{
	cnt[a[pos]]++;
	sum += (long long)2ll * cnt[a[pos]] - 1ll;
}

void Del(int pos)
{
	cnt[a[pos]]--;
	sum -= (long long)2ll * cnt[a[pos]] + 1ll;
}

long long gcd(long long a, long long b)
{
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return gcd(b, a % b);
}

int main()
{
	cin >> n >> m;
	blocksiz = sqrt(n);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= m; i++)
	{
		cin >> Q[i].l >> Q[i].r;
		Q[i].id = i;
	}
	cl = 1, cr = 0;
	sort(Q + 1, Q + m + 1);
	for (int i = 1; i <= m; i++)
	{
		if (Q[i].l == Q[i].r)
		{
			nom[Q[i].id] = 0;
			den[Q[i].id] = 1;
			continue;
		}
		while (cl > Q[i].l) Add(--cl);
		while (cr < Q[i].r) Add(++cr);
		while (cl < Q[i].l) Del(cl++);
		while (cr > Q[i].r) Del(cr--);
		nom[Q[i].id] = sum - (long long)(Q[i].r - Q[i].l + 1ll);
		den[Q[i].id] = (long long)(Q[i].r - Q[i].l + 1ll) * (Q[i].r - Q[i].l);
		long long _gcd = gcd(nom[Q[i].id], den[Q[i].id]);
		nom[Q[i].id] /= _gcd, den[Q[i].id] /= _gcd;
	}
	for (int i = 1; i <= m; i++) cout << nom[i] << '/' << den[i] << endl;
	return 0;
}