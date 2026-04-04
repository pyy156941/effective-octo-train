#include <bits/stdc++.h>

using namespace std;

int n, a;
pair <int, int> st[3000001];
int ans[3000001];
int top = 0;

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a;
		while (top && st[top].first < a) ans[st[top--].second] = i;
		st[++top] = {a, i};
	}
	for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
	cout << endl;
	return 0;
}