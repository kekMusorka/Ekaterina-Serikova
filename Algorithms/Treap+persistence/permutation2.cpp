#include <bits/stdc++.h>

using namespace std;

int arr[100005];
int n, m;

struct Treap {
	int key, prior, sz;
	Treap *left, *right;
	Treap(int key): key(key), prior(rand()), sz(1), left(NULL), right(NULL) {}
};

struct Tree {
    Treap *root;
    Tree *left, *right;
    Tree() : root(NULL), left(NULL), right(NULL) {}
};

int SZ(Treap *&root) {
    if (root == NULL) {
        return 0;
    }
    else {
        return root->sz;
    }
}

void update(Treap *&root) {
    if (root != NULL) {
        root->sz = SZ(root->left) + SZ(root->right) + 1;
    }
}

Treap *merge_(Treap *l, Treap *r) {
	if (r == NULL) {
		return l;
	}
	if (l == NULL) {
		return r;
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
	if (root->key < key) {
		Treap *tmp_l = NULL, *tmp_r = NULL;
		split(root->right, key, tmp_l, tmp_r);
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

void insert(Treap *&root, int key) {
    Treap *l = NULL, *r = NULL;
    split(root, key, l, r);
    Treap *x = new Treap(key);
    root = merge_(merge_(l, x), r);
}

Treap *change(Treap *root, int key) {
    if (root == NULL) {
        return NULL;
    }
    if (root->key < key) {
        root->right = change(root->right, key);
    }
    else {
        if (root->key > key) {
            root->left = change(root->left, key);
        }
        else {
            return merge_(root->left, root->right);
        }
    }
    update(root);
    return root;
}

void init(Tree *&ROOT, int l, int r) {
    ROOT = new Tree();
    if (l + 1 == r) {
        insert(ROOT->root, arr[l]);
        return;
    }
    init(ROOT->left, l, (l + r) / 2);
    init(ROOT->right, (l + r) / 2, r);
    for (int i = l; i < r; i++) {
        insert(ROOT->root, arr[i]);
    }
    return;
}

void SET(Tree *&ROOT, int l, int r, int place, int val1) {
    if (place < l || place >= r) {
        return;
    }
    ROOT->root = change(ROOT->root, arr[place]);
    insert(ROOT->root, val1);
    if (l + 1 == r) {
        return;
    }
    SET(ROOT->left, l, (l + r) / 2, place, val1);
    SET(ROOT->right, (l + r) / 2, r, place, val1);
}

int GET(Tree *&ROOT, int l, int r, int x, int y, int val_l, int val_r) {
    if (ROOT == NULL || ROOT->root == NULL) {
        return 0;
    }
    if (l >= y || r <= x) {
        return 0;
    }
    if (l >= x && r <= y) {
        Treap *tmp_l = NULL, *tmp_r = NULL, *tmp_ll = NULL, *tmp_rr = NULL;
        split(ROOT->root, val_l, tmp_l, tmp_r);
        split(tmp_r, val_r + 1, tmp_ll, tmp_rr);
        update(tmp_ll);
        int temp_ans = SZ(tmp_ll);
        ROOT->root = merge_(merge_(tmp_l, tmp_ll), tmp_rr);
        return temp_ans;
    }
    return GET(ROOT->left, l, (l + r) / 2, x, y, val_l, val_r) + GET(ROOT->right, (l + r) / 2, r, x, y, val_l, val_r);
}

int main() {
    //freopen("input.txt", "r", stdin);
    freopen("permutation2.in", "r", stdin);
    freopen("permutation2.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    Tree *ROOT = NULL;
    init(ROOT, 0, n);
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        if (s == "SET") {
            int a, b;
            cin >> a >> b;
            a--;
            SET(ROOT, 0, n, a, b);
            arr[a] = b;
        }
        else {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            a--;
            cout << GET(ROOT, 0, n, a, b, c, d) << endl;
        }
    }
    return 0;
}
