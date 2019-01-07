#include <bits/stdc++.h>

using namespace std;

int n, m, k;
int leader[150006], r[150006];

tuple<string, int, int> q[150006];

vector <int> e[150006];

vector <string> ans;

int par(int v) {
    if (leader[v] == v) {
        return v;
    }
    else {
        return leader[v] = par(leader[v]);
    }
}

void ask(int a, int b) {
    if (par(a) == par(b)) {
        ans.push_back("YES");
    }
    else {
        ans.push_back("NO");
    }
}

void join_(int a, int b) {
    int root1 = par(a);
    int root2 = par(b);
    if (root1 == root2) {
        return;
    }
    if (r[root2] > r[root1]) {
        leader[root1] = root2;
        return;
    }
    if (r[root2] < r[root1]) {
        leader[root2] = root1;
        return;
    }
    leader[root1] = root2;
    r[root2]++;
}

int main() {
    freopen("in.in", "r", stdin);
    //freopen("cutting.out", "w", stdout);
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        e[a].push_back(b);
        e[b].push_back(a);
    }
    for (int i = 0; i < k; i++) {
        string s; int a, b;
        cin >> s >> a >> b;
        get<0>(q[i]) = s;
        get<1>(q[i]) = a - 1;
        get<2>(q[i]) = b - 1;
    }
    for (int i = 0; i < n; i++) {
        leader[i] = i;
        r[i] = 0;
    }
    for (int i = k - 1; i >= 0; i--) {
        string s;
        int a, b;
        s = get<0>(q[i]);
        a = get<1>(q[i]);
        b = get<2>(q[i]);
        if (s == "ask") {
            ask(a, b);
        }
        else {
            join_(a, b);
        }
    }
    for (int i = (int)ans.size() - 1; i >= 0; i--) {
        cout << ans[i] << endl;
    }
    return 0;
}
