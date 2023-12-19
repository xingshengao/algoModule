// https://www.luogu.com.cn/problem/P3870
#include <bits/stdc++.h>

using namespace std;

struct SegTree {

    vector<int> d, lazy;

    SegTree() {}
    SegTree(int n) {
        d.resize(n * 4 + 5);
        lazy.resize(n * 4 + 5);
    }

    void push_down(int p, int l, int r, int m) {
        if (lazy[p] != 0) {
            d[p << 1] = m - l + 1 - d[p << 1];
            d[p << 1 | 1] = r - m - d[p << 1 | 1];
            lazy[p << 1] ^= 1;
            lazy[p << 1 | 1] ^= 1;
            lazy[p] = 0;
        }
    }

    void change(int p, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) {
            return;
        } else if (ql <= l && r <= qr) {
            d[p] = r - l + 1 - d[p];
            lazy[p] ^= 1;
            return;
        } else {
            int m = l + r >> 1;
            push_down(p, l, r, m);
            change(p << 1, l, m, ql, qr);
            change(p << 1 | 1, m + 1, r, ql, qr);
            d[p] = d[p << 1] + d[p << 1 | 1];
        }
    }

    int query(int p, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) {
            return 0;
        } else if (ql <= l && r <= qr) {
            return d[p];
        } else {
            int m = l + r >> 1;
			push_down(p, l, r, m);
            return query(p << 1, l, m, ql, qr) + query(p << 1 | 1, m + 1, r, ql, qr);
        }
    }

};

signed main() {
	int n, m;
	cin >> n >> m;
	SegTree S(n);
	while (m--) {
		int op, a, b;
		cin >> op >> a >> b;
		if (op == 0) {
			S.change(1, 1, n, a, b);
		} else {
			cout << S.query(1, 1, n, a, b) << endl;
		}
	}
}