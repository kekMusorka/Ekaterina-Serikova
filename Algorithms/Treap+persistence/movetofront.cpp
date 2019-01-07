#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100005;

int arr[MAX_N];

struct Treap {
	int high, prior, k;
	Treap *left, *right;
	Treap(int _k) : high(1), k(_k), left(NULL), right(NULL) { this->prior = rand(); }
};

int high_(Treap *t) {
	if (t == NULL) {
		return 0;
	}
	return t->high;
}

void update(Treap *t) {
	t->high = high_(t->left) + high_(t->right) + 1;
}

Treap *merge_(Treap *l, Treap *r) {
	if (l == NULL) {
		return r;
	}
	if (r == NULL) {
		return l;
	}
	if (l->prior < r->prior) {
		r->left = merge_(l, r->left);
		update(r);
		return r;
	}
	else {
		l->right = merge_(l->right, r);
		update(l);
		return l;
	}
}


void split(Treap *root, int key, Treap *&l, Treap *&r) {
	if (root == NULL) {
		l = r = NULL;
		return;
	}
	if (high_(root->left) < key) {
		Treap *tmp_l = NULL, *tmp_r = NULL;
		split(root->right, key - high_(root->left) - 1, tmp_l, tmp_r);
		root->right = tmp_l;
		update(root);
		l = root, r = tmp_r;
		return;
	}
	else {
		Treap *tmp_l = NULL, *tmp_r = NULL;
		split(root->left, key, tmp_l, tmp_r);
		root->left = tmp_r;
		update(root);
		l = tmp_l, r = root;
		return;
	}
}

void write_treap(Treap *v) {
	if(v == NULL) {
		return;
	}
	write_treap(v->left);
	cout << v->k << " ";
	write_treap(v->right);
}

int main() {
	freopen("movetofront.in", "r", stdin);
	freopen("movetofront.out", "w", stdout);
	int n, m;
	cin >> n >> m;
	Treap *root = NULL;
	for (int i = 1; i <= n; i++) {
		arr[i] = i;
		Treap *t = new Treap(arr[i]);
		root = merge_(root, t);
	}
	for (int i = 0; i < m; i++) {
		int l, r;
		cin >> l >> r;
		Treap *k1, *k2, *k3;
		split(root, r, k1, k3);
		split(k1, l - 1, k1, k2);
		root = merge_(k1, k3);
		root = merge_(k2, root);
	}
	write_treap(root);
	return 0;
}
