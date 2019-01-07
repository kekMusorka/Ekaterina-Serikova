#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, m;

ll arr[200005];

tuple <ll, ll, ll> q[200005];

ll k = 800;

ll blocks[200005];

bool compare(tuple <ll, ll, ll> a, tuple <ll, ll, ll> b) {
    if (blocks[get<0>(a)] != blocks[get<0>(b)]) {
        return blocks[get<0>(a)] < blocks[get<0>(b)];
    }
    return get<1>(a) < get<1>(b);
}

ll cnt[1000006];

ll ans[1000006];

ll max_ = -1;

int main() {
    //freopen("input.txt", "r", stdin);
    freopen("power.in", "r", stdin);
    freopen("power.out", "w", stdout);
    cin >> n >> m;
    ll bl = -1;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        max_ = max(max_, arr[i]);
        if (i % k == 0) {
            bl++;
        }
        blocks[i] = bl;
    }
    for (int i = 0; i < m; i++) {
        cin >> get<0>(q[i]) >> get<1>(q[i]);
        get<0>(q[i])--;
        get<1>(q[i])--;
        get<2>(q[i]) = i;
    }
    sort(q, q + m, compare);
    ll l = 0, r = -1;
    ll temp_ans = 0;
    for (int i = 0; i < m; i++) {
        //cout << get<0>(q[i]) << " " << get<1>(q[i]) << endl;
        if (i == 0 || blocks[get<0>(q[i])] != blocks[get<0>(q[i - 1])]) {
            for (int j = 1; j <= max_; j++) {
                cnt[j] = 0;
            }
            l = get<0>(q[i]);
            r = get<0>(q[i]);
            cnt[arr[get<0>(q[i])]]++;
            temp_ans = arr[get<0>(q[i])];
        }
        while (l < get<0>(q[i])) {
            temp_ans -= (cnt[arr[l]] * cnt[arr[l]] * arr[l]);
            cnt[arr[l]]--;
            temp_ans += (cnt[arr[l]] * cnt[arr[l]] * arr[l]);
            l++;
        }
        while (l > get<0>(q[i])) {
            l--;
            temp_ans -= (cnt[arr[l]] * cnt[arr[l]] * arr[l]);
            cnt[arr[l]]++;
            temp_ans += (cnt[arr[l]] * cnt[arr[l]] * arr[l]);
        }
        while (r < get<1>(q[i])) {
            r++;
            temp_ans -= (cnt[arr[r]] * cnt[arr[r]] * arr[r]);
            cnt[arr[r]]++;
            temp_ans += (cnt[arr[r]] * cnt[arr[r]] * arr[r]);
        }
        while (r > get<1>(q[i])) {
            temp_ans -= (cnt[arr[r]] * cnt[arr[r]] * arr[r]);
            cnt[arr[r]]--;
            temp_ans += (cnt[arr[r]] * cnt[arr[r]] * arr[r]);
            r--;
        }
        l = get<0>(q[i]);
        r = get<1>(q[i]);
        ans[get<2>(q[i])] = temp_ans;
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
