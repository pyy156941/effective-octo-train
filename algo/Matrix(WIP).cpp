#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

using ll = long long;
const ll mod = 1e9 + 7ll;
struct Mat
{
	int m, n;
	ll v[101][101];
	
	Mat (int row = 0, int col = 0) 
	{
		m = row, n = col;
		memset(v, 0, sizeof(v));
	}
	
	Mat operator + (const Mat &a) const
	{
		assert(n == a.n && m == a.m);
		Mat res(m, n);
		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				res.v[i][j] = (v[i][j] + a.v[i][j]) % mod;
			}
		}
		return res;
	}
	
	Mat operator - (const Mat &a) const
	{
		assert(n == a.n && m == a.m);
		Mat res(m, n);
		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				res.v[i][j] = ((v[i][j] - a.v[i][j]) % mod + mod) % mod;
			}
		}
		return res;
	}
	
	Mat operator * (const Mat &a) const
 	{
 		assert(n == a.m);
		int p = a.n;
		Mat res(m, p);
		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= p; j++)
			{
				res.v[i][j] = 0;
				for (int k = 1; k <= n; k++) 
				{
					res.v[i][j] += (v[i][k] * a.v[k][j]) % mod;
					res.v[i][j] %= mod;
				}
			}
		}
		return res;
	}
	
	Mat operator ^ (long long a) const
	{
		assert(m == n);
		Mat ans(n, n), base(n, n);
		for (int i = 1; i <= n; i++) ans.v[i][i] = 1;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				base.v[i][j] = v[i][j] % mod;
			}
		}
		while (a)
		{
			if (a % 2) ans = ans * base;
			base = base * base;
			a >>= 1;
		}
		return ans;
	} 
};
int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	long long n;
	cin >> n;
	if (n <= 2)
	{
		cout << 1 << endl;
		return 0;
	}
	Mat init;
	init.m = 1, init.n = 2;
	init.v[1][1] = 1, init.v[1][2] = 1;
	Mat trans;
	trans.m = trans.n = 2;
	trans.v[1][1] = 1;
	trans.v[1][2] = 1;
	trans.v[2][1] = 1;
	trans.v[2][2] = 0;
	Mat trans_ = trans ^ (n - 2);
	trans_ = init * trans_;
	cout << trans_.v[1][1] << endl;
	return 0;
}