        #include <bits/stdc++.h>
     
        using namespace std;
     
        typedef long long ll;
     
        const int MAXN = (int)1e5 + 5;
        const ll pw = 30;
        const ll inf = (ll)1e10;
     
        ll n, tin[MAXN], tout[MAXN], lvl[MAXN];
        vector <pair<ll, ll> > gr[MAXN];
        pair<ll, ll> sons[MAXN];
        ll up[MAXN][pw];
        ll mn[MAXN][pw];
        bool used[MAXN];
     
        ll t = 0;
     
        void dfs(int v, int p) {
            tin[v] = t;
            t++;
            up[v][0] = p;
            if (v != p) {
            	mn[v][0] = sons[v].second;
            }
            else {
            	mn[v][0] = inf;
            }
            used[v] = true;
            for (int i = 1; i < pw; i++) {
                up[v][i] = up[up[v][i - 1]][i - 1];
                mn[v][i] = min(mn[v][i - 1], mn[up[v][i - 1]][i - 1]);
            }
            for (int i = 0; i < (int)gr[v].size(); i++) {
                if (!used[gr[v][i].first]) {
                    lvl[gr[v][i].first] = lvl[v] + 1;
                    dfs(gr[v][i].first, v);
                }
            }
            tout[v] = t;
            t++;
        }
     
        bool par(ll x, ll y) {
            if (x == -1) return false;
            return tin[x] <= tin[y] && tout[x] >= tout[y];
        }
     
        ll cnt(ll x, ll y) {
            if (par(x, y)) {
                return x;
            }
            if (par(y, x)) {
                return y;
            }
            for (int i = pw - 1; i >= 0; i--) {
                if (!par(up[x][i], y)) {
                    x = up[x][i];
                }
            }
            return up[x][0];
        }
     
        int main() {
            freopen("minonpath.in", "r", stdin);
            freopen("minonpath.out", "w", stdout);
            cin >> n;
            for (int i = 1; i < n; i++) {
                ll x, y;
                cin >> x >> y;
                x--;
                gr[x].push_back(make_pair(i, y));
                sons[i] = make_pair(x, y);
            }
            dfs(0, 0);
            lvl[0] = 0;
            int m;
            cin >> m;
            for (int i = 0; i < m; i++) {
                int u, v;
                cin >> u >> v;
                u--;
                v--;
                int h = cnt(u, v);
                ll ans = inf;
                if (h != u) {
                	for (int j = pw - 1; j >= 0; j--) {
            			if (!par(up[u][j], h)) {
                	    	ans = min((ll)ans, (ll)mn[u][j]);
                	    	u = up[u][j];
                		}
            		}
            		if (u != h) {
            			ans = min(ans, (ll)sons[u].second);
            		}
                }
                if (h != v) {
                	for (int j = pw - 1; j >= 0; j--) {
            			if (!par(up[v][j], h)) {
                	    	ans = min((ll)ans, (ll)mn[v][j]);
                	    	v = up[v][j];
                		}
            		}
            		if (v != h) {
            			ans = min(ans, (ll)sons[v].second);
            		}
                }
                cout << ans << endl;
            }
            return 0;
        }