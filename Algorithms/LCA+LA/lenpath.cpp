    #include <bits/stdc++.h>
     
    using namespace std;
     
    typedef long long ll;
     
    const int MAXN = (int)1e5 + 5;
    const int pw = 30;
     
    ll n, tin[MAXN], tout[MAXN], lvl[MAXN];
    vector <ll> gr[MAXN];
    ll up[MAXN][pw];
    bool used[MAXN];
     
    ll t = 0;
     
    void dfs(int v, int p) {
        tin[v] = t;
        t++;
        up[v][0] = p;
        used[v] = true;
        for (int i = 1; i < pw; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }
        for (int i = 0; i < (int)gr[v].size(); i++) {
            if (!used[gr[v][i]]) {
                lvl[gr[v][i]] = lvl[v] + 1;
                dfs(gr[v][i], v);
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
        freopen("lenpath.in", "r", stdin);
        freopen("lenpath.out", "w", stdout);
        cin >> n;
        for (int i = 0; i < n - 1; i++) {
            ll u, v;
            cin >> u >> v;
            u--;
            v--;
            gr[u].push_back(v);
            gr[v].push_back(u);
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
            int ans = lvl[v] + lvl[u] - 2*lvl[h];
            cout << ans << endl;
        }
        return 0;
    }