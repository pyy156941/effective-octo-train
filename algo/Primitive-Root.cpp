#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1000000;
bool nprime[N + 1];
vector <int> prime;
int phi[N + 1];

int QPow(int a, int b, int p)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) ans = (ll)ans * a % p;
		a = (ll)a * a % p;
		b >>= 1;
	}
	return ans;
}

void Sieve()
{
	phi[1] = 1;
	for (int i = 2; i <= N; i++)
	{
		if (!nprime[i]) prime.push_back(i), phi[i] = i - 1;
		for (auto p : prime)
		{
			if (i * p > N) break;
			nprime[i * p] = 1;
			if (i % p == 0)
			{
				phi[i * p] = phi[i] * p;
				break;
			}
			phi[i * p] = phi[i] * (p - 1);
		}
	}	
}

vector <int> pfac;
void Fac(int n)
{
	pfac.clear();
	for (auto p : prime)
	{
		if (n % p) continue;
		pfac.push_back(p);
		while (n % p == 0) n /= p;
	}
	if (n > 1) pfac.push_back(n);
}

bool Check(int n)
{
	if (n == 2 || n == 4) return true;
	if (n % 2 == 0) n /= 2;
	for (auto p : prime) 
	{
		if (p == 2 || n % p) continue;
		while (n % p == 0) n /= p;
		break;
	}
	if (n > 1) return false;
	return true;
}

bool CheckPr(int n, int r)
{
	int ph = phi[n];
	for (auto p : pfac)
	{
		if (QPow(r, ph / p, n) == 1) return false;
	}
	return true;
}

bool isp[N];
void Solve()
{
	int n, d;
	cin >> n >> d;
	memset(isp, 0, sizeof(isp));
	if (n == 2)
	{
		cout << "1\n";
		if (d == 1) cout << 1;
		cout << '\n';
		return;
	}
	if (!Check(n)) 
	{
		cout << "0\n\n";
		return;
	}
	Fac(phi[n]);
	int cnt = 0, mpr;
	for (int i = 1; i < n; i++)
	{
		if (__gcd(i, n) != 1) continue;
		if (CheckPr(n, i))
		{
			mpr = i;
			break;
		}
	}
	for (int i = 1; i < phi[n]; i++)
	{
		if (__gcd(i, phi[n]) != 1) continue;
		isp[QPow(mpr, i, n)] = 1;
	}
	cout << phi[phi[n]] << '\n';
	for (int i = 1; i < n; i++) 
	{
		if (isp[i])
		{
			cnt++;
			if (cnt % d == 0) cout << i << ' ';
		}
	}
	cout << '\n';
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int _;
	cin >> _;
	Sieve();
	while (_--) Solve();
	return 0;
}