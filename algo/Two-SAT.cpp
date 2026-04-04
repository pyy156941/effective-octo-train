#include <bits/stdc++.h>

using namespace std;

int n, m;
vector <int> adj[16001], adj_[16001], scc[16001];
int bel[16001], st[16001], top = 0, scnt = 0;
bool ins[16001], vis[16001];
int low[16001], dfn[16001], cnt = 0;

void DFS(int cur)
{
	dfn[cur] = ++cnt;
	vis[cur] = 1;
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
		else if (ins[it]) low[cur] = min(low[cur], dfn[it]);
	}
	if (dfn[cur] == low[cur])
	{
		++scnt;
		while (st[top] != cur)
		{
			scc[scnt].push_back(st[top]);
			bel[st[top]] = scnt;
			ins[st[top]] = 0;
			top--;
		}
		scc[scnt].push_back(st[top]);
		bel[st[top]] = scnt;
		ins[st[top]] = 0;
		top--;
	}
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int a, b;
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> a >> b;
		adj[a].push_back(b % 2 ? b + 1 : b - 1);
		adj[b].push_back(a % 2 ? a + 1 : a - 1);
	}
	for (int i = 1; i <= 2 * n; i++)
	{
		if (!vis[i]) DFS(i);
	}
	for (int i = 1; i <= n; i++)
	{
		if (bel[2 * i - 1] == bel[2 * i])
		{
			cout << "NIE\n";
			return 0;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (bel[2 * i - 1] < bel[2 * i]) cout << 2 * i - 1 << '\n';
		else if (bel[2 * i - 1] > bel[2 * i]) cout << 2 * i << '\n';
	}
	return 0;
}