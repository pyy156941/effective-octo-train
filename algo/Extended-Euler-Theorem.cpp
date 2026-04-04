#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll mod;
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

const int N = 10000;
bool nprime[N + 1];
vector <int> prime;

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

ll Phi(ll n)
{
	ll ans = n;
	for (auto p : prime)
	{
		if (n % p) continue;
		ans /= p, ans *= (p - 1);
		while (n % p == 0) n /= p;
	}
	if (n > 1) ans /= n, ans *= (n - 1);
	return ans;
}

ll QucikeerPow(ll a, int b[], int len)
{
	ll res = 0;
	bool flag = false;
	ll phi = Phi(mod);
	for (int i = 1; i <= len; i++) 
	{
		if (res * 10 + b[i] >= phi) flag = true;
		res = (res * 10 + b[i]) % phi;
	}
	return QPow(a, (flag ? res + phi : res));
}

int b[20000001];
int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	ll a;
	cin >> a >> mod;
	Sieve();
	char c;
	int len = 0;
	string str;
	cin >> str;
	for (auto i : str) b[++len] = (int)(i - '0');
	cout << QucikeerPow(a, b, len) << endl;
	return 0;
}