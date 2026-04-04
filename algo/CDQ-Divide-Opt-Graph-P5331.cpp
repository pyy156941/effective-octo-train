#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
random_device rd;
mt19937 rng(rd());
const int INF = 0x3f3f3f3f;
int n;
struct Edge
{
	int v, nxt;
	int cap, flow, cost;
}e[1000100];

int ecnt = 1, nc = 0;
int dis[1000100];
int W, a[1005];// 2n + 1 source 2n + 2 sink
int head[1000100], cHead[1000100];
bool vis[1000100];

void AddEdge(int u, int v, int w, int c)
{
	e[++ecnt] = {v, head[u], w, 0, c};
	head[u] = ecnt;
	e[++ecnt] = {u, head[v], 0, 0, -c};
	head[v] = ecnt;
}

int temp[1001];
void Connect(int l, int r)
{
	if (l == r) return;
	int mid = (l + r) >> 1, cnt = 0;
	Connect(l, mid);
	Connect(mid + 1, r);
	for (int i = l; i <= r; i++) temp[++cnt] = a[i];
	sort(temp + 1, temp + cnt + 1);
	cnt = unique(temp + 1, temp + cnt + 1) - temp - 1;
	for (int i = 2; i <= cnt; i++) AddEdge(nc + i, nc + i - 1, INF, temp[i] - temp[i - 1]), AddEdge(nc + i - 1, nc + i, INF, temp[i] - temp[i - 1]);
	for (int i = l; i <= mid; i++)
	{
		int plac = lower_bound(temp + 1, temp + cnt + 1, a[i]) - temp;
		AddEdge(nc + plac, i + n, 1, 0);
	}
	for (int i = mid + 1; i <= r; i++)
	{
		int plac = lower_bound(temp + 1, temp + cnt + 1, a[i]) - temp;
		AddEdge(i, nc + plac, 1, 0);
	}
	nc += cnt;
}

bool SPFA(int s, int t)
{
	memcpy(cHead, head, sizeof(head));
	memset(dis, 0x3f, sizeof(dis));
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

ll rall = 0;
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
			if (c) rall += (ll)c * e[it].cost, e[it].flow += c, e[it ^ 1].flow -= c, rfl += c;
		}
	}
	vis[cur] = 0;
	return rfl;
}

int MCMF(int s, int t)
{
	int ans = 0;
	while (SPFA(s, t))
	{
		int x;
		memset(vis, 0, sizeof(vis));
		while ((x = DFS(s, t, INF))) ans += x;
	}
	return ans;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> W;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) AddEdge(2 * n + 1, i, 1, 0), AddEdge(i, 2 * n + 2, 1, W), AddEdge(i + n, 2 * n + 2, 1, 0);
	nc = 2 * n + 3;
	Connect(1, n);
	MCMF(2 * n + 1, 2 * n + 2);
	cout << rall << endl;
	return 0;
}