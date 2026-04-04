#include <bits/stdc++.h>

using namespace std;

struct Node
{
	int tr[2];
	int siz, xs;
}tree[10000001];

int n;
int cnt = 1, rt = 1;
int stk[25], top = 0;

void Pushup(int cur)
{
	tree[cur].siz = tree[tree[cur].tr[0]].siz + tree[tree[cur].tr[1]].siz;
	tree[cur].xs = 0;
	if (tree[cur].tr[0]) tree[cur].xs ^= (tree[tree[cur].tr[0]].xs << 1);
	if (tree[cur].tr[1]) tree[cur].xs ^= (tree[tree[cur].tr[1]].xs << 1) | (tree[tree[cur].tr[1]].siz & 1);
}

void Insert(int x)
{
	int cur = rt;
	top = 0;
	for (int i = 0; i <= 21; i++)
	{
		int curd = (x & (1 << i) ? 1 : 0);
		stk[++top] = cur; 
		if (!tree[cur].tr[curd]) tree[cur].tr[curd] = ++cnt;
		cur = tree[cur].tr[curd];
	}
	tree[cur].siz++;
	while (top) Pushup(stk[top]), top--;
}

void Delete(int x)
{
	int cur = rt;
	top = 0;
	for (int i = 0; i <= 21; i++)
	{
		int curd = (x & (1 << i) ? 1 : 0);
		stk[++top] = cur;
		assert(tree[cur].tr[curd]);
		cur = tree[cur].tr[curd];
	}
	tree[cur].siz--;
	while (top) Pushup(stk[top]), top--;
}

void Incr(int cur)
{
	if (tree[cur].tr[1]) Incr(tree[cur].tr[1]);
	swap(tree[cur].tr[0], tree[cur].tr[1]);
	Pushup(cur);
}

vector <int> adj[525015];
int fa[525015], dep[525015], hson[525015], dfn[525015], rnk[525015], v[525015], siz[525015];
int dfc = 0;
int ans[525015];

void DFS1(int cur)
{
	siz[cur] = 1;
	for (auto it : adj[cur])
	{
		if (it == fa[cur]) continue;
		fa[it] = cur;
		dep[it] = dep[cur] + 1;
		DFS1(it);
		siz[cur] += siz[it];
		if (siz[it] > siz[hson[cur]] || !hson[cur]) hson[cur] = it;
	}
}

void DFS2(int cur)
{
	dfn[cur] = ++dfc;
	rnk[dfc] = cur;
	if (hson[cur]) DFS2(hson[cur]); // iterate heavy son first
	for (auto it : adj[cur])
	{
		if (it == fa[cur] || it == hson[cur]) continue;
		DFS2(it);
	}
}

void DFS3(int cur, int keep)
{
	for (auto it : adj[cur]) // light sons
	{
		if (it == fa[cur] || it == hson[cur]) continue;
		DFS3(it, false);
	}
	if (hson[cur]) DFS3(hson[cur], true), Incr(rt);
	for (auto it : adj[cur])
	{
		if (it == fa[cur] || it == hson[cur]) continue;
		for (int i = dfn[it]; i < dfn[it] + siz[it]; i++) Insert(v[rnk[i]] + dep[rnk[i]] - dep[cur]);
	}
	Insert(v[cur]);
	ans[cur] = tree[rt].xs;
	if (!keep) for (int i = dfn[cur]; i < dfn[cur] + siz[cur]; i++) Delete(v[rnk[i]] + dep[rnk[i]] - dep[cur]);
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> v[i];
	int p;
	for (int i = 2; i <= n; i++)
	{
		cin >> p;
		adj[p].push_back(i);
		adj[i].push_back(p);
	}
	DFS1(1), DFS2(1), DFS3(1, false);
	long long fans = 0;
	for (int i = 1; i <= n; i++) fans += (long long)ans[i];
	cout << fans << endl;
	return 0;
}