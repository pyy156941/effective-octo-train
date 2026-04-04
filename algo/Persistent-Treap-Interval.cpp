#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
random_device rd;
mt19937 rng(rd());
int n, cnt = 0;
int rt[200001];
struct Node
{
	int ls, rs, siz;
	ll val, sum;
	bool ltr;
	int key;
}tree[25700001];

inline int NewNode(ll val)
{
	tree[++cnt].siz = 1;
	tree[cnt].val = val;
	tree[cnt].sum = val;
	tree[cnt].ltr = 0;
	tree[cnt].key = rng();
	return cnt;
}

inline int DupNode(int cur)
{
	tree[++cnt] = tree[cur];
	return cnt;
}

inline void Pushup(int cur)
{
	tree[cur].sum = tree[tree[cur].ls].sum + tree[tree[cur].rs].sum + tree[cur].val;
	tree[cur].siz = tree[tree[cur].ls].siz + tree[tree[cur].rs].siz + 1;
}

inline void Pushdown(int cur)
{
	if (tree[cur].ltr)
	{
		if (tree[cur].ls) tree[cur].ls = DupNode(tree[cur].ls);
		if (tree[cur].rs) tree[cur].rs = DupNode(tree[cur].rs);
		swap(tree[cur].ls, tree[cur].rs); // Move upwards 642
		if (tree[cur].ls) tree[tree[cur].ls].ltr ^= 1;
		if (tree[cur].rs) tree[tree[cur].rs].ltr ^= 1;
		tree[cur].ltr = 0;
	}
}

pair <int, int> Split(int cur, int siz)
{
	if (!cur) return make_pair(0, 0);
	Pushdown(cur); // Pushdown before dupping
	int s = DupNode(cur);
	pair <int, int> res;
	if (tree[tree[cur].ls].siz >= siz)
	{
		res = Split(tree[cur].ls, siz);
		tree[s].ls = res.second;
		res.second = s;	
	}
	else
	{
		res = Split(tree[cur].rs, siz - tree[tree[cur].ls].siz - 1);
		tree[s].rs = res.first;
		res.first = s;
	}
	Pushup(s);
	return res;
}

int Merge(int x, int y)
{
	if (!x || !y) return x + y;	
	if (tree[x].key <= tree[y].key)
	{
		Pushdown(x);
		tree[x].rs = Merge(tree[x].rs, y);
		Pushup(x);
		return x;
	} 
	else
	{
		Pushdown(y);
		tree[y].ls = Merge(x, tree[y].ls);
		Pushup(y);
		return y;
	}
}

void Insert(int p, ll x, int &rt)
{
	auto y = Split(rt, p);
	rt = Merge(Merge(y.first, NewNode(x)), y.second);
}

void Remove(int p, int &rt)
{
	auto x = Split(rt, p - 1);
	auto y = Split(x.second, 1);
	rt = Merge(x.first, y.second);
}

void Reverse(int l, int r, int &rt)
{
	auto x = Split(rt, l - 1);
	auto y = Split(x.second, r - l + 1);
	tree[y.first].ltr ^= 1;
	rt = Merge(Merge(x.first, y.first), y.second); // 657
}

ll Add(int l, int r, int &rt)
{
	auto x = Split(rt, l - 1);
	auto y = Split(x.second, r - l + 1);
	ll res = tree[y.first].sum;
	rt = Merge(Merge(x.first, y.first), y.second);
	return res;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	int v, mode;
	ll x, l, r, p, lastans = 0;
	for (int i = 1; i <= n; i++)
	{
		cin >> v >> mode;
		rt[i] = rt[v];
		if (mode == 1)
		{
			cin >> p >> x;
			p ^= lastans;
			x ^= lastans;
			Insert(p, x, rt[i]);
		}
		else if (mode == 2)
		{
			cin >> p;
			p ^= lastans;
			Remove(p, rt[i]);
		}
		else if (mode == 3)
		{
			cin >> l >> r;
			l ^= lastans;
			r ^= lastans;
			Reverse(l, r, rt[i]);
		}
		else
		{
			cin >> l >> r;
			l ^= lastans;
			r ^= lastans;
			lastans = Add(l, r, rt[i]);
			cout << lastans << endl;
		}
	}
}