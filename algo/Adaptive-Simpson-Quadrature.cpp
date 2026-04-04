#include <bits/stdc++.h>

using namespace std;

double a;
const double eps = 1e-7;
double f(double x)
{
	return pow(x, a / x - x);
}

double Simpson(double l, double r)
{
	return (r - l) * (f(l) + f(r) + 4.0 * f((l + r) / 2.0)) / 6.0;
}

double Solve(double l, double r, double eps, double ans, int step)
{
	double mid = (l + r) / 2.0;
	double il = Simpson(l, mid), ir = Simpson(mid, r);
	if (fabs(il + ir - ans) < 15.0 * eps && step >= 24) return il + ir + (il + ir - ans) / 15.0;
	return Solve(l, mid, eps / 2.0, il, step + 1) + Solve(mid, r, eps / 2.0, ir, step + 1);
}

int main()
{
	cin >> a;
	if (a < -eps) 
	{
		cout << "orz\n";
		return 0;
	}
	cout << fixed << setprecision(5) << Solve(1e-12, 50, eps, Simpson(1e-12, 50), 0) << endl;
	return 0;
}