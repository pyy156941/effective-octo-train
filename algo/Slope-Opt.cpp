#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll dp[200001], h[200001];
inline ll Y(int x) {return dp[x] + h[x] * h[x]; }
inline ll X(int x) {return h[x]; }
inline double Slope(int x, int y) {return (double)(Y(y) - Y(x)) / (X(y) - X(x)); }

int n, Q[200001];
ll C;
int head = 1, tail = 0;

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> C;
	for (int i = 1; i <= n; i++) cin >> h[i];
	dp[1] = 0;
	Q[++tail] = 1;
	for (int i = 2; i <= n; i++)
	{
		while (head < tail && Slope(Q[head], Q[head + 1]) < 2.0 * h[i]) head++;
		dp[i] = dp[Q[head]] + (h[i] - h[Q[head]]) * (h[i] - h[Q[head]]) + C;
		while (head < tail && Slope(Q[tail - 1], Q[tail]) >= Slope(Q[tail], i)) tail--;
		Q[++tail] = i;  
	} 
	cout << dp[n] << endl;
	return 0;
}