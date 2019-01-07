            #include <bits/stdc++.h>
     
            using namespace std;
     
            typedef long long ll;
     
            const int MAXN = (int)2e5 + 5;
     
            ll n, m;
            int tin[MAXN], tout[MAXN], used[MAXN];
            vector <int> arr[MAXN], lst;
            int st[20][MAXN], pl[20][MAXN];
            int pw[MAXN], deep[MAXN];
            int tme = 0;
     
            void dfs(int v, int dp) {
            	tin[v] = tme;
            	tout[v] = -1;
            	deep[v] = dp;
            	tme++;
            	used[v] = 1;
            	lst.push_back(v);
            	for (int i = 0; i < (int)arr[v].size(); i++) {
            		int u = arr[v][i];
            		if (used[u] == 0) {
            			dfs(u, dp + 1);
            			tout[v] = tme;
            			lst.push_back(v);
            			tme++;
            		}
            	}
            	if (tout[v] == -1) {
            		tout[v] = tin[v];
            	}
            }
     
     		int cnt(int l, int r) {
     			int dst = pw[r - l + 1];
     			if (r - (1 << dst) + 1 >= l && st[dst][l] > st[dst][r - (1 << dst) + 1]) {
        			return pl[dst][r - (1 << dst) + 1];
    			}
    			return pl[dst][l];
     		}
     
            int main() {
     			freopen("lca2.in", "r", stdin);
     			freopen("lca2.out", "w", stdout);
     
            	scanf("%lld%lld", &n, &m);
     
            	for (int i = 1; i < n; i++) {
            		int x;
            		scanf("%d", &x);
            		arr[x].push_back(i);
            	}
     
            	dfs(0, 0);
     
            	int sz = (int)lst.size();
     
            	for (int i = 0; i < tme; i++) {
            		st[0][i] = deep[lst[i]];
            		pl[0][i] = lst[i];
            	}
     
            	for (int k = 1; k < 20; k++) {
            		for (int i = 0; i < sz; i++) {
            			if (i + (1 << (k - 1)) < sz) {
            				st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            				if (st[k - 1][i] < st[k - 1][i + (1 << (k - 1))]) {
            					pl[k][i] = pl[k - 1][i];
            				}
            				else {
            					pl[k][i] = pl[k - 1][i + (1 << (k - 1))];
            				}
            			}
            			else {
            				st[k][i] = st[k - 1][i];
            				pl[k][i] = pl[k - 1][i]; 
            				break;
            			}
            		}
            	}
     
            	for (int i = 1; i < MAXN; i++) {
            		if (i == (1 << (pw[i - 1] + 1))) {
            			pw[i] = pw[i - 1] + 1;
            		}
        			else {
        				pw[i] = pw[i - 1];
        			}
            	}
     
     			ll aa1, aa2, aaa1, aaa2;
            	
            	ll x, y, z;
            	scanf("%lld%lld%lld%lld%lld", &aa1, &aa2, &x, &y, &z);
            	ll ans = 0;
            	
            	ll ch = 0;
            	for (int i = 0; i < m; i++) {
            		ll a1 = (aa1 + ch) % n, a2 = aa2;
            		ch = cnt(min(tin[a1], tin[a2]), max(tout[a1], tout[a2]));
            		ans += ch;
            		aaa1 = (aa1*x + aa2*y + z)%n;
					aaa2 = (aa2*x + aaa1*y + z)%n;
					//cout << "		" << aaa1 << "   " << aaa2 << endl;
					aa1 = aaa1;
					aa2 = aaa2;
            	}
				printf("%lld", ans);
     
            	return 0;
            }