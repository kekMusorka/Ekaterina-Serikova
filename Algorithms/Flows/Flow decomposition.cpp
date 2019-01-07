#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6;

typedef long long ll;

int n, m;

struct reb {
    int v, u;
    ll c, f, z;
};

ll const inf = (ll)1e18;
vector <reb> edge;
vector <ll> d, place[MAXN], wch[MAXN];

ll max_c = 0;

deque <int> q;

void bfs(ll len) {
    q.clear();
    q.push_back(0);
    d[0] = 0;
    while (true) {
        if (q.empty()) {
            return;
        }
        int v = q.front();
        q.pop_front();
        for (int ii = 0; ii < (int)place[v].size(); ii++) {
            int i = place[v][ii];
            int u = edge[i].u;
            if ((d[u] <= d[v] + 1) || (edge[i].c - edge[i].f < len)) {
                continue;
            }
            d[u] = d[v] + 1;
            q.push_back(u);
        }
    }
}

void find_gr(ll len) {
    bfs(len);

    for(int i = 0; i < n; i++) {
        wch[i].clear();
    }

    for (int i = 0; i < edge.size(); i++) {
        int v = edge[i].v;
        int u = edge[i].u;
        ll c = edge[i].c;
        ll f = edge[i].f;
        if ((d[u] != d[v] + 1) || (c - f < len)) {
            continue;
        }
        wch[v].push_back(i);
    }
}

vector <ll> ans[MAXN];

int cc_numb = 0;

long long flow(int v, ll cmin, ll len) {
    if (v == n - 1) {
        return cmin;
    }
    while (!(wch[v].empty())) {
        int i = wch[v].back();
        int u = edge[i].u;
        if (edge[i].c - edge[i].f < len) {
            wch[v].pop_back();
            continue;
        }
        ll new_min = flow(u, min(cmin, edge[i].c - edge[i].f), len);
        if (new_min == 0) {
            wch[v].pop_back();
        }
        else {
            edge[i].f += new_min;
            edge[i ^ 1].f -= new_min;
            return new_min;
        }
    }
    return 0;
}

int used[MAXN];

int ccnt = 0;

ll mn;

void dfs(int v) {
    if (v == n - 1) {
        return;
    }
    for (int ii = 0; ii < (int)place[v].size(); ii++) {
        int i = place[v][ii];
        int u = edge[i].u;
        if (edge[i].f > 0 && used[i] == 0) {
            used[i] = 1;
            mn = min(mn, edge[i].f);
            ans[ccnt].push_back(edge[i].z);
            dfs(u);
            edge[i].f -= mn;
            used[i] = 0;
            break;
        }

    }
}

int main() {
    freopen("decomposition.in", "r", stdin);
    freopen("decomposition.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        ll z;
        cin >> x >> y >> z;
        x--; y--;
        reb e;
        e.v = x;
        e.u = y;
        e.c = z;
        e.f = 0;
        e.z = i + 1;
        edge.push_back(e);
        max_c = max(max_c, e.c);
        e.v = y;
        e.u = x;
        e.c = 0;
        e.f = 0;
        edge.push_back(e);
        place[x].push_back(edge.size() - 2);
        place[y].push_back(edge.size() - 1);
    }

    int sum = 0;

    ll st = 1LL << 31;
    while (st >= 1) {
        while (true) {
            d.clear();
            d.resize(n, inf);
            find_gr(st);
            if (d[n - 1] == inf) {
                break;
            }
            int cnt = 0;
            bool fl = true;
            while (true) {
                long long add_flow = flow(0, 1e9, st);
                sum += add_flow;
                if (add_flow == 0) {
                    break;
                }
            }
        }
        st /= 2;
    }

    while(true) {
        mn = 1e9;
        dfs(0);
        ans[ccnt].push_back(mn);
        //cout << mn << endl;
        if ((int)ans[ccnt].size() == 1) {
            break;
        }
        ccnt++;
    }

    cout << ccnt << endl;

    for(int i = 0; i < ccnt; i++) {
        cout << ans[i][(int)ans[i].size() - 1] << " ";
        int r = (int)ans[i].size() - 1;
        cout << r << " ";
        for(int j = 0; j < (int)ans[i].size() - 1; j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
