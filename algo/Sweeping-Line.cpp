#include <bits/stdc++.h>
#define ls(x) x << 1
#define rs(x) x << 1 | 1

using namespace std;

typedef long long ll;
int n;
struct Node
{
	int l, r;
	int p, val;
}tree[850001];

struct ych
{
	int x1, x2, val, cor;
	bool operator < (const ych a) const
	{
		return val < a.val;
	}
}r[200001];

int xc[200001], yc[200001], t[200001];
int cnt = 0;

void Pushup(int cur)
{
	if (tree[cur].p) tree[cur].val = tree[cur].r - tree[cur].l;
	else tree[cur].val = tree[ls(cur)].val + tree[rs(cur)].val;
}

void Build(int cur, int l, int r)
{
	tree[cur].l = t[l], tree[cur].r = t[r + 1];
	if (l == r) return;
	int mid = (l + r) >> 1;
	Build(ls(cur), l, mid);
	Build(rs(cur), mid + 1, r);
}

void Update(int cur, int l, int r, int s, int t, int x)
{
	if (l <= s && t <= r)
	{
		tree[cur].p += x;
		if (tree[cur].p) tree[cur].val = tree[cur].r - tree[cur].l;
		else if (s != t) tree[cur].val = tree[ls(cur)].val + tree[rs(cur)].val;
		else tree[cur].val = 0; // check leaf node
		return;
	}
	int mid = (s + t) >> 1;
	if (l <= mid) Update(ls(cur), l, r, s, mid, x);
	if (r > mid) Update(rs(cur), l, r, mid + 1, t, x);
	Pushup(cur);
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> xc[2 * i - 1] >> yc[2 * i - 1] >> xc[2 * i] >> yc[2 * i];
		t[++cnt] = xc[2 * i - 1];
		t[++cnt] = xc[2 * i];
	}
	sort(t + 1, t + cnt + 1);
	cnt = unique(t + 1, t + cnt + 1) - t - 1;
	for (int i = 1; i <= 2 * n; i++) xc[i] = lower_bound(t + 1, t + cnt + 1, xc[i]) - t;
	for (int i = 1; i <= n; i++)
	{
		 r[2 * i - 1].x1 = r[2 * i].x1 = xc[2 * i - 1];
		 r[2 * i - 1].x2 = r[2 * i].x2 = xc[2 * i];
		 r[2 * i - 1].val = yc[2 * i - 1], r[2 * i].val = yc[2 * i];
		 r[2 * i - 1].cor = 1, r[2 * i].cor = -1;
	}
	sort(r + 1, r + 2 * n + 1);
	ll ans = 0;
	Build(1, 1, cnt - 1);
	for (int i = 1; i <= 2 * n; i++)
	{
		int cv = r[i].val, ch = r[i - 1].val;
		if (i > 1) ans += (ll)(tree[1].val) * (cv - ch);
		Update(1, r[i].x1, r[i].x2 - 1, 1, cnt - 1, r[i].cor);
		while (r[i + 1].val == cv)
		{
			i++;
			Update(1, r[i].x1, r[i].x2 - 1, 1, cnt - 1, r[i].cor);
		}
	}
	cout << ans << endl;
	return 0;
}