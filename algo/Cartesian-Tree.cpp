#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int n;
int w[10000001], ls[10000001], rs[10000001];

int st[10000001], top = 0;
void Build()
{
	for (int i = 1; i <= n; i++)
	{
		int las = 0;
		while (top && w[st[top]] > w[i]) las = st[top--]; 
		if (top) rs[st[top]] = i;
		ls[i] = las;
		st[++top] = i;
	}
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> w[i];
	Build();
	ll al = 0, ar = 0;
	for (int i = 1; i <= n; i++)
	{
		al ^= (ll)i * (ls[i] + 1);
		ar ^= (ll)i * (rs[i] + 1);
	}
	cout << al << ' ' << ar << endl;
	return 0;
}