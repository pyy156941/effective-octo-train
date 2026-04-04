#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int st[10001], top = 1;
vector <int> scc[10001], adj[10001];
int bel[10001], dfn[10001], low[10001];
bool vis[10001], ins[10001];
int cnt = 0, sccc = 0;

void DFS(int cur)
{
	vis[cur] = 1;
	dfn[cur] = ++cnt;
	low[cur] = dfn[cur];
	st[++top] = cur;
	ins[cur] = 1;
	for (auto it : adj[cur])
	{
		if (!vis[it])
		{
			DFS(it);
			low[cur] = min(low[cur], low[it]);
		}
		else if (ins[it])
		{
			low[cur] = min(low[cur], dfn[it]);
		}
	}
	if (dfn[cur] == low[cur])
	{	
		++sccc;
		while (st[top] != cur)
		{
			scc[sccc].push_back(st[top]);
			bel[st[top]] = sccc;
			ins[st[top]] = 0;
			top--;
		}
		scc[sccc].push_back(st[top]);
		bel[st[top]] = sccc;
		ins[st[top]] = 0; 	
		top--;
	}
}

int main()
{
	int n, m, u, v;
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> u >> v;
		adj[u].push_back(v);
	}
	for (int i = 1; i <= n; i++) if (!vis[i]) DFS(i);
	for (int i = 1; i <= sccc; i++) vis[i] = 0;
	cout << sccc << endl;
	for (int i = 1; i <= sccc; i++) sort(scc[i].begin(), scc[i].end()); 
	for (int i = 1; i <= n; i++)
	{
		if (!vis[bel[i]])
		{
			for (auto it : scc[bel[i]]) cout << it << ' ';
			cout << endl;
			vis[bel[i]] = 1;
		}
	}
	return 0;
}