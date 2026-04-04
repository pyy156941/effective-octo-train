#include <bits/stdc++.h>

using namespace std;

int n, m;
int degin[100001], degout[100001];
int head[100001];
vector <int> adj[100001];
vector <int> ans;

void DFS(int cur)
{
	for (int i = head[cur]; i < adj[cur].size(); i = head[cur])
	{
		head[cur] = i + 1;
		DFS(adj[cur][i]);
	}
	ans.push_back(cur);
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
		degout[u]++, degin[v]++;
		adj[u].push_back(v);
	}
	for (int i = 1; i <= n; i++) sort(adj[i].begin(), adj[i].end());
	int st = 1;
	int count1 = 0, count2 = 0;
	for (int i = n; i >= 1; i--)
	{
		if (degin[i] != degout[i]) 
		{
			if (degout[i] - degin[i] == 1) st = i, count1++;
			else if (degout[i] - degin[i] == -1) count2++;
			else 
			{
				cout << "No\n";
				return 0;
			}
		}
	}
	if (count1 > 1 || count2 > 1)
	{
		cout << "No\n";
		return 0;
	}
	DFS(st);
	for (int i = ans.size() - 1; i >= 0; i--) cout << ans[i] << ' ';
	cout << endl;
}