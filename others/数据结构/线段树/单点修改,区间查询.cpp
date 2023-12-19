// https://loj.ac/p/130
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct SegTree {
    
    int n, inf = 2e9;
    vector<int> sum;
    
    SegTree() {}
    SegTree(int n) {
        this->n = n;
        sum = vector<int> (n * 4 + 5);
    }

    void change(int p, int l, int r, int pos, int val) {    // 单点修改
        if (l == r && l == pos) {
            sum[p] = val;
            return;
        }
        int m = l + r >> 1;
        if (pos <= m) {
            change(p * 2, l, m, pos, val);
        }
        if (m < pos) {
            change(p * 2 + 1, m + 1, r, pos, val);
        }
        sum[p] = sum[p * 2] + sum[p * 2 + 1];
    }

    int query(int p, int l, int r, int ql, int qr) {    // 查询区间sum
        if (ql <= l && r <= qr) {
            return sum[p];
        }
        int m = l + r >> 1;
        int res = 0;
        if (ql <= m) {
            res += query(p * 2, l, m, ql, qr);
        }
        if (qr > m) {
            res += query(p * 2 + 1, m + 1, r, ql, qr);
        }
        return res;
    }

    void change(int pos, int val) {
        change(1, 0, n, pos, val);
    }

    int query(int ql, int qr) {
        return query(1, 0, n, ql, qr);
    }

};

signed main() {
    int n, q;
    cin >> n >> q;
    SegTree Seg(n);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        Seg.change(i, a);
    }
    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            int now = Seg.query(l, l);
            Seg.change(l, now + r);
        } else {
            cout << Seg.query(l, r) << endl;
        }
    }
    return 0;
}