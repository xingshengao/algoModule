// https://loj.ac/p/132
#include <bits/stdc++.h>
#define int long long

using namespace std;

struct SegTree {

    int n;
    vector<int> d, lazy;

    SegTree() {}
    SegTree(int n) {
        this->n = n;
        d = vector<int> (n * 4 + 5);
        lazy = vector<int> (n * 4 + 5);
    }

    void push_down(int p, int l, int r, int m) {
        if (lazy[p] != 0) {
            d[p << 1] += lazy[p] * (m - l + 1);
            d[p << 1 | 1] += lazy[p] * (r - m);
            lazy[p << 1] += lazy[p];
            lazy[p << 1 | 1] += lazy[p];
            lazy[p] = 0;
        }
    }

    void change(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) {
            d[p] += (r - l + 1) * v;
            lazy[p] += v;
            return;
        }
        int m = l + r >> 1;
        push_down(p, l, r, m);
        if (ql <= m) {
            change(p << 1, l, m, ql, qr, v);
        }
        if (qr > m) {
            change(p << 1 | 1, m + 1, r, ql, qr, v);
        }
        d[p] = d[p << 1] + d[p << 1 | 1];
    }

    int query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return d[p];
        }
        int m = l + r >> 1;
        int res = 0;
        push_down(p, l, r, m);
        if (ql <= m) {
            res += query(p << 1, l, m, ql, qr);
        }
        if (qr > m) {
            res += query(p << 1 | 1, m + 1, r, ql, qr);
        }
        return res;
    }

    void change(int ql, int qr, int v) {
        change(1, 0, n, ql, qr, v);
    }

    int query(int ql, int qr) {
        return query(1, 0, n, ql, qr);
    }

};

signed main() {
    int n, m;
    cin >> n >> m;
    SegTree S(n);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        S.change(i, i, a);
    }
    while (m--) {
        int op, l, r, v;
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> v;
            S.change(l, r, v);
        } else {
            cin >> l >> r;
            cout << S.query(l, r) << endl;
        }
    }
    return 0;
}
