#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-12;

int n;
double a[101][101], b[101];
double tr[101][102];
double ans[101];
bool Solve()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			tr[i][j] = a[i][j];
		}
	}
	for (int i = 1; i <= n; i++) tr[i][n + 1] = b[i];
	for (int i = 1; i <= n; i++)
	{
		double pv = -2e9;	
		int p = 0;
		for (int j = i; j <= n; j++) 
		{
			if (abs(tr[j][i]) > pv)
			{
				pv = tr[j][i];
				p = j;
			}
		}
		if (abs(pv) < eps) return false;
		if (p != i) for (int j = 1; j <= n + 1; j++) swap(tr[p][j], tr[i][j]);
		for (int j = 1; j <= n; j++)
		{
			if (j == i) continue; // hack
			double t = tr[j][i] / tr[i][i];
			for (int k = i + 1; k <= n + 1; k++) tr[j][k] -= tr[i][k] * t;
		}
	}
	for (int i = 1; i <= n; i++) ans[i] = tr[i][n + 1] / tr[i][i];
	return true;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> a[i][j];
		}
		cin >> b[i];
	}
	if (!Solve()) cout << "No Solution\n";
	else
	{
		for (int i = 1; i <= n; i++) cout << fixed << setprecision(2) << ans[i] << endl;
	}
	return 0;
}