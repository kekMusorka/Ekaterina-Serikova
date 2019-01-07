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

bool was[MAXN];

vector <pair <pair <int, int>, char> > all;
vector <int> allt;

void dfs(int i) {
	was[i] = true;
	for (map <char, int> :: iterator it = st[i].next.begin(); it != st[i].next.end(); ++it) {
		if (!was[(*it).second]) {
			dfs((*it).second);
		}
		all.push_back(make_pair(make_pair(i, (*it).second), (*it).first));
	}
}

int main() {
	freopen("automaton.in", "r", stdin);
	freopen("automaton.out", "w", stdout);

	ios_base::sync_with_stdio(false);

	string s; cin >> s;
	init();
	for (int i = 0; i < (int)s.length(); i++) {
		add(s[i]);
	}

	dfs(0);

	int i = last;
	while (i != 0) {
		allt.push_back(i);
		i = st[i].link;
	}
	allt.push_back(0);

	cout << sz << " " << (int)all.size() << endl;
	sort(all.begin(), all.end());
	for (int i = 0; i < (int)all.size(); i++) {
        cout << all[i].first.first + 1 << " " << all[i].first.second + 1 << " " << all[i].second << endl;
	}
	cout << (int)allt.size() << endl;
	for (int i = 0; i < (int)allt.size(); i++) {
		cout << allt[i] + 1 << " ";
	}
	cout << endl;

	return 0;
}
