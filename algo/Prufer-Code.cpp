#include <bits/stdc++.h>

using namespace std;

int n, m;
int fa[5000001], prufer[5000001];
int deg[5000001];

void BuildPrufer()
{
	for (int i = 1; i < n; i++) deg[fa[i]]++;
	int p = 1, c = 0;
	for (int i = 1; i <= n - 2; i++)
	{
		while (deg[p]) p++;
		prufer[i] = fa[p];
		while (i < n - 2 && !--deg[prufer[i]] && prufer[i] < p)
		{
			prufer[i + 1] = fa[prufer[i]];
			i++;
		}
		p++;
	}
}

void BuildFa()
{
	for (int i = 1; i <= n - 2; i++) deg[prufer[i]]++;
	int p = 1;
	prufer[n - 1] = n;
	for (int i = 1; i <= n - 1; i++)
	{
		while (deg[p]) p++;
		fa[p] = prufer[i];
		while (i < n - 1 && !--deg[prufer[i]] && prufer[i] < p)
		{
			fa[prufer[i]] = prufer[i + 1];
			i++;
		}
		p++;
	}
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m;
	if (m == 1)
	{
		for (int i = 1; i < n; i++) cin >> fa[i];
		BuildPrufer();
		for (int i = 1; i <= n - 2; i++) cout << prufer[i] << ' ';
	} 
	else
	{
		for (int i = 1; i <= n - 2; i++) cin >> prufer[i];
		BuildFa();
		for (int i = 1; i < n; i++) cout << fa[i] << ' ';
	}
}