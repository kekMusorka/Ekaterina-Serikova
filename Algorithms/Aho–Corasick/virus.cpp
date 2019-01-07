#include <bits/stdc++.h>

using namespace std;

int n;

struct point {
    int par;
    int kid[2];
    int child[2];
    int sufflink, superlink;
    bool term;
    point() {}
};

point *g[600010];

int col[600010];

int last = 1;

void Bor(string s) {
    int place = 1;
    for (int i = 0; i < (int)s.size(); i++) {
        if (g[place]->kid[s[i] - '0'] != -1) {
            place = g[place]->kid[s[i] - '0'];
        }
        else {
            last++;
            g[place]->kid[s[i] - '0'] = last;
            g[last]->par = place;
            place = last;
        }
        if (i == (int)s.size() - 1) {
            g[place]->term = true;
        }
    }
}

int Suff(int v, int color);

int Find_Suff(int v, int color) {
    if (g[v]->sufflink == -1) {
        if (g[g[v]->par]->kid[0] == v) {
            g[v]->sufflink = Suff(v, 0);
        }
        else {
            g[v]->sufflink = Suff(v, 1);
        }
    }
    int v_suff = g[v]->sufflink;
    if (g[v_suff]->kid[color] != -1) {
        return g[v_suff]->kid[color];
    }
    else {
        if (v_suff == 1) {
            if (g[v_suff]->kid[color] != -1) {
                return g[v_suff]->kid[color];
            }
            return 1;
        }
        else {
            return Find_Suff(v_suff, color);
        }
    }
}

int Suff(int v, int color) {
    if (g[v]->par == 1) {
        g[v]->sufflink = 1;
    }
    else {
        g[v]->sufflink = Find_Suff(g[v]->par, color);
    }
    for (int i = 0; i < 2; i++) {
        if (g[v]->kid[i] != -1) {
            Suff(g[v]->kid[i], i);
            g[v]->child[i] = g[v]->kid[i];
        }
        else {
            g[v]->child[i] = Find_Child(v, i);
        }
    }
    return g[v]->sufflink;
}

int Find_Child(int v, int color) {
    int v_suff = g[v]->sufflink;
    if (g[v_suff]->kid[color] != -1) {
        return g[v_suff]->kid[color];
    }
    else {
        if (v_suff == 1) {
            if (g[v_suff]->kid[color] != -1) {
                return g[v_suff]->kid[color];
            }
            return 1;
        }
        else {
            return Find_Child(v_suff, color);
        }
    }
}

int Find_Super(int v) {
    if (g[g[v]->sufflink]->term) {
        return g[v]->sufflink;
    }
    if (v == 1) {
        return v;
    }
    else {
        return Find_Super(g[v]->sufflink);
    }
}

void Super(int v) {
    if (g[v]->par == 1) {
        g[v]->superlink = 1;
    }
    else {
        g[v]->superlink = Find_Super(v);
    }
    for (int i = 0; i < 2; i++) {
        if (g[v]->kid[i] != -1) {
            Super(g[v]->kid[i]);
        }
    }
}

void write_() {
    for (int i = 1; i <= last; i++) {
        cout << i << endl;
        cout << "   " << g[i]->child[0] << ", " << g[i]->child[1] << "  " << g[i]->par << "     " << g[i]->term << endl;
        cout << "       " << g[i]->sufflink << "    " << g[i]->superlink << endl;
    }
}

void dfs(int v) {
    //cout << v << endl;
    col[v] = 1;
    for (int i = 0; i < 2; i++) {
        if (col[g[v]->child[i]] == 1) {
            cout << "TAK";
            exit(0);
        }
        if (col[g[v]->child[i]] == 0) {
            int v_child = g[v]->child[i];
            if (!g[v_child]->term && (g[v_child]->superlink == -1 || g[v_child]->superlink == 1)) {
                dfs(v_child);
            }
        }
    }
    col[v] = 2;
}

int main() {
    //freopen("input.txt", "r", stdin);
    freopen("virus.in", "r", stdin);
    freopen("virus.out", "w", stdout);
    cin >> n;
    int sz = 0;
    for (int i = 0; i < 600010; i++) {
        g[i] = new point();
        g[i]->par = -1;
        g[i]->kid[0] = -1;
        g[i]->kid[1] = -1;
        g[i]->sufflink = -1;
        g[i]->superlink = -1;
        g[i]->term = false;
    }
    g[1]->par = 1;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        sz += (int)s.size();
        Bor(s);
    }
    Suff(1, -1);
    Build(1);
    Super(1);
    //write_();
    dfs(1);
    cout << "NIE";
    return 0;
}
