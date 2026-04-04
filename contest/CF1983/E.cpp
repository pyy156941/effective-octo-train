#include <bits/stdc++.h>
#pragma GCC optimize("O3,Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

using namespace std;

#define pb push_back
#define eb emplace_back
#define ls(x) x << 1
#define rs(x) x << 1 | 1
#define lowbit(x) (x & (-x))
#define ctz(x) (__builtin_ctz(x))
#define ppc(x) (__builtin_popcount(x))

using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;
using i128 = __int128;

#define gc() getchar()
#define pc(x) putchar(x)
#define debug(x) cerr << #x << " : " << x << endl;
#define isdigit(x) (x >= '0' && x <= '9')

#define yn(x) pc(x ? 'Y' : 'N'), pc(x ? 'e' : 'o'), x ? (pc('s'), pc('\n')) : pc('\n')
#define ync(x) pc(x ? 'Y' : 'N'), pc(x ? 'E' : 'O'), x ? (pc('S'), pc('\n')) : pc('\n')
#define ynl(x) pc(x ? 'y' : 'n'), pc(x ? 'e' : 'o'), x ? (pc('s'), pc('\n')) : pc('\n')

template <typename ... Args>
void multiRead(Args& ... args)
{
    ((cin >> args), ...);
}

template <typename ... Args>
void multiWrite(Args ... args)
{
    ((cout << args << " "), ...);
}

template <typename T>
void exgcd(T a, T b, T &x, T &y)
{
	if (b == 0)
	{
		x = 1, y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}

template <typename T>
T Inv(T a, T p)
{
	T x, y;
	exgcd(a, p, x, y);
	return (x + p) % p;
}

template <typename T>
T QPow(T a, T b, T mod)
{
	T ans = 1;
	while (b)
	{
		if (b & 1) ans = ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}

bool multiTest = true;

ll fac[2000001], inv[2000001];

const ll mod = 1000000007;
void Initfact()
{
	fac[1] = fac[0] = inv[0] = inv[1] = 1;
	for (int i = 2; i <= 2000000; i++)
	{
		fac[i] = (fac[i - 1] * (ll)i) % mod;
		inv[i] = Inv <ll> (fac[i], mod);
	}
}

ll nCr(ll n, ll m)
{
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int n, k;
int v[400001];

const ll inv2 = 500000004;
ll Slv(ll a, ll b) // split a into b segments
{
	if (b == 1) return a;
	ll tots = nCr(a + b - 1, b - 1);
	ll it = Inv <ll> (tots, mod);
	ll res = 0;
	for (int x = 0; x <= a; x++)
	{
		ll cur = nCr(a - x + b - 2, b - 2);
		res = (res + cur * it % mod * (a + x) % mod * inv2 % mod) % mod;
	}
	return res;
}

void Solve()
{
	cin >> n >> k;
	ll snsp = 0, ssp = 0;
	for (int i = 1; i <= n; i++) 
	{
		cin >> v[i];
		if (i <= k) ssp += (ll)v[i];
		else snsp += (ll)v[i];
	}
	snsp %= mod;
	ssp %= mod;
	ll invn = Inv <ll> (n, mod);
	ll ans = 0;
	if ((n - k) % 2)
	{
		ans = snsp * (n - k + 1) % mod * inv2 % mod * Inv <ll> (n - k, mod) % mod;
	}
	else
	{
		ans = snsp * inv2 % mod;
	}
//	cerr << ans << endl;
	if ((n - k) % 2)
	{
//		ans = (ans + ssp * Slv(k, n - k) % mod * (n - k) % mod * invn % mod * invn % mod) % mod;
//		ans = (ans + ssp * (k - 1) % mod * k % mod * invn % mod) % mod;
		ans = (ans + ssp * inv2 % mod) % mod;
	}
	else
	{
//		ans = (ans + ssp * Slv(k - 1, n - k + 1) % mod * k % mod * invn % mod * invn % mod) % mod;
//		ans = (ans + ssp * k % mod * Inv <ll> (k, mod) % mod * invn % mod) % mod;
//		ans = (ans + ssp * inv2 % mod * (n - k) % mod * invn % mod) % mod;
		ans = (ans + ssp * (n - k + 2) % mod * inv2 % mod * Inv <ll> (n - k + 1, mod) % mod) % mod;
	}
	cout << ans << ' ' << (ssp + snsp - ans + mod * 2) % mod << endl;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr);
	int _ = 1;
	if (multiTest) cin >> _;
	Initfact();
	while (_--) Solve();
	return 0;
}