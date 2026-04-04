#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge
{
	int v, w;
	Edge (int _v, int _w)
	{
		v = _v, w = _w;
	}
};

struct Node
{
	int id, dis, cnt;
	bool vis;
	Node (int _id = 0, int _dis = 0, int _cnt = 0, bool _vis = 0) 
	{
		id = _id, dis = _dis, cnt = _cnt, vis = _vis;
	}
}a[2001];

int T, n, m;
vector <Edge> adj[2001];

inline void AddEdge(int u, int v, int w)
{
	adj[u].push_back(Edge(v, w));
}

inline void Init()
{
	for (int i = 1; i <= n; i++) adj[i].clear();
	a[1].dis = 0;
	for (int i = 2; i <= n; i++) a[i].dis = 2e9;
	for (int i = 1; i <= n; i++) a[i].cnt = 0, a[i].vis = 0, a[i].id = i;
}

bool SPFA(int s)
{
	queue <Node> Q;
	Q.push(Node(s, 0, 0));
	while (!Q.empty())
	{
		int cur = Q.front().id;
		Q.pop();
		a[cur].vis = 0;
		for (auto it : adj[cur])
		{
			int v = it.v, w = it.w;
			if (a[v].dis > a[cur].dis + w)
			{
				a[v].dis = a[cur].dis + w;
				a[v].cnt = a[cur].cnt + 1;
				if (a[v].cnt > n - 1) return false;
				if (!a[v].vis) Q.push(a[v]), a[v].vis = 1;
			}
		}
	}
	return true;
}

void Solve()
{
	int u, v, w;
	cin >> n >> m;
	Init();
	for (int i = 1; i <= m; i++)
	{
		cin >> u >> v >> w;
		if (w >= 0) AddEdge(u, v, w), AddEdge(v, u, w);
		else AddEdge(u, v, w);
	}
	if (SPFA(1)) cout << "NO" << endl;
	else cout << "YES" << endl;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> T;
	while (T--) Solve();
	return 0;
}