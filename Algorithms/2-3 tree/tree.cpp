#include <bits/stdc++.h>

using namespace std;

struct Tree {
	int sz, x;
	Tree *left, *right;
	Tree(int x = 0) : sz(1), x(x), left(NULL), right(NULL) {}
};

void update(Tree *x) {
	if (x == NULL)
		return;
	x->sz = 1;
	if (x->left != NULL)
		x->sz += x->left->sz;
	if (x->right != NULL)
		x->sz += x->right->sz;
}

void set_edge(Tree *parent, Tree *x, bool k) {
	update(x);
	update(parent);
	if (k == 0)
		parent->left = x;
	else if (k == 1)
		parent->right = x;
	update(x);
	update(parent);
}

vector <pair <Tree*, bool> > len;

void find_(Tree *root, int pos) {
	Tree *x = root;
	len.push_back(make_pair(root, 0));
	while (true) {
		if (x == NULL) {
			return;
		}
		int lsz = 0;
		if (x->left != NULL) {
			lsz = x->left->sz;
		}
		if (pos - lsz == 0) {
			return;
		}
		if (lsz + 1 <= pos) {
			pos -= lsz + 1;
            x = x->right;
			if (x == NULL) {
				return;
			}
			len.push_back(make_pair(x, 1));
		}
		else {
			x = x->left;
			len.push_back(make_pair(x, 0));
		}
	}
}

void splay(Tree *&root, int pos) {
	len.clear();
	find_(root, pos);
	for (int i = (int)len.size() - 1; i >= 1; i--) {
		if (i > 1) {
			Tree *x = len[i].first, *p = len[i - 1].first, *g = len[i - 2].first;
			bool k1 = len[i].second, k2 = len[i - 1].second, k3 = len[i - 2].second;
			if (k1 == 0) {
				p->left = x;
			}
			if (k1 == 1) {
				p->right = x;
			}
			if (k2 == 0) {
				g->left = p;
			}
			if (k2 == 1) {
				g->right = p;
			}
			len.pop_back();
			len.pop_back();
			len.pop_back();
			if (g->left == p && p->left == x) {
				set_edge(g, p->right, 0);
				set_edge(p, g, 1);
				set_edge(p, x->right, 0);
				set_edge(x, p, 1);
			} else if (g->right == p && p->right == x) {
				set_edge(g, p->left, 1);
				set_edge(p, g, 0);
				set_edge(p, x->left, 1);
				set_edge(x, p, 0);
			} else if (g->right == p && p->left == x) {
				set_edge(p, x->right, 0);
				set_edge(x, p, 1);
				set_edge(g, x->left, 1);
				set_edge(x, g, 0);
			} else if (g->left == p && p->right == x) {
				set_edge(p, x->left, 1);
				set_edge(x, p, 0);
				set_edge(g, x->right, 0);
				set_edge(x, g, 1);
			}
			len.push_back(make_pair(x, k3));
			i--;
		}
		else {
            Tree *x = len[i].first, *p = len[i - 1].first;
			bool k1 = len[i].second, k2 = len[i - 1].second;
			if (k1 == 0) {
				p->left = x;
			}
			if (k1 == 1) {
				p->right = x;
			}
			len.pop_back();
			len.pop_back();
			if (p->left == x) {
				set_edge(p, x->right, 0);
				set_edge(x, p, 1);
			}
			else if (p->right == x) {
				set_edge(p, x->left, 1);
				set_edge(x, p, 0);
			}
			len.push_back({x, k2});
		}
	}
	root = len[0].first;
}

Tree *merge_(Tree *l, Tree *r) {
	if (l == NULL) {
		return r;
	}
	if (r == NULL) {
		return l;
	}
	splay(l, l->sz - 1);
	l->right = r;
	update(l);
	return l;
}

void split(Tree *root, Tree *&l, Tree *&r, int sz_left) {
	if (root == NULL) {
		l = NULL;
        r = NULL;
		return;
	}
	if (sz_left >= root->sz) {
		l = root;
        r = NULL;
		return;
	}
	splay(root, sz_left);
	l = root->left;
	root->left = NULL;
	update(root);
	r = root;
}

void movetofront(Tree *&root, int x, int y) {
	Tree *l = NULL, *r = NULL, *m = NULL, *r1 = NULL;
	split(root, l, r1, x);
	split(r1, m, r, y - x + 1);
	root = merge_(merge_(m, l), r);
}

void add(Tree *&root, int pos, int x) {
	Tree *l, *r;
	split(root, l, r, pos);
	root = new Tree(x);
	root->left = l, root->right = r;
	update(root);
}

Tree *root = NULL;

void print_tree(Tree *root) {
	if (root == NULL)
		return;
	print_tree(root->left);
	printf("%d ", root->x);
	print_tree(root->right);
}

int main() {
	//freopen("input.txt", "r", stdin);
	freopen("movetofront.in", "r", stdin);
	freopen("movetofront.out", "w", stdout);

	ios_base::sync_with_stdio(false);

	int n, m; scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		add(root, i, i + 1);

	for (int i = 0; i < m; i++) {
		int l, r; scanf("%d%d", &l, &r);
		l--;
		r--;
		movetofront(root, l, r);
	}

	print_tree(root);
	printf("\n");

	return 0;
}
