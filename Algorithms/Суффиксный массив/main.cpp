#include <bits/stdc++.h>

using namespace std;

int p[3*(int)1e5 + 5], c[3*(int)1e5 + 5], p2[3*(int)1e5 + 5], c2[3*(int)1e5 + 5];

char arr[3*(int)1e5 + 5];

int ans[3*(int)1e5 + 5];

vector <int> cl[1000];
int check[1000];

pair <int, pair <int, int> > nw[3*(int)1e5 + 5];

int main() {
    //freopen("suffarray.in", "r", stdin);
    //freopen("suffarray.out", "w", stdout);
    int n;
    string s;
    cin >> n >> s;
    s += '#';
    n++;
    for (int i = 0; i < n; i++) {
        arr[i] = s[i];
        cl[arr[i]].push_back(i);
    }
    sort(arr, arr + n);
    int id = 0, id2 = 0;
    for (int i = 0; i < n; i++) {
        if (check[arr[i]] == 0) {
            check[arr[i]] = 1;
            for (int j = 0; j < (int)cl[arr[i]].size(); j++) {
                int x = cl[arr[i]][j];
                p[x] = id2;
                id2++;
                c[x] = id;
            }
            if ((int)cl[arr[i]].size() != 0) id++;
        }
    }
    int k = 1;
    for (int i = 1; i < n; i++) {
        if (k >= n) {
            break;
        }
        k *= 2;
        for (int j = 0; j < n; j++) {
            p2[j] = p[j];
            c2[j] = c[j];
        }
        for (int j = 0; j < n; j++) {
            int x, y;
            x = c2[j];
            y = c2[(j + (k / 2)) % n];
            nw[j] = make_pair(x, make_pair(y, j));
        }
        sort(nw, nw + n);
        id = 0; id2 = 0;
        for (int j = 0; j < n; j++) {
            int x = nw[j].second.second;
            p[x] = id2;
            id2++;
            if (j == 0 || (j > 0
                && make_pair(nw[j].first, nw[j].second.first) == make_pair(nw[j - 1].first, nw[j - 1].second.first))) {
                c[x] = id;
            }
            else {
                id++;
                c[x] = id;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        ans[p[i]] = i + 1;
    }
    for (int i = 1; i < n; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
