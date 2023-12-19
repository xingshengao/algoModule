// https://loj.ac/p/130
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct SegTree {
    
    int cnt;
    vector<int> tr, lson, rson;

    SegTree() {}
    SegTree(int n) {    // 能开多大就开多大
        cnt = 2;
        tr.resize(n);
        lson.resize(n);
        rson.resize(n);
    }

    void change(int p, int l, int r, int x, int v) {
        if (r < x || l > x) {
            return;
        } else if (l == r && l == x) {
            tr[p] = v;
        } else {
            int m = l + r >> 1;
            if (lson[p] == 0) lson[p] = cnt++;
            if (rson[p] == 0) rson[p] = cnt++;
            change(lson[p], l, m, x, v);
            change(rson[p], m + 1, r, x, v);
            tr[p] = tr[lson[p]] + tr[rson[p]];
        }
    }

    int query(int p, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) {
            return 0;
        } else if (ql <= l && r <= qr) {
            return tr[p];
        } else {
            int m = l + r >> 1;
            if (lson[p] == 0) lson[p] = cnt++;
            if (rson[p] == 0) rson[p] = cnt++; 
            return query(lson[p], l, m, ql, qr) + query(rson[p], m + 1, r, ql, qr);
        }
    }
};

signed main() {
    int n, q;
    cin >> n >> q;
    SegTree Seg(5000000);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        Seg.change(1, 1, n, i, a);
    }
    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            int now = Seg.query(1, 1, n, l, l);
            Seg.change(1, 1, n, l, now + r);
        } else {
            cout << Seg.query(1, 1, n, l, r) << endl;
        }
    }
    return 0;
}