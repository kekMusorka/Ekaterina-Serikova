#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll P = 239, M = 15000001;

ll h[(int)1e6], p[(int)1e6];

ll hash_(int l, int r) {
    if (l != 0) return (((((h[r - 1] - (h[l - 1] * p[r - l]) % M) + M)% M)) + M) % M;
    else return h[r - 1];
}

int main() {
    freopen("cyclic-shift.in", "r", stdin);
    freopen("cyclic-shift.out", "w", stdout);
    p[0] = 1;
    for (int i = 1; i < 10002; i++) {
        p[i] = (p[i - 1] * P) % M;
    }
    string s;
    cin >> s;
    int n = (int)s.size();
    s += s;
    h[0] = s[0];
    for (int i = 0; i < 2*n; i++) {
        h[i] = (((h[i - 1] * P) % M) + s[i] + M) % M;
    }
    int ans = 0;
    for (int i = 1; i < n; i++) {
        ll b = -1, e = n + 1;
        while (b + 1 != e) {
            ll m = (b + e) / 2;
            if (hash_(i, i + m) == hash_(ans, ans + m)) {
                b = m;
            }
            else {
                e = m;
            }
        }
        if (b + 1 < n && s[i + b] < s[ans + b]) {
            ans = i;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << s[ans];
        ans++;
        if (ans == n) {
            ans = 0;
        }
    }
    return 0;
}
