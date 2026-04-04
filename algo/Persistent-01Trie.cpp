#include <bits/stdc++.h>

using namespace std;

struct Node
{
	int tr[2];
	int siz;
}tree[16000001];

int cnt = 0, rcnt = 0;
int rt[600002];
int suf[600001];
int n, m;

int NewNode()
{
	tree[++cnt].siz = 0;
	tree[cnt].tr[0] = tree[cnt].tr[1] = 0;
	return cnt;
}

int DupNode(int cur)
{
	tree[++cnt] = tree[cur];
	return cnt;
}

int Insert(int rt, int x)
{
	int res = DupNode(rt);
	int cur = res;
	for (int i = 25; i >= 0; i--)
	{
		int curd = (x & (1 << i) ? 1 : 0);
		tree[cur].siz++;
		if (!tree[cur].tr[curd]) tree[cur].tr[curd] = NewNode();
		else tree[cur].tr[curd] = DupNode(tree[cur].tr[curd]);
		cur = tree[cur].tr[curd];
	}
	tree[cur].siz++;
	return res;
}

int Query(int l, int r, int x)
{
	int res = 0;
	int curl = rt[l - 1], curr = rt[r];
	for (int i = 25; i >= 0; i--)
	{
		int curd = (x & (1 << i) ? 1 : 0);
		if (tree[tree[curr].tr[curd ^ 1]].siz - tree[tree[curl].tr[curd ^ 1]].siz)
		{
			res += (1 << i);
			curl = tree[curl].tr[curd ^ 1];
			curr = tree[curr].tr[curd ^ 1];
		}
		else
		{
			curl = tree[curl].tr[curd];
			curr = tree[curr].tr[curd];
		}
	}
	return res;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int x, l, r;
	string mode;
	suf[0] = 0;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> x;
		suf[rcnt + 1] = suf[rcnt] ^ x;
		rt[rcnt + 1] = Insert(rt[rcnt], suf[rcnt + 1]);
		rcnt++;
	}
	for (int i = 1; i <= m; i++)
	{
		cin >> mode;
		if (mode[0] == 'A')
		{
			cin >> x;
			suf[rcnt + 1] = suf[rcnt] ^ x;
			rt[rcnt + 1] = Insert(rt[rcnt], suf[rcnt + 1]);
			rcnt++;
		}
		else
		{
			cin >> l >> r >> x;
			int tmp = x ^ suf[rcnt];
			if (l == 1) cout << max(tmp, Query(1, r - 1, tmp)) << endl;
			else cout << Query(l - 1, r - 1, tmp) << endl;
		}
	}
	return 0;
}