// https://www.luogu.com.cn/problem/P5490
#include <bits/stdc++.h>
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

    void pushup(SegTree* root, int l, int r) {
        if (root->lazy) {
            root->value = r - l + 1;
        } else {
            int res = 0;
            if (root->left != NULL) res += root->left->value;
            if (root->right != NULL) res += root->right->value;
            root->value = res;
        }
    }

    void change(SegTree* root, int l, int r, int ql, int qr, int value) {
        if (ql <= l && r <= qr) {
            root->lazy += value;
            pushup(root, l, r);
            return;
        }
        int m = l + r >> 1;
        if (ql <= m) {
            if (root->left == NULL) root->left = new SegTree();
            change(root->left, l, m, ql, qr, value);
        }
        if (m < qr) {
            if (root->right == NULL) root->right = new SegTree();
            change(root->right, m + 1, r, ql, qr, value);
        }
        pushup(root, l, r);
    }

    void change(int ql, int qr, int value) {
        change(this, 0, 1000000000, ql, qr, value);
    }

};

signed main() {
    int n;
    cin >> n;
    vector<vector<int>> edges;
    for (int i = 0; i < n; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        edges.push_back({a, b + 1, d, 1});
        edges.push_back({c, b + 1, d, -1});
    }
    SegTree S;
    sort(edges.begin(), edges.end());
    long long res = 0;
    int last = edges[0][0];
    for (int i = 0; i < edges.size(); i++) {
        res += ((long long)edges[i][0] - last) * S.value;
        last = edges[i][0];
        S.change(edges[i][1], edges[i][2], edges[i][3]);
    }
    cout << res << endl;
}