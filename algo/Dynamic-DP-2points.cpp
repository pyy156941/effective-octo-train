#include <bits/stdc++.h>
#define ls(x) x << 1
#define rs(x) x << 1 | 1

using namespace std;

typedef long long ll;
const ll INF = 1e15;
struct mat
{
	int n, m;//r, c
	ll val[2][2];
	
	mat (int _n = 2, int _m = 2) 
	{
		n = _n, m = _m;
		val[0][0] = val[1][1] = 0;
		val[0][1] = val[1][0] = INF;
	}
	
	const bool operator == (const mat a) const
	{
		assert(n == a.n && m == a.m);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++) 
			{
				if (val[i][j] != a.val[i][j]) return false;
			}
		}
		return true;
	}
	
	const mat operator * (const mat a) const
	{
		assert(m == a.n);
		mat res = mat(n, a.m);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < a.m; j++)
			{
				ll tmp = INF;
				for (int k = 0; k < m; k++) tmp = min(tmp, val[i][k] + a.val[k][j]);
				res.val[i][j] = tmp;
			}
		}
		return res;
	}
}ir[100001], fm[100001];

int n, m;
ll f[100001][2], g[100001][2]; // g0 brothers f0 sum, g1 brother min f0 f1 sum
ll p[100001];
vector <int> adj[100001];
int dep[100001], siz[100001], fa[100001], top[100001], hson[100001], dfn[100001], rnk[100001]; 
int kfa[100001][17];
int cnt = 0;

void DFS1(int cur)
{
	siz[cur] = 1;
	f[cur][0] = 0;
	f[cur][1] = p[cur];
	for (auto it : adj[cur])
	{
		if (it == fa[cur]) continue;
		fa[it] = cur;
		dep[it] = dep[cur] + 1;
		DFS1(it);
		siz[cur] += siz[it];
		f[cur][0] += f[it][1];
		f[cur][1] += min(f[it][0], f[it][1]);
		if (siz[it] > siz[hson[cur]] || !hson[cur]) hson[cur] = it;
	}
	fm[cur].val[0][0] = f[cur][0];
	fm[cur].val[0][1] = f[cur][1];
	fm[cur].n = 1, fm[cur].m = 2;
	for (auto it : adj[cur])
	{
		if (it == fa[cur]) continue;
		g[it][0] = f[cur][0] - f[it][1];
		g[it][1] = f[cur][1] - p[cur] - min(f[it][0], f[it][1]);
		ir[it].val[0][0] = INF;
		ir[it].val[0][1] = g[it][1] + p[cur];
		ir[it].val[1][0] = g[it][0];
		ir[it].val[1][1] = g[it][1] + p[cur];
	}
}

void DFS2(int cur, int head)
{
	dfn[cur] = ++cnt;
	rnk[cnt] = cur;
	top[cur] = head;
	if (hson[cur]) DFS2(hson[cur], head);
	for (auto it : adj[cur])
	{
		if (it == fa[cur] || it == hson[cur]) continue;
		DFS2(it, it);
	}
}

int LCA(int x, int y)
{
	while (top[x] != top[y])
	{
		if (dep[top[x]] > dep[top[y]]) swap(x, y);
		y = fa[top[y]];
	}
	return dep[x] < dep[y] ? x : y;
}

struct sgt
{
	mat tree[500001];
	
	mat Merge(mat a, mat b)
	{
		return a * b;
	}
	
	inline void Pushup(int cur)
	{
		tree[cur] = Merge(tree[rs(cur)], tree[ls(cur)]);
	}
	
	void Build(int cur, int l, int r)
	{
		if (l == r)
		{
			tree[cur] = ir[rnk[l]];
			return;
		}
		int mid = (l + r) >> 1;
		Build(ls(cur), l, mid);
		Build(rs(cur), mid + 1, r);
		Pushup(cur);
	}
	
	void Update(int cur, int p, int s, int t, int px, int py, int x)
	{
		if (s == t)
		{
			tree[cur].val[px][py] = x;
			return;
		}
		int mid = (s + t) >> 1;
		if (p <= mid) Update(ls(cur), p, s, mid, px, py, x);
		if (p > mid) Update(rs(cur), p, mid + 1, t, px, py, x);
		Pushup(cur);
	}
	
	mat Query(int cur, int l, int r, int s, int t)
	{
		if (l <= s && t <= r) return tree[cur];
		int mid = (s + t) >> 1;
		mat ans;
		bool flag = false;
		if (l <= mid) ans = Query(ls(cur), l, r, s, mid), flag = true;
		if (r > mid)
		{
			if (flag) ans = Merge(Query(rs(cur), l, r, mid + 1, t), ans);
			else ans = Query(rs(cur), l, r, mid + 1, t);
		}
		return ans;
	}
}s;

