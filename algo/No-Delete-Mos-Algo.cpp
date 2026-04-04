#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int n, q;
int blocksiz;
int L[320], R[320];

int getBlock(int p)
{
	return ceil((double)p / blocksiz);
}

struct Query
{
	int l, r, id;
	const bool operator < (const Query a)
	{
		if (getBlock(l) != getBlock(a.l)) return getBlock(l) < getBlock(a.l);
		return r < a.r;
	}
}Q[100001];
long long ans[100001];
int val[100001];
int a[100001], t[100001], cnt[100001], cnt2[100001];

long long bruteQuery(int l, int r)
{
	long long ans = 0;
	for (int i = l; i <= r; i++) cnt2[a[i]] = 0;
	for (int i = l; i <= r; i++)
	{
		cnt2[a[i]]++;
		ans = max(ans, (long long)cnt2[a[i]] * t[a[i]]);
	}
	return ans;
}

int main()
{
	int m = 0;
	cin >> n >> q;
	blocksiz = sqrt(n);
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		t[++m] = a[i];
	}
  	sort(t + 1, t + 1 + m);
  	m = unique(t + 1, t + 1 + m) - (t + 1);
  	for (int i = 1; i <= n; i++) a[i] = lower_bound(t + 1, t + 1 + m, a[i]) - t;
	for (int i = 1; i <= q; i++)
	{
		cin >> Q[i].l >> Q[i].r;
		Q[i].id = i;
	}
	for (int cur = 1, p = 1; cur <= n; p++)
	{
		L[p] = cur;
		R[p] = min(n, cur + blocksiz - 1);
		cur += blocksiz;
	}
	sort(Q + 1, Q + q + 1);
	int l = 1, r = 0;
	long long ans1 = 0, ans2 = 0;
	for (int i = 1; i <= q; i++)
	{
		int br = R[getBlock(Q[i].l)];
		if (i == 1 || getBlock(Q[i].l) != getBlock(Q[i - 1].l))
		{
			l = br + 1;
			r = br;
			ans1 = 0;
			for (int j = 1; j <= m; j++) cnt[j] = 0;
		}
		if (getBlock(Q[i].l) == getBlock(Q[i].r)) 
		{
			ans[Q[i].id] = bruteQuery(Q[i].l, Q[i].r);
			continue;
		}
		while (r < Q[i].r) 
		{
   			cnt[a[++r]]++;
   			ans1 = max(ans1, (long long)cnt[a[r]] * t[a[r]]);
  		}
  		ans2 = ans1;
  		while (l > Q[i].l) 
  		{
   			cnt[a[--l]]++;
   			ans2 = max(ans2, (long long)cnt[a[l]] * t[a[l]]);
  		}	
  		ans[Q[i].id] = ans2;
  		while (l < br + 1) cnt[a[l++]]--;
	}
	for (int i = 1; i <= q; i++) cout << ans[i] << endl;
	return 0;
}