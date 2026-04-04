#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1001;

int n, m, e;
vector <int> adj[1001];
int match[1001];
int vis[1001];

int DFS(int cur, int t)
{
	for (auto it : adj[cur])
	{
		if (vis[it] != t)
		{
			vis[it] = t;
			if (!match[it] || DFS(match[it], t))
			{
				match[it] = cur;
				return 1;
			}
		}
	}
	return 0;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m >> e;
	int a, b;
	for (int i = 1; i <= e; i++)
	{
		cin >> a >> b;
		adj[a].push_back(n + b);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) ans += DFS(i, i);
	cout << ans << endl;
	return 0;
}