mat Query(int x, int y) // x to y (ancestor of x)
{
	if (x == y) return mat();
	int depy = max(dep[x] - dep[y] - 1, 0), t = 0;
	y = x;
	while (depy)
	{
		if (depy % 2) y = kfa[y][t];
		depy >>= 1;
		t++;
	}
	mat res;
	if (top[x] == top[y]) return s.Query(1, dfn[y], dfn[x], 1, n);
	res = s.Query(1, dfn[top[x]], dfn[x], 1, n);
	x = fa[top[x]];
	while (top[x] != top[y])
	{
		res = s.Merge(res, s.Query(1, dfn[top[x]], dfn[x], 1, n));
		x = fa[top[x]];
	}
	res = s.Merge(res, s.Query(1, dfn[y], dfn[x], 1, n));
	return res;
}

ll Update(int a, bool x, int b, bool y)
{
	if (fa[a] == b || fa[b] == a)
	{
		if (!(x + y)) return -1;
	}
	int lca = LCA(a, b);
	int depa = max(dep[a] - dep[lca] - 1, 0), depb = max(dep[b] - dep[lca] - 1, 0);
	int ta = a, t = 0, tb = b;
	while (depa)
	{
		if (depa % 2) ta = kfa[ta][t];
		depa >>= 1;
		t++;
	}
	t = 0;
	while (depb)
	{
		if (depb % 2) tb = kfa[tb][t];
		depb >>= 1;
		t++;
	}
	fm[a].val[0][!x] = INF;
	fm[b].val[0][!y] = INF;
	fm[ta] = fm[a] * Query(a, ta);
	fm[tb] = fm[b] * Query(b, tb);
	if (b == lca)
	{
		fm[lca].val[0][0] -= f[ta][1];
		fm[lca].val[0][0] += fm[ta].val[0][1];
		fm[lca].val[0][1] -= min(f[ta][0], f[ta][1]);
		fm[lca].val[0][1] += min(fm[ta].val[0][0], fm[ta].val[0][1]);
	}
	else if (a == lca)
	{
		fm[lca].val[0][0] -= f[tb][1];
		fm[lca].val[0][0] += fm[tb].val[0][1];
		fm[lca].val[0][1] -= min(f[tb][0], f[tb][1]);
		fm[lca].val[0][1] += min(fm[tb].val[0][0], fm[tb].val[0][1]);
	}
	else
	{
		assert(ta != tb);
		fm[lca].val[0][0] -= f[ta][1] + f[tb][1];
		fm[lca].val[0][0] += fm[ta].val[0][1] + fm[tb].val[0][1];
		fm[lca].val[0][1] -= min(f[ta][0], f[ta][1]) + min(f[tb][0], f[tb][1]);
		fm[lca].val[0][1] += min(fm[ta].val[0][0], fm[ta].val[0][1]) + min(fm[tb].val[0][0], fm[tb].val[0][1]);
	}
	mat res = fm[lca] * Query(lca, 1);
	fm[a].val[0][0] = f[a][0];
	fm[a].val[0][1] = f[a][1];
	fm[b].val[0][0] = f[b][0];
	fm[b].val[0][1] = f[b][1];
	fm[ta].val[0][0] = f[ta][0];
	fm[ta].val[0][1] = f[ta][1];
	fm[tb].val[0][0] = f[tb][0];
	fm[tb].val[0][1] = f[tb][1];
	fm[lca].val[0][0] = f[lca][0];
	fm[lca].val[0][1] = f[lca][1];
	return min(res.val[0][0], res.val[0][1]);
	//revert
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	string tp;
	cin >> n >> m >> tp;
	for (int i = 1; i <= n; i++) cin >> p[i];
	int u, v;
	for (int i = 1; i < n; i++) 
	{
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	DFS1(1);
	DFS2(1, 1);
	fm[1].val[0][0] = f[1][0];
	fm[1].val[0][1] = f[1][1];
	s.Build(1, 1, n);
/*	for (int i = 1; i <= n; i++)
	{
		cout << fm[i].val[0][0] << ' ' << fm[i].val[0][1] << endl;
		cout << ir[i].val[0][0] << ' ' << ir[i].val[0][1] << endl;
		cout << ir[i].val[1][0] << ' ' << ir[i].val[1][1] << endl;
		mat tmp = fm[i] * ir[i];
		cout << tmp.val[0][0] << ' ' << tmp.val[0][1] << endl;
		cout << endl;
	} */
	for (int i = 1; i <= n; i++) kfa[i][0] = fa[i];
	for (int r = 1; r <= 16; r++)
	{
		for (int i = 1; i <= n; i++)
		{
			kfa[i][r] = kfa[kfa[i][r - 1]][r - 1];
		}
	}
	bool x, y;
	for (int i = 1; i <= m; i++)
	{
		cin >> u >> x >> v >> y;
		cout << Update(u, x, v, y) << endl;
	}
	return 0;
}