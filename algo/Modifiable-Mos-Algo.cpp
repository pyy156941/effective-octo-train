#include <iostream>
#include <cmath>
#include <cassert>
#include <algorithm>

using namespace std;

int n, m, blocksiz;
int a[133334], b[133334];

int getBlock(int p)
{
	return ceil((double)p / blocksiz);
}

struct Query
{
	int l, r, id, time; // for modifications, l = place, r = val
	const bool operator < (const Query a)
	{
		if (getBlock(l) != getBlock(a.l)) return l < a.l;
		if (getBlock(r) != getBlock(a.r)) return r < a.r;
		return time < a.time;
	}
}Q[133334], M[133334];
int cq = 0, cm = 0;

int curans = 0;
int cnt[1000001], ans[133334];

void Add(int val)
{
	if (cnt[val] == 0) curans++;
	cnt[val]++;
}

void Del(int val)
{
	cnt[val]--;
	if (cnt[val] == 0) curans--;
}

int main()
{
	char mode[5];
	cin >> n >> m;
	blocksiz = cbrt(n) * cbrt(n);
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		b[i] = a[i];
	}
	for (int i = 1; i <= m; i++)
	{
		cin >> mode;
		if (mode[0] == 'Q')
		{
			++cq;
			Q[cq].id = cq;
			Q[cq].time = cm;
			cin >> Q[cq].l >> Q[cq].r;
		}
		else 
		{
			++cm;
			cin >> M[cm].l >> M[cm].r;
			M[cm].time = b[M[cm].l];
			b[M[cm].l] = M[cm].r;
		}
	}
	sort(Q + 1, Q + cq + 1);
	int l = 1, r = 0, t = 0;
	for (int i = 1; i <= cq; i++)
	{
		while (l > Q[i].l) Add(a[--l]);
		while (r < Q[i].r) Add(a[++r]);
		while (l < Q[i].l) Del(a[l++]);
		while (r > Q[i].r) Del(a[r--]);
		while (t > Q[i].time)
		{
			if (l <= M[t].l && M[t].l <= r)
			{
				Del(a[M[t].l]);
				Add(M[t].time);			
//				assert(M[t].r == a[M[t].l]);	
			}
			a[M[t].l] = M[t].time;
			t--;
		}
		while (t < Q[i].time)
		{
			t++;
			if (l <= M[t].l && M[t].l <= r)
			{
				Del(a[M[t].l]);
				Add(M[t].r);
//				assert(M[t].time == a[M[t].l]);
			}
			a[M[t].l] = M[t].r;
		}
		ans[Q[i].id] = curans;
	}
	for (int i = 1; i <= cq; i++) cout << ans[i] << endl;
	return 0;
}