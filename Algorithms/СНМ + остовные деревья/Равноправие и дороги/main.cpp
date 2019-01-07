#include <bits/stdc++.h>

using namespace std;

tuple <int, int, int> e[200004];

int n, m, q;

int par[100005], rank_[100005];

int find_sets(int v) {
    if (v == par[v]) {
        return v;
    }
    else {
        return par[v] = find_sets(par[v]);
    }
}

bool together(int a, int b) {
    if (find_sets(a) == find_sets(b)) {
        return true;
    }
    else {
        return false;
    }
}

void union_sets(int a, int b) {
    int root1 = find_sets(a);
    int root2 = find_sets(b);
    if (root1 == root2) {
        return;
    }
    if (rank_[root2] > rank_[root1]) {
        par[root1] = root2;
        return;
    }
    if (rank_[root2] < rank_[root1]) {
        par[root2] = root1;
        return;
    }
    par[root1] = root2;
    rank_[root2]++;
}

int main() {
    //freopen("input.txt", "r", stdin);
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        get<0>(e[i]) = c;
        get<1>(e[i]) = a;
        get<2>(e[i]) = b;
    }
    sort(e, e + m);
    for (int i = 1; i <= n; i++) {
        rank_[i] = 0;
        par[i] = i;
    }
    int min_ = 0;
    for (int i = 0; i < m; i++) {
        if (!together(get<1>(e[i]), get<2>(e[i]))) {
            union_sets(get<1>(e[i]), get<2>(e[i]));
            min_ += (get<0>(e[i]));
        }
    }
    for (int i = 2; i <= n; i++) {
        if (find_sets(i) != find_sets(i - 1)) {
            for (int j = 0; j < q; j++) {
                int w;
                cin >> w;
                cout << "NO" << endl;
            }
            return 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        rank_[i] = 0;
        par[i] = i;
    }
    int max_ = 0;
    for (int i = m - 1; i >= 0; i--) {
        if (!together(get<1>(e[i]), get<2>(e[i]))) {
            union_sets(get<1>(e[i]), get<2>(e[i]));
            max_ += (get<0>(e[i]));
        }
    }
    for (int i = 2; i <= n; i++) {
        if (find_sets(i) != find_sets(i - 1)) {
            for (int j = 0; j < q; j++) {
                int w;
                cin >> w;
                cout << "NO" << endl;
            }
            return 0;
        }
    }
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        if (n - 1 - x >= min_ && n - 1 - x <= max_) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
