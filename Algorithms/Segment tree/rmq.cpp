#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll inf = -(ll)1e10;

int n, m;

tuple <int, int, ll> mn[100005];

struct Tree {
    ll min_;
    Tree *left, *right;
    Tree(ll mm) : min_(mm), left(NULL), right(NULL) {}
};

void init(Tree *&root, int l, int r) {
    if (l + 1 == r) {
        root = new Tree(inf);
        return;
    }
    root = new Tree(inf);
    init(root->left, l, (l + r) / 2);
    init(root->right, (l + r) / 2, r);
}

void change(Tree *&root, int l, int r, int a, int b, ll mi) {
    if (b <= l || a >= r) {
        return;
    }
    if (l + 1 == r) {
        root->min_ = max(root->min_, mi);
        return;
    }
    if (l >= a && r <= b) {
        root->min_ = max(root->min_, mi);
        return;
    }
    change(root->left, l, (l + r) / 2, a, b, mi);
    change(root->right, (l + r) / 2, r, a, b, mi);
}

void maximum(Tree *&root, int l, int r) {
    if (l + 1 == r) {
        return;
    }
    if (root->left != NULL) {
        root->left->min_ = max(root->left->min_, root->min_);
    }
    if (root->right != NULL) {
        root->right->min_ = max(root->right->min_, root->min_);
    }
    maximum(root->left, l, (l + r) / 2);
    maximum(root->right, (l + r) / 2, r);
}

void write_tree(Tree *root, int l, int r) {
    if (root == NULL) {
        return;
    }
    cout << "   " << l << ", " << r << "    " << root->min_ << endl;
    write_tree(root->left, l, (l + r) / 2);
    write_tree(root->right, (l + r) / 2, r);
}

ll arr[100005];

void build(Tree *root, int l, int r) {
    if (l + 1 == r) {
        if (root->min_ != inf) {
            arr[l] = root->min_;
        }
        else {
            arr[l] = 0;
        }
        return;
    }
    build(root->left, l, (l + r) / 2);
    build(root->right, (l + r) / 2, r);
}

void init2(Tree *&root, int l, int r) {
    if (l + 1 == r) {
        root = new Tree(arr[l]);
        return;
    }
    root = new Tree(-inf);
    init2(root->left, l, (l + r) / 2);
    init2(root->right, (l + r) / 2, r);
    ll m1 = -inf, m2 = -inf;
    if (root->left != NULL) {
        m1 = root->left->min_;
    }
    if (root->right != NULL) {
        m2 = root->right->min_;
    }
    root->min_ = min(m1, m2);
}

ll MIN = -inf;

void minimum(Tree *root, int l, int r, int a, int b) {
    if (b <= l || a >= r) {
        return;
    }
    if (l + 1 == r) {
        MIN = min(MIN, root->min_);
        return;
    }
    if (l >= a && r <= b) {
        MIN = min(MIN, root->min_);
        return;
    }
    minimum(root->left, l, (l + r) / 2, a, b);
    minimum(root->right, (l + r) / 2, r, a, b);
}

int main() {
    //freopen("input.txt", "r", stdin);
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
    Tree *root;
    cin >> n >> m;
    init(root, 0, n);
    for (int i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        get<0>(mn[i]) = a - 1;
        get<1>(mn[i]) = b;
        get<2>(mn[i]) = c;
    }
    for (int i = 0; i < m; i++) {
        change(root, 0, n, get<0>(mn[i]), get<1>(mn[i]), get<2>(mn[i]));
    }
    maximum(root, 0, n);
    //write_tree(root, 0, n);
    build(root, 0, n);
    Tree *ROOT;
    init2(ROOT, 0, n);
    for (int i = 0; i < m; i++) {
        MIN = -inf;
        minimum(ROOT, 0, n, get<0>(mn[i]), get<1>(mn[i]));
        if (MIN != get<2>(mn[i])) {
            cout << "inconsistent";
            return 0;
        }
    }
    cout << "consistent" << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}
