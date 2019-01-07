#include <bits/stdc++.h>

using namespace std;

const int MAXN = 4e5 + 5;

struct Node {
	int len, link;
	map <char, int> next;
	Node(int len = 0, int link = -1) : len(len), link(link) {}
};

Node st[2 * MAXN];
int sz, last;

void init() {
	last = 0;
	sz = 1;
	for (int i = 0; i < 2 * MAXN; i++) {
		st[i] = Node();
    }
}


void add(char c) {
	int cur = sz++;
	st[cur].len = st[last].len + 1;
	int p = last;
	while (true) {
		if (p == -1 || st[p].next.count(c)) {
            break;
		}
		st[p].next[c] = cur;
		p = st[p].link;
	}
	if (p == -1)
		st[cur].link = 0;
	else {
		int q = st[p].next[c];
		if (st[p].len + 1 == st[q].len) {
			st[cur].link = q;
		}
		else {
			int nq = sz++;
			st[nq].len = st[p].len + 1;
			st[nq].next = st[q].next;
			st[nq].link = st[q].link;
			while (true) {
				if (p == -1 || st[p].next[c] != q) {
                    break;
				}
				st[p].next[c] = nq;
				p = st[p].link;
			}
			st[q].link = st[cur].link = nq;
		}
	}

	last = cur;
}

int main() {
	freopen("freedom.in", "r", stdin);
	freopen("freedom.out", "w", stdout);

	ios_base::sync_with_stdio(false);

	int n;
	string s, t;
	cin >> n >> s >> t;
	init();
	for (int i = 0; i < (int)s.size(); i++) {
		add(s[i]);
	}

	int l = 0, v = 0, ans_len = 0, pos = 0;

	for (int i = 0; i < (int)t.size(); i++) {
        while (v && !st[v].next.count(t[i])) {
            v = st[v].link;
            l = st[v].len;
        }
        if (st[v].next.count(t[i])) {
            v = st[v].next[t[i]];
            l++;
        }
        if (l > ans_len) {
            ans_len = l;
            pos = i;
        }
	}

	for (int i = pos - ans_len + 1; i <= pos; i++) {
        cout << t[i];
	}

	return 0;
}
