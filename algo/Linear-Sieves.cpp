#include <bits/stdc++.h>

using namespace std;

const int N = 10000001;
vector <int> prime;
bool nprime[N];
int phi[N], mu[N];
int divisor[N], num[N];

void Sieve(int n)
{
	mu[1] = 1;
	phi[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (!nprime[i]) 
		{
			prime.push_back(i);
			phi[i] = i - 1;
			mu[i] = -1;
			num[i] = 1;
			divisor[i] = 2;
		}
		for (auto p : prime)
		{
			if (i * p > n) break;
			nprime[i * p] = true;
			if (i % p == 0) 
			{
				num[i * p] = num[i] + 1;
				divisor[i * p] = divisor[i] / num[i * p] * (num[i * p] + 1);
				phi[i * p] = phi[i] * p;
				mu[i * p] = 0;
				break;
			}
			num[i * p] = 1;
			divisor[i * p] = divisor[i] * 2;
			phi[i * p] = phi[i] * phi[p]; // Multiplicative
			mu[i * p] = mu[i] * mu[p]; // MuOP
		}
	}
}

int main()
{
	ios :: sync_with_stdio(false);
	int n;
	cin >> n;
	Sieve(n);
	for (int i = 1; i <= n; i++)
	{
		cout << i << ' ' << !nprime[i] << ' ' << phi[i] << ' ' << mu[i] << ' ' << d[i] << ' ' << num[i] << endl;
	}
}