// 例题:https://loj.ac/p/132
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct SegTree {
    
    int cnt;
    vector<int> tr, lson, rson, lazy;

    SegTree() {}
    SegTree(int n) {    // 能开多大就开多大
        cnt = 2;
        tr.resize(n);
        lson.resize(n);
        rson.resize(n);
        lazy.resize(n);
    }

    void push_down(int p, int l, int r, int m) {
        if (lazy[p]) {
            tr[lson[p]] += lazy[p] * (m - l + 1);
            tr[rson[p]] += lazy[p] * (r - m);
            lazy[lson[p]] += lazy[p];
            lazy[rson[p]] += lazy[p];
            lazy[p] = 0;
        }
    }

    void change(int p, int l, int r, int L, int R, int v) {
        if (r < L || l > R) {
            return;
        } else if (L <= l && r <= R) {
            tr[p] += (r - l + 1) * v;
            lazy[p] += v;
        } else {
            int m = l + r >> 1;
            if (lson[p] == 0) lson[p] = cnt++;
            if (rson[p] == 0) rson[p] = cnt++;
            push_down(p, l, r, m);
            change(lson[p], l, m, L, R, v);
            change(rson[p], m + 1, r, L, R, v);
            tr[p] = tr[lson[p]] + tr[rson[p]];
        }
    }


    int query(int p, int l, int r, int L, int R) {
        if (r < L || l > R) {
            return 0;
        } else if (L <= l && r <= R) {
            return tr[p];
        } else {
            int m = l + r >> 1;
            if (lson[p] == 0) lson[p] = cnt++;
            if (rson[p] == 0) rson[p] = cnt++; 
            push_down(p, l, r, m);
            return query(lson[p], l, m, L, R) + query(rson[p], m + 1, r, L, R);
        }
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    SegTree S(4 * n);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        S.change(1, 1, n, i, i, a);
    }
    while (m--) {
        int op, l, r, v;
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> v;
            S.change(1, 1, n, l, r, v);
        } else {
            cin >> l >> r;
            cout << S.query(1, 1, n, l, r) << endl;
        }
    }
    return 0;
}
