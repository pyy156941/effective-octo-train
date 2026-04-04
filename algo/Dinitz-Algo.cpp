#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;
struct Edge
{
	int v, nxt;
	long long cap, flow;
}e[10002];

int ecnt = 1;
int dep[201];
int head[201], cHead[201];

void AddEdge(int u, int v, int w)
{
	e[++ecnt] = {v, head[u], w, 0};
	head[u] = ecnt;
	e[++ecnt] = {u, head[v], 0, 0};
	head[v] = ecnt;
}

bool BFS(int s, int t)
{
	queue <int> Q;
	for (int i = 1; i <= n; i++) dep[i] = 0;
	dep[s] = 1;
	Q.push(s);
	while (!Q.empty())
	{
		int cur = Q.front();
		Q.pop();
		for (int it = head[cur]; it; it = e[it].nxt)
		{
			int v = e[it].v;
			if (!dep[v] && e[it].cap > e[it].flow)
			{
				dep[v] = dep[cur] + 1;
				Q.push(v);
			}
		}
	}
	return dep[t];
}

long long DFS(int cur, int t, long long flow)
{
	if (cur == t || !flow) return flow;
	long long ret = 0;
	for (int it = cHead[cur]; it; it = e[it].nxt)
	{
		cHead[cur] = it; // opt
		int v = e[it].v;
		long long c;
		if (dep[v] == dep[cur] + 1 && (c = DFS(v, t, min(flow - ret, e[it].cap - e[it].flow))))
		{
			ret += c;
			e[it].flow += c;
			e[it ^ 1].flow -= c;
		}
	}
	return ret;
}

long long MaxFlow(int s, int t)
{
	long long maxflow = 0;
	while (BFS(s, t))
	{
		for (int i = 1; i <= n; i++) cHead[i] = head[i];
		maxflow += DFS(s, t, 1e10);
	}
	return maxflow;
}

int main()
{
	int u, v, w, s, t;
	cin >> n >> m >> s >> t;
	for (int i = 1; i <= m; i++)
	{
		cin >> u >> v >> w;
		AddEdge(u, v, w);
	}
	cout << MaxFlow(s, t) << endl;
	return 0;
}