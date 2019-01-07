#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cassert>
#include <map>
#include <set>

using namespace std;

typedef long long ll;

const int MAXN = 1000000;
const int MAXK = 20;

int n;
vector <ll> g[MAXN];
vector <ll> a, c, c1, lcp;

int num(char r) { return (int)r - (int)'a' + 1; }

ll sp[MAXK][MAXN];

ll get_min_lcp(int l, int r) {
	ll k = 0;
	while (l + (1 << (k + 1)) <= r)
		k++;

	return min(sp[k][l], sp[k][r - (1 << k) + 1]);
}

int main() {
	freopen("keepcounted.in", "r", stdin);
	freopen("keepcounted.out", "w", stdout);

    ios_base::sync_with_stdio(false);

    string s;

    cin >> s;
    for (int i = 0; 2 * i < (int)s.length(); i++)
		swap(s[i], s[(int)s.length() - 1 - i]);
    s += char('a' - 1);
    n = (int)s.length();

    for (int i = 0; i < n; i++)
        g[num(s[i])].push_back(i);
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < (int)g[i].size(); j++)
            a.push_back(g[i][j]);
        g[i].clear();
    }
    c.resize((int)a.size());
    c1.resize((int)a.size());
    c[a[0]] = 0;
    for (int i = 1; i < (int)a.size(); i++)
        c[a[i]] = c[a[i - 1]] + (s[a[i]] != s[a[i - 1]]);

    for (int k = 0; (1 << k) <= 8 * n; k++) {
        for (int i = 0; i < n; i++) {
            int cur = (a[i] - (1 << k) + 10 * n) % n;
            g[c[cur]].push_back(cur);
        }
        a.clear();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < (int)g[i].size(); j++)
                a.push_back(g[i][j]);
            g[i].clear();
        }

        c1[a[0]] = 0;
        for (int i = 1; i < n; i++) {
            ll nxt1 = (a[i] + (1 << k)) % n;
            ll nxt2 = (a[i - 1] + (1 << k)) % n;
            c1[a[i]] = c1[a[i - 1]] + (c[a[i]] != c[a[i - 1]] || c[nxt1] != c[nxt2]);
        }
        c = c1;
    }

    vector <ll> r;
    r.resize(n);
    for (int i = 0; i < n; i++)
        r[a[i]] = i;
    lcp.resize(n - 1);
    ll d = 0;
    for (int i = 0; i < n - 1; i++) {
        d = max(d - 1, (ll)0);
        while (i + d < n && a[r[i] - 1] + d < n && s[i + d] == s[a[r[i] - 1] + d])
            d++;
        lcp[r[i] - 1] = d;
    }

    s.resize((int)s.length() - 1);
    for (int i = 0; i < (int)a.size() - 1; i++)
		a[i] = a[i + 1];
    a.resize((int)a.size() - 1);
    for (int i = 0; i < (int)lcp.size() - 1; i++)
		lcp[i] = lcp[i + 1];
	lcp.pop_back();
	n--;

    for (int i = 0; i < MAXN; i++)
		sp[0][i] = 1e9;
    for (int i = 0; i < (int)lcp.size(); i++)
		sp[0][i] = lcp[i];
	for (int k = 1; k < MAXK; k++)
		for (int i = 0; i < MAXN; i++) {
			if (i + (1 << (k - 1)) < MAXN) {
				sp[k][i] = min(sp[k - 1][i], sp[k - 1][i + (1 << (k - 1))]);
			} else
				sp[k][i] = sp[k - 1][i];
		}

	vector <pair <ll, ll> > p;
	for (int i = 0; i < (int)a.size(); i++)
		p.push_back(make_pair(-a[i], i));

	sort(p.begin(), p.end());

	ll answer = 0;

	set <ll> ss;
	for (ll kek228 = 0; kek228 < (int)p.size(); kek228++) {
		ll i = p[kek228].second;
		ll cur = -p[kek228].first;

		ll last = 0;
		set <ll> :: iterator it = ss.lower_bound(i);
		if (it != ss.end())
			last = max(last, get_min_lcp(i, (*it) - 1));
		if (it != ss.begin()) {
			it--;
			last = max(last, get_min_lcp((*it), i - 1));
		}

		answer += n - cur - last;

		cout << answer << endl;

		ss.insert(i);
	}

	return 0;
}

