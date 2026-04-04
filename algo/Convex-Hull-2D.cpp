#include <bits/stdc++.h>

using namespace std;

struct Vec
{
	double x, y;
	Vec (double _x = 0, double _y = 0)
	{
		x = _x, y = _y;
	}
	bool operator == (const Vec a) const
	{
		return (x == a.x) && (y == a.y);
	}
	Vec operator - (const Vec a) const
	{
		return Vec(x - a.x, y - a.y);
	}
}V[100001];

Vec cv[100001];
int n;

double Dist(Vec a, Vec b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool CMP(Vec a, Vec b)
{
	double a1 = atan2(a.y - V[1].y, a.x - V[1].x); // has to be compared to V1
	double a2 = atan2(b.y - V[1].y, b.x - V[1].x);
	if (a1 == a2) return Dist(a, V[1]) > Dist(b, V[1]);
	return a1 < a2;
}

double crossP(Vec a, Vec b)
{
	return a.x * b.y - a.y * b.x;
}

bool check(Vec a, Vec b, Vec p) // recite these
{
	return crossP(b - a, p - a) >= 0;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> V[i].x >> V[i].y;
	for (int i = 2; i <= n; i++)
	{
		if (V[i].y < V[1].y) swap(V[i], V[1]);
		else if (V[i].y == V[1].y && V[i].x < V[1].x) swap(V[i], V[1]);
	}
	sort(V + 2, V + n + 1, CMP);
	n = unique(V + 2, V + n + 1) - (V + 1);
	int cnt = 0;
	cv[++cnt] = V[1];
	for (int i = 2; i <= n; i++)
	{
		while (cnt > 1 && !check(cv[cnt - 1], cv[cnt], V[i])) cnt--;
		cv[++cnt] = V[i];
	}
	cv[++cnt] = V[1];
	double ans = 0;
	for (int i = 1; i < cnt; i++) ans += Dist(cv[i], cv[i + 1]);
	cout << fixed << setprecision(2) << ans << endl;
	return 0;
}