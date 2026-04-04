#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, m;
struct Edge
{
	int v, nxt;
	int cap, flow, cost;
}e[100025];

struct Node
{
	int fv, fe;
}N[5005];

struct NodeDis
{
	int id;
	ll dis;
	NodeDis(int _id, ll _dis) 
	{
		id = _id, dis = _dis;
	}	
	const bool operator < (const NodeDis a) const
	{
		return dis > a.dis; // must be >
	}
};

int ecnt = 1;
bool vis[5005];
ll ph[5005], dis[5005];
int head[5005];
void AddEdge(int u, int v, int w, int c)
{
	e[++ecnt] = {v, head[u], w, 0, c};
	head[u] = ecnt;
	e[++ecnt] = {u, head[v], 0, 0, -c};
	head[v] = ecnt;
}

void SPFA(int s, int t)
{
	queue <int> Q;
	memset(ph, 0x3f, sizeof(ph));
	memset(vis, 0, sizeof(vis));
	vis[s] = 1;
	ph[s] = 0;
	Q.push(s);
	while (!Q.empty())
	{
		int cur = Q.front();
		Q.pop();
		vis[cur] = 0;
		for (int it = head[cur]; it; it = e[it].nxt)
		{
			int v = e[it].v;
			if (e[it].cap - e[it].flow && ph[v] > ph[cur] + (ll)e[it].cost)
			{
				ph[v] = ph[cur] + (ll)e[it].cost;
				if (!vis[v]) vis[v] = 1, Q.push(v);
			}
		}
	}
}

bool Dijkstra(int s, int t)
{
	priority_queue <NodeDis> Q;
	memset(vis, 0, sizeof(vis));
	memset(dis, 0x3f, sizeof(dis));
	dis[s] = 0;
	Q.push(NodeDis(s, 0));
	while (!Q.empty())
	{
		int cur = Q.top().id;
		Q.pop();
		vis[cur] = 1;
		for (int it = head[cur]; it; it = e[it].nxt)
		{
			int v = e[it].v;
			ll nc = (ll)e[it].cost + ph[cur] - ph[v];
			if (e[it].cap - e[it].flow && dis[v] > dis[cur] + nc)
			{
				dis[v] = dis[cur] + nc;
				N[v].fv = cur;
				N[v].fe = it;
				if (!vis[v]) Q.push(NodeDis(v, dis[v]));
			}
		}
	}
	return dis[t] != INF;
}

pair <ll, ll> MCMF(int s, int t)
{
	ll maxflow = 0, mincost = 0;
	SPFA(s, t);
	while (Dijkstra(s, t))
	{
		ll minflow = INF;
		for (int i = 1; i <= n; i++) ph[i] += dis[i];
		for (int i = t; i != s; i = N[i].fv) minflow = min(minflow, (ll)e[N[i].fe].cap - e[N[i].fe].flow);
		for (int i = t; i != s; i = N[i].fv) 
		{
			e[N[i].fe].flow += minflow;
			e[N[i].fe ^ 1].flow -= minflow;
		}
		maxflow += minflow;
		mincost += minflow * ph[t];
	}
	return make_pair(maxflow, mincost);
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int s, t, u, v, w, c;
	cin >> n >> m >> s >> t;
	for (int i = 1; i <= m; i++)
	{
		cin >> u >> v >> w >> c;
		AddEdge(u, v, w, c);
	}
	auto ans = MCMF(s, t);
	cout << ans.first << ' ' << ans.second << endl;
	return 0;
}