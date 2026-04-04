#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1664511;
vector <int> prime;
bool nprime[N + 1];
int mu[N + 1], smu[N + 1];
ll sph[N + 1], phi[N + 1];
map <ll, ll> mpu, mpp;

void Sieve()
{
	mu[1] = 1;
	phi[1] = 1;
	for (int i = 2; i <= N; i++)
	{
		if (!nprime[i]) 
		{
			prime.push_back(i);
			phi[i] = i - 1;
			mu[i] = -1;
		}
		for (auto p : prime)
		{
			if (i * p > N) break;
			nprime[i * p] = true;
			if (i % p == 0) 
			{
				phi[i * p] = phi[i] * p;
				mu[i * p] = 0;
				break;
			}
			phi[i * p] = phi[i] * phi[p]; // Multiplicative
			mu[i * p] = mu[i] * mu[p]; // MuOP
		}
	}
	for (int i = 1; i <= N; i++) smu[i] = smu[i - 1] + mu[i];
	for (int i = 1; i <= N; i++) sph[i] = sph[i - 1] + phi[i];
}

ll SolveM(ll x)
{
	if (x <= N) return smu[x];
	if (mpu[x]) return mpu[x];
	ll res = 1ll;
	for (ll l = 2, r; l <= x; l = r + 1)
	{
		r = x / (x / l);
		res -= SolveM(x / l) * (ll)(r - l + 1);
	}
	return mpu[x] = res;
}

ll SolveP(ll x)
{
	if (x <= N) return sph[x];
	if (mpp[x]) return mpp[x];
	ll res = x * (x + 1ll) / 2ll;
	for (ll l = 2, r; l <= x; l = r + 1)
	{
		r = x / (x / l);
		res -= SolveP(x / l) * (ll)(r - l + 1);
	}
	return mpp[x] = res;
}

void Solve()
{
	ll n;
	cin >> n;
	cout << SolveP(n) << ' ' << SolveM(n) << endl;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int t;
	cin >> t;
	Sieve();
	while (t--) Solve();
	return 0;
}