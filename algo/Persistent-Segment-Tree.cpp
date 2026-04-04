#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

struct Node
{
	int ls, rs, val;
}tree[3200001];

int n, m;
int cnt = 0, acnt = 0;
int rt[100001];
int te[100001], a[100001];

void Pushup(int cur)
{
	tree[cur].val = tree[tree[cur].ls].val + tree[tree[cur].rs].val;
}

int Build(int l, int r)
{
	int node = ++cnt;
	if (l == r) return node;
	int mid = (l + r) >> 1;
	tree[node].ls = Build(l, mid);
	tree[node].rs = Build(mid + 1, r);
	return node;
}

int Update(int cur, int s, int t, int p, int x)
{
	int node = ++cnt;
	tree[node].ls = tree[cur].ls;
	tree[node].rs = tree[cur].rs;
	tree[node].val = tree[cur].val + x;
	if (s == t)
	{
//		tree[node].val += x;
		return node;
	}
	int mid = (s + t) >> 1;
	if (p <= mid) tree[node].ls = Update(tree[node].ls, s, mid, p, x);
	if (p > mid) tree[node].rs = Update(tree[node].rs, mid + 1, t, p, x);
//	Pushup(cur);
	return node;
}

int QueryKth(int rt1, int rt2, int s, int t, int p)
{
	if (s == t) return s;
	int lsc = tree[tree[rt2].ls].val - tree[tree[rt1].ls].val; // larger - smaller
	int mid = (s + t) >> 1;
	if (p > lsc) return QueryKth(tree[rt1].rs, tree[rt2].rs, mid + 1, t, p - lsc);
	else return QueryKth(tree[rt1].ls, tree[rt2].ls, s, mid, p);
}

void ItTree(int cur, int l, int r)
{
	cout << tree[cur].val << ' ' << l << ' ' << r << endl;
	if (l == r) return;
	int mid = (l + r) >> 1;
	ItTree(tree[cur].ls, l, mid);
	ItTree(tree[cur].rs, mid + 1, r);
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		te[++acnt] = a[i];
	}
	sort(te + 1, te + acnt + 1);
	for (int i = 1; i <= n; i++) a[i] = lower_bound(te + 1, te + acnt + 1, a[i]) - te;
	rt[0] = Build(1, acnt);
	for (int i = 1; i <= n; i++) rt[i] = Update(rt[i - 1], 1, acnt, a[i], 1);
	int l, r, k;
	for (int i = 1; i <= m; i++)
	{
		cin >> l >> r >> k;
		cout << te[QueryKth(rt[l - 1], rt[r], 1, acnt, k)] << endl;
	}
	return 0;
}