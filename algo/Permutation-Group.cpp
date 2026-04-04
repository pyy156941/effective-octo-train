#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 31700;
const ll mod = 1000000007ll;

vector <int> prime;
bool nprime[N + 1];

ll QPow(ll a, ll b)
{
	ll ans = 1;
	while (b)
	{
		if (b & 1) ans = (ans * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return ans;
}

void Sieve()
{
	for (int i = 2; i <= N; i++)
	{
		if (!nprime[i]) prime.push_back(i);
		for (auto p : prime)
		{
			if (i * p > N) break;
			nprime[i * p] = 1;
			if (i % p == 0) break;
		}
	}
}

int Phi(int n)
{
	int ans = n;
	for (auto p : prime)
	{
		if (n % p) continue;
		ans /= p, ans *= (p - 1);
		while (n % p == 0) n /= p;
	}
	if (n > 1) ans /= n, ans *= (n - 1);
	return ans;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int t, n;
	cin >> t;
	Sieve();
	while (t--)
	{
		cin >> n;
		ll ans = 0;
		for (int i = 1; i * i <= n; i++)
		{
			if (n % i) continue;
			ll res = QPow(n, i);
			res = (res * (ll)Phi(n / i)) % mod;
			ans = (ans + res) % mod;
			if (i * i == n) continue;
			res = QPow(n, n / i);
			res = (res * (ll)Phi(i)) % mod;
			ans = (ans + res) % mod;
		}
		ans = (ans * QPow(n, mod - 2)) % mod;
		cout << ans << endl;
	}
	return 0;
}