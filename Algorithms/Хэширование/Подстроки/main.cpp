#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll M = 1e9 + 7;
const ll MOD = 500003;
const ll P = 239;

ll h[11][10005];

ll p[10003];

ll hash_(int l, int r, int numb) {
    if (l != 0) return (((((h[numb][r - 1] - (h[numb][l - 1] * p[r - l]) % M) + M)% M)) + M) % M;
    else return h[numb][r - 1];
}

void Init_P() {
    p[0] = 1;
    for (int i = 1; i < 10002; i++) {
        p[i] = (p[i - 1] * P) % M;
    }
}

tuple <ll, ll, int> mp[1000004];

int check[1000004];

vector <int> rem;

int main() {
    freopen("substr.in", "r", stdin);
    freopen("substr.out", "w", stdout);
    ios_base::sync_with_stdio(false);

    string ans;
    string s[11];
    Init_P();
    int k;
    cin >> k;
    int max_len = -1;
    int min_len = 1e9;
    for (int i = 0; i < k; i++) {
        cin >> s[i];
        h[i][0] = s[i][0];
        int sz = (int)s[i].size();
        max_len = max(max_len, sz);
        min_len = min(min_len, sz);
        for (int j = 1; j < (int)s[i].size(); j++) {
            h[i][j] = (((h[i][j - 1] * P + s[i][j]) % M) + M) % M;
        }
    }
    ll b = 0, e = min_len + 1;
    ll ans_hash = -1;
    string ans_;
    while (b + 1 != e) {
        ll m = (b + e) / 2;
        int ch = 0;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < (int)s[i].size(); j++) {
                if (j + m - 1 >= (int)s[i].size()) {
                    break;
                }
                ll h_substr = hash_(j, j + m, i);
                ll id = (h_substr) % MOD;
                while (true) {
                    if (check[id] == 0) {
                        mp[id] = make_tuple(h_substr, 1, i);
                        rem.push_back(id);
                        check[id] = 1;
                        if (get<1>(mp[id]) == k) {
                            ch = 1;
                            ans_hash = h_substr;
                        }
                        break;
                    }
                    if (h_substr == (get<0>(mp[id]))) {
                        if (get<2>(mp[id]) != i) {
                            get<1>(mp[id])++;
                            get<2>(mp[id]) = i;
                            if (get<1>(mp[id]) == k) {
                                ch = 1;
                                ans_hash = h_substr;
                            }
                            break;
                        }
                    }
                    id++;
                    if (id == MOD) {
                        id = 0;
                    }
                }
            }
        }
        for (int i = 0; i < (int)rem.size(); i++) {
            check[rem[i]] = 0;
        }
        rem.clear();
        if (ch == 1) {
            b = m;
        }
        else {
            e = m;
        }
    }
    for (int i = 0; i < (int)s[0].size(); i++) {
        if (i + b - 1 >= (int)s[0].size()) {
            break;
        }
        if (hash_(i, i + b, 0) == ans_hash) {
            for (int j = i; j < i + b; j++) {
                ans_ += s[0][j];
            }
            cout << ans_;
            return 0;
        }
    }
    return 0;
}
