#include <bits/stdc++.h>

using namespace std;

int n, m;
int low[500001], dfn[500001], cnt = 0;
bool vis[500001];
int fa[500001];

int bc = 0;
int bel[500001];
vector <int> bcc[500001], adj[500001];
set <int> cut[500001];

void DFS(int cur)
{
	vis[cur] = 1;
	dfn[cur] = low[cur] = ++cnt;
	for (auto it : adj[cur])
	{
		if (!vis[it])
		{
			fa[it] = cur;
			DFS(it);
			low[cur] = min(low[cur], low[it]);
			if (low[it] > dfn[cur]) cut[cur].insert(it), cut[it].insert(cur);
		}
		else if (it != fa[cur]) low[cur] = min(low[cur], dfn[it]);
	}
}

void DFS2(int cur, int id)
{
	bel[cur] = id;
	bcc[id].push_back(cur);
	for (auto it : adj[cur])
	{
		if (bel[it]) continue;
		if (cut[cur].find(it) == cut[cur].end()) DFS2(it, id);
	}
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m;
	int u, v;
	for (int i = 1; i <= m; i++)
	{
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) 
	{
		if (!vis[i]) DFS(i);
	}
/*	for (int i = 1; i <= n; i++)
	{
		for (auto it : cut[i]) cerr << i << ' ' << it << endl;
	}*/
	for (int i = 1; i <= n; i++)
	{
		if (!bel[i])
		{
			bc++;
			DFS2(i, bc);
		}
	}
	cout << bc << '\n';
	for (int i = 1; i <= bc; i++)
	{
		cout << bcc[i].size() << ' ';
		for (auto it : bcc[i]) cout << it << ' ';
		cout << '\n';
	}
	return 0;
}