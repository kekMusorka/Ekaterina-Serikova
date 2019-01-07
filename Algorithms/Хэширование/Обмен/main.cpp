#include <bits/stdc++.h>

using namespace std;

//typedef long long ll;

unordered_map<int, int> mp(400005);

pair <int, int> sw[2 * (int)1e5];

int main() {
    freopen("swap.in", "r", stdin);
    freopen("swap.out", "w", stdout);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        mp[a] = a;
        mp[b] = b;
        sw[i].first = a;
        sw[i].second = b;
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        a = sw[i].first;
        b = sw[i].second;
        printf("%d\n", abs(mp[a] - mp[b]));
        swap(mp[a], mp[b]);
    }
    return 0;
}
