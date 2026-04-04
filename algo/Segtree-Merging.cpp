#include <bits/stdc++.h>

using namespace std;

struct Node
{
	int ls, rs;
	int val, p;
}tree[16000001];
int rt[100001];
int cnt = 0;

void Pushup(int cur)
{
	if (tree[tree[cur].ls].val >= tree[tree[cur].rs].val) tree[cur].p = tree[tree[cur].ls].p;
	else tree[cur].p = tree[tree[cur].rs].p;
	tree[cur].val = max(tree[tree[cur].ls].val, tree[tree[cur].rs].val);
	if (!tree[cur].val) tree[cur].p = 0;
}

int Update(int cur, int p, int s, int t, int x)
{
	if (!cur) cur = ++cnt;
	if (s == t) 
	{
		tree[cur].val += x;
		tree[cur].p = p;
		return cur;
	}
	int mid = (s + t) >> 1;
	if (p <= mid) tree[cur].ls = Update(tree[cur].ls, p, s, mid, x);
	if (p > mid) tree[cur].rs = Update(tree[cur].rs, p, mid + 1, t, x);
	Pushup(cur);
	return cur;
}

int Merge(int ca, int cb, int s, int t)
{
	if (!ca || !cb) return ca + cb;
	if (s == t)
	{
		tree[ca].val += tree[cb].val;
		return ca;
	}
	int mid = (s + t) >> 1;
	tree[ca].ls = Merge(tree[ca].ls, tree[cb].ls, s, mid);
	tree[ca].rs = Merge(tree[ca].rs, tree[cb].rs, mid + 1, t);
	Pushup(ca);
	return ca;
}

vector <int> adj[100001];
int fa[100001];
int siz[100001], dep[100001], hson[100001], top[100001];

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
		if (!hson[cur] || siz[it] > siz[hson[cur]]) hson[cur] = it;
	}
}

void DFS2(int cur, int head)
{
	top[cur] = head;
	if (hson[cur]) DFS2(hson[cur], head);
	for (auto it : adj[cur])
	{
		if (it == fa[cur] || it == hson[cur]) continue;
		DFS2(it, it);	
	}
}

int LCA(int x, int y)
{
	while (top[x] != top[y])
	{
		if (dep[top[x]] < dep[top[y]]) y = fa[top[y]];
		else x = fa[top[x]];
	}
	return dep[x] < dep[y] ? x : y;
}

int ans[100001];
void DFS3(int cur)
{
	for (auto it : adj[cur])
	{
		if (it == fa[cur]) continue;
		DFS3(it);
		rt[cur] = Merge(rt[cur], rt[it], 1, 100000);
	}
	ans[cur] = tree[rt[cur]].p;
}

int n, m;
int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	int u, v;
	for (int i = 1; i < n; i++)
	{
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	DFS1(1);
	DFS2(1, 1);
	int z;
	for (int i = 1; i <= m; i++)
	{
		cin >> u >> v >> z;
		int lca = LCA(u, v);
		rt[u] = Update(rt[u], z, 1, 100000, 1);
		rt[v] = Update(rt[v], z, 1, 100000, 1);
		rt[lca] = Update(rt[lca], z, 1, 100000, -1);
		rt[fa[lca]] = Update(rt[fa[lca]], z, 1, 100000, -1);
	}
	DFS3(1);
	for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
	return 0;
}