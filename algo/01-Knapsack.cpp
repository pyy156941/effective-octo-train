#include <iostream>

using namespace std;

int n, W;
long long v[101];
int w[101];
long long dp[100001];// plac, left
int main()
{
	cin >> n >> W;
	for (int i = 1; i <= n; i++) cin >> w[i] >> v[i];
	for (int i = 1; i <= n; i++)
	{
		for (int j = W; j >= w[i]; j--)
		{
			dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
//			cout << i << ' ' << j << ' ' << dp[i][j] << endl;
		}
//		for (int j = 0; j < w[i]; j++) dp[j] = dp[j];
//		cout << endl;
	}
	cout << dp[W] << endl;
}