// https://loj.ac/p/132
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct SegTree {

    int value, lazy;
    SegTree* left;
    SegTree* right;

    SegTree() { 
        this->value = 0; 
        this->lazy = 0;
        this->left = NULL;
        this->right = NULL;
    }

    void push_down(SegTree* root, int l, int r, int m) {
        if (root->lazy != 0) {
            if (root->left == NULL) root->left = new SegTree();
            if (root->right == NULL) root->right = new SegTree();
            root->left->value += root->lazy * (m - l + 1);
            root->right->value += root->lazy * (r - m);
            root->left->lazy += root->lazy;
            root->right->lazy += root->lazy;
            root->lazy = 0;
        }
    }

    void change(SegTree* root, int l, int r, int ql, int qr, int value) {
        if (ql <= l && r <= qr) {
            root->value += (r - l + 1) * value;
            root->lazy += value;
            return;
        }
        int m = l + r >> 1;
        push_down(root, l, r, m);
        if (ql <= m) {
            if (root->left == NULL) root->left = new SegTree();
            change(root->left, l, m, ql, qr, value);
        }
        if (m < qr) {
            if (root->right == NULL) root->right = new SegTree();
            change(root->right, m + 1, r, ql, qr, value);
        }
        root->value = 0;
        if (root->left != NULL) root->value += root->left->value;
        if (root->right != NULL) root->value += root->right->value;
    }

    int query(SegTree* root, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return root->value;
        }
        int m = l + r >> 1;
        push_down(root, l, r, m);
        int res = 0;
        if (ql <= m) {
            if (root->left != NULL) {
                res += query(root->left, l, m, ql, qr);
            }
        }
        if (m < qr) {
            if (root->right != NULL) {
                res += query(root->right, m + 1, r, ql, qr);
            }
        }
        return res;
    }

    void change(int ql, int qr, int value) {
        change(this, 0, 1e6, ql, qr, value);
    }

    int query(int ql, int qr) {
        return query(this, 0, 1e6, ql, qr);
    }

};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    SegTree* S = new SegTree();
    for (int i = 1; i <= n; i++) {
        int v;
        cin >> v;
        S->change(i, i, v);
    }
    while (q--) {
        int op, l, r, value;
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> value;
            S->change(l, r, value);
        } else {
            cin >> l >> r;
            cout << S->query(l, r) << endl;
        }
    }
}