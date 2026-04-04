#include <bits/stdc++.h>

using namespace std;

using ll = long long;
int n, k;

struct Node
{
	ll val;
	int dep;
	
	Node (ll _val, int _dep) : val(_val), dep(_dep) {}
	
	bool operator < (const Node a) const
	{
		if (val == a.val) return dep > a.dep;
		return val > a.val;
	}
};

priority_queue <Node> Q;

ll ans = 0, ad = 0;
int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> k;
	ll w;
	for (int i = 1; i <= n; i++)
	{
		cin >> w;
		Q.push(Node(w, 1));
	}
	while ((Q.size() - 1) % (k - 1)) Q.push(Node(0, 1));
	while (Q.size() >= k)
	{
		ll sum = 0;
		int mxd = 0;
		for (int i = 1; i <= k; i++)
		{
			auto cur = Q.top();
//			cerr << cur.dep << ' ' << cur.val << endl;
			Q.pop();
			mxd = max(mxd, cur.dep + 1);
			sum += cur.val;
		} 
		ans += sum;
		Q.push(Node(sum, mxd));
	}
	cout << ans << endl << Q.top().dep - 1 << endl;
	return 0;
}