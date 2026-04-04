#include <bits/stdc++.h>

using namespace std;

int n, m;
int low[500001], dfn[500001], cnt = 0;
bool vis[500001];

int bc = 0;
int bel[500001];
vector <int> bcc[500001];
vector <pair <int, int>> adj[500001];
set <int> cut[500001];

void DFS(int cur, int las)
{
	vis[cur] = 1;
	dfn[cur] = low[cur] = ++cnt;
	for (auto it : adj[cur])
	{
		int id = it.second, to = it.first;
		if (id == (las ^ 1)) continue;
		if (!vis[to])
		{
			DFS(to, id);
			low[cur] = min(low[cur], low[to]);
			if (low[to] > dfn[cur]) cut[cur].insert(to), cut[to].insert(cur);
		}
		else low[cur] = min(low[cur], dfn[to]);
	}
}

void DFS2(int cur, int id)
{
	bel[cur] = id;
	bcc[id].push_back(cur);
	for (auto it : adj[cur])
	{
		int to = it.first;
		if (bel[to]) continue;
		if (cut[cur].find(to) == cut[cur].end()) DFS2(to, id);
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
		adj[u].push_back({v, 2 * i - 2});
		adj[v].push_back({u, 2 * i - 1});
	}
	for (int i = 1; i <= n; i++) 
	{
		if (!vis[i]) DFS(i, -1);
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