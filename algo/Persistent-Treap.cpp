#include <bits/stdc++.h>

using namespace std;

int rt[500001], cnt = 0;
struct Node
{
	int val, key, ls, rs, siz;
}tree[25000001];

mt19937 rng(time(0));
int NewNode(int val)
{
	cnt++;
	tree[cnt].val = val;
	tree[cnt].key = rng();
	tree[cnt].siz = 1;
	return cnt;
}

inline void Pushup(int cur)
{
	tree[cur].siz = tree[tree[cur].ls].siz + tree[tree[cur].rs].siz + 1;
}

pair <int, int> Split(int cur, int val)
{
	if (!cur) return make_pair(0, 0);
	int s = NewNode(tree[cur].val);
	tree[s] = tree[cur];
	pair <int, int> res;
	if (tree[cur].val <= val)
	{
		res = Split(tree[cur].rs, val);
		tree[s].rs = res.first;
		res.first = s;
	}
	else
	{
		res = Split(tree[cur].ls, val);
		tree[s].ls = res.second;
		res.second = s;
	}
	Pushup(s);
	return res;
}


int Merge(int x, int y)
{
	if (!x || !y) return x + y;
	if (tree[x].key < tree[y].key)
	{
		tree[x].rs = Merge(tree[x].rs, y);
		Pushup(x);
		return x;
	}
	else
	{
		tree[y].ls = Merge(x, tree[y].ls);
		Pushup(y);
		return y; 
	}
}

inline void Insert(int val, int &rt)
{
	auto x = Split(rt, val);
	rt = Merge(Merge(x.first, NewNode(val)), x.second);
}

inline void Remove(int val, int &rt)
{
	auto x = Split(rt, val); 
	auto y = Split(x.first, val - 1); 
	y.second = Merge(tree[y.second].ls, tree[y.second].rs);
	rt = Merge(Merge(y.first, y.second), x.second);
}

int getRank(int val, int &rt)
{
	auto x = Split(rt, val - 1);
	int res = tree[x.first].siz + 1;
	rt = Merge(x.first, x.second);
	return res;
}

int getValue(int rnk, int &rt)
{
	int cur = rt;
	while (cur)
	{
		if (tree[tree[cur].ls].siz + 1 == rnk) break;
		else if (tree[tree[cur].ls].siz >= rnk) cur = tree[cur].ls;
		else
		{
			rnk -= tree[tree[cur].ls].siz + 1;
			cur = tree[cur].rs;
		}
	}
	return tree[cur].val;
}

int prePro(int val, int &rt)
{
	auto x = Split(rt, val - 1);
	int cur = x.first;
	while (tree[cur].rs) cur = tree[cur].rs;
	int res = tree[cur].val;
	rt = Merge(x.first, x.second);
	return res;
}

int postPro(int val, int &rt)
{
	auto x = Split(rt, val);
	int cur = x.second;
	while (tree[cur].ls) cur = tree[cur].ls;
	int res = tree[cur].val;
	rt = Merge(x.first, x.second);
	return res;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int n;
	cin >> n;
	int v, mode, x;
	Insert(-2147483647, rt[0]);
	Insert(2147483647, rt[0]);
	for (int i = 1; i <= n; i++)
	{
		cin >> v >> mode >> x;
		rt[i] = rt[v];
		if (mode == 1) Insert(x, rt[i]);
		else if (mode == 2) Remove(x, rt[i]);
		else if (mode == 3) cout << getRank(x, rt[i]) - 1 << endl;
		else if (mode == 4) cout << getValue(x + 1, rt[i]) << endl;
		else if (mode == 5) cout << prePro(x, rt[i]) << endl;
		else cout << postPro(x, rt[i]) << endl;
	}
}