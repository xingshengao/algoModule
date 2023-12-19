// https://loj.ac/p/130
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct SegTree {

    int value;
    SegTree* left;
    SegTree* right;

    SegTree() { 
        this->value = 0; 
        this->left = NULL;
        this->right = NULL;
    }

    void change(SegTree* root, int l, int r, int pos, int value) {
        if (l == r) {
            root->value += value;
            return;
        }
        int m = l + r >> 1;
        if (pos <= m) {
            if (root->left == NULL) root->left = new SegTree();
            change(root->left, l, m, pos, value);
        }
        if (m < pos) {
            if (root->right == NULL) root->right = new SegTree();
            change(root->right, m + 1, r, pos, value);
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

    void change(int pos, int value) {
        change(this, 0, 1e6, pos, value);
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
        S->change(i, v);
    }
    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            S->change(l, r);
        } else {
            cout << S->query(l, r) << endl;
        }
    }
}