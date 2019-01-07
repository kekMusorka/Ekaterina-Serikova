#include <bits/stdc++.h>
 
using namespace std;
 
const int MAXN = 1e6 + 1;
 
vector <int> col[MAXN], arr[MAXN], q[MAXN], result;
int par[MAXN], c[MAXN], ccnt[MAXN], ans[MAXN], tin[MAXN], tout[MAXN], dsu_p[MAXN], dsu_r[MAXN];
int tme = 0;
bool used[MAXN];
int rk[MAXN];

bool in(int u, int v) { 
	return tin[v] <= tin[u] && tout[u] <= tout[v]; 
}
 
int cnt(int v) { 
    ans[v] = ccnt[v];
	for (int i = 0; i < (int)arr[v].size(); i++) {
        int u = arr[v][i];
        ans[v] += cnt(u);
	}
	return ans[v];
}
 
void dfs1(int v) {
	tin[v] = tme++;
	col[c[v]].push_back(v);
	for (int i = 0; i < (int)arr[v].size(); i++) {
		int u = arr[v][i];
		dfs1(u);
	}
	tout[v] = tme++;
}
 
int find_sets(int v) {
    if (dsu_p[v] == v) {
		return v;
    }
	return dsu_p[v] = find_sets(dsu_p[v]);
}
 
int get_root(int v) {
    return dsu_r[find_sets(v)];
}
 
void union_sets(int u, int v, int r) {
	v = find_sets(v);
	u = find_sets(u);
	if (rand() % 2) {
		swap(v, u);
	}
	dsu_p[u] = v;
	dsu_r[u] = -1;
	dsu_r[v] = r;
}
 
void dfs2(int v) {
	dsu_p[v] = v;
	dsu_r[v] = v;
	used[v] = true;
	for (int i = 0; i < (int)arr[v].size(); i++) {
		int u = arr[v][i];
		dfs2(u);
		union_sets(v, u, v);
	}
	for (int i = 0; i < (int)q[v].size(); i++) {
		if (used[q[v][i]]) {
			result.push_back(get_root(q[v][i]));
		}
    }
}
 
vector <pair <int, int> > f;
int root;
 
vector <int> get_lca() {
	for (int i = 0; i < (int)f.size(); i++) {
		q[f[i].first].push_back(f[i].second);
		q[f[i].second].push_back(f[i].first);
	}
	dfs2(root);
 
	return result;
}
 
int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
 
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &par[i], &c[i]);
		c[i]--;
		par[i]--;
		if (par[i] != -1) {
			arr[par[i]].push_back(i);
		}
		else {
			root = i;
		}
	}
 
	dfs1(root);
	if (n > MAXN) {
		cout << -1;
		return 0;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 1; j < (int)col[i].size(); j++) {
			int c1 = col[i][j - 1];
			int c2 = col[i][j];
			if (in(c1, c2)) {
				result.push_back(c2);
			}
			else if (in(c2, c1))
				result.push_back(c1);
			else {
				f.push_back(make_pair(c1, c2));
			}
		}
		for (int j = 0; j < (int)col[i].size(); j++) {
			ccnt[col[i][j]]++;
		}
	}
 
	vector <int> lca = get_lca();
	for (int i = 0; i < (int)lca.size(); i++) {
		ccnt[lca[i]]--;
	}
 
	cnt(root);
 
	for (int i = 0; i < n; i++) {
		printf("%d ", ans[i]);
	}
 
	return 0;
}