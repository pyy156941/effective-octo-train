#include <iostream>
#include <string>
#include <queue>
#include <cstring>

using namespace std;

int n;
int nodecnt = 0;
int tree[10501][26];
int count[273001], fail[273001], to[273001];
bool ise[273001]; // is end
string S[151], T;
int ans = 0;

void Clear()
{
	memset(count, 0, sizeof(count));
	memset(tree, 0, sizeof(tree));
	memset(ise, 0, sizeof(ise));
	memset(fail, 0, sizeof(fail));
	memset(to, 0, sizeof(to));
	ans = 0;
	nodecnt = 0;
}

void Insert(string s, int id)
{
	int cur = 0;
	for (auto it : s)
	{
		int ss = it - 'a';
		if (!tree[cur][ss]) tree[cur][ss] = ++nodecnt;
		cur = tree[cur][ss];
	}
	to[id] = cur;
	ise[cur] = 1;
}

void BuildAC()
{
	queue <int> Q;
	for (int i = 0; i < 26; i++)
	{
		if (tree[0][i]) Q.push(tree[0][i]); 
	}
	while (!Q.empty())
	{
		int cur = Q.front();
		Q.pop();
		for (int i = 0; i < 26; i++)
		{
			if (tree[cur][i]) 
			{
				fail[tree[cur][i]] = tree[fail[cur]][i];
				Q.push(tree[cur][i]);
			}
			else tree[cur][i] = tree[fail[cur]][i];
		}
	}
}

void Query(string s)
{
	int cur = 0;
	for (auto it : s)
	{
		int ss = it - 'a';
		cur = tree[cur][ss];
		for (int i = cur; i; i = fail[i])
		{
			if (ise[i])
			{
				count[i]++;
				if (count[i] > ans) ans = count[i];
			}
		}
	}
}

int main()
{
	while (1)
	{
		cin >> n;
		if (!n) break;
		Clear();
		for (int i = 1; i <= n; i++)
		{
			cin >> S[i];
			Insert(S[i], i);
		}
		cin >> T;
		BuildAC();
		Query(T);
		cout << ans << endl;
		for (int i = 1; i <= n; i++)
		{
			if (count[to[i]] == ans) cout << S[i] << endl;
		}
	}
	return 0;
}
