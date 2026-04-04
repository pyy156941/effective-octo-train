#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int n, m;
struct Edge
{
	int v, nxt;
	int cap, flow, cost;
}e[100002];

int ecnt = 1;
int dis[5001], head[5001], cHead[5001];
bool vis[5001];

void AddEdge(int u, int v, int w, int c)
{
	e[++ecnt] = {v, head[u], w, 0, c};
	head[u] = ecnt;
	e[++ecnt] = {u, head[v], 0, 0, -c};
	head[v] = ecnt;
}

bool SPFA(int s, int t)
{
	memcpy(cHead, head, sizeof(head));
	for (int i = 1; i <= n; i++) dis[i] = INF;
	queue <int> Q;
	dis[s] = 0;
	vis[s] = 1;
	Q.push(s);
	while (!Q.empty())
	{
		int cur = Q.front();
		Q.pop();
		vis[cur] = 0;
		for (int it = head[cur]; it; it = e[it].nxt)
		{
			int v = e[it].v;
			if (dis[v] > dis[cur] + e[it].cost && e[it].cap - e[it].flow)
			{
				dis[v] = dis[cur] + e[it].cost;
				if (!vis[v]) Q.push(v), vis[v] = 1;	
			}
		}
	}
	return dis[t] != INF;
}

int rall = 0;
int DFS(int cur, int t, int flow)
{
	if (cur == t || !flow) return flow;
	vis[cur] = 1;
	int rfl = 0;
	for (int it = cHead[cur]; it && rfl < flow; it = e[it].nxt)
	{
		cHead[cur] = it;
		int v = e[it].v;
		if (!vis[v] && e[it].cap - e[it].flow && dis[v] == dis[cur] + e[it].cost)
		{
			int c = DFS(v, t, min(e[it].cap - e[it].flow, flow - rfl));
			if (c) rall += c * e[it].cost, e[it].flow += c, e[it ^ 1].flow -= c, rfl += c;
		}
	}
	vis[cur] = 0;
	return rfl;
}

int MCMF(int s, int t)
{
	if (s == t) return 0;
	int ans = 0;
	while (SPFA(s, t))
	{
		int x;
		while ((x = DFS(s, t, INF))) 
		{
			ans += x;
			memset(vis, 0, sizeof(vis));
		}
	}
	return ans;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int u, v, w, s, t, c;
	cin >> n >> m >> s >> t;
	for (int i = 1; i <= m; i++)
	{
		cin >> u >> v >> w >> c;
		AddEdge(u, v, w, c);
	}
	cout << MCMF(s, t) << ' ' << rall << endl;
	return 0;
}