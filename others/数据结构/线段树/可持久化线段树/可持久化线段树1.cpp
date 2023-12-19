// https://www.luogu.com.cn/problem/P3919
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct SegTree {

    struct node {
        int l, r;
        int v;
    };

    int idx;
    vector<node> tr;
    vector<int> root;   // 存每个版本根节点位置
    vector<int> a;      // 初始版本

    SegTree(int n = 1000005) {
        idx = 0;
        tr.resize(n * 25 + 5);  // 能开多大就开多大
        root.resize(n + 5);
    }

    void build(int& x, int l, int r) {
        x = ++idx;
        if (l == r) {
            tr[x].v = a[l];
            return;
        }
        int m = l + r >> 1;
        build(tr[x].l, l, m);
        build(tr[x].r, m + 1, r);
    }

    void change(int& x, int y, int l, int r, int pos, int v) {  // 在y版本的基础上, 新增x版本
        x = ++idx;
        tr[x] = tr[y];
        if (l == r) {
            tr[x].v = v;
            return;
        }
        int m = l + r >> 1;
        if (pos <= m) {
            change(tr[x].l, tr[y].l, l, m, pos, v);
        } else {
            change(tr[x].r, tr[y].r, m + 1, r, pos, v);
        }
    }

    int query(int x, int l, int r, int pos) {   // 询问x版本pos位置的值
        if (l == r) {
            return tr[x].v;
        }
        int m = l + r >> 1;
        if (pos <= m) {
            return query(tr[x].l, l, m, pos);
        } else {
            return query(tr[x].r, m + 1, r, pos);
        }
    }

};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n, m;
    int ver, op, x, y;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    SegTree S;
    S.a = a;    // 传入初始版本
    S.build(S.root[0], 1, n);
    for (int i = 1; i <= m; i++) {
        cin >> ver >> op;
        if (op == 1) {
            cin >> x >> y;
            S.change(S.root[i], S.root[ver], 1, n, x, y);
        } else {
            cin >> x;
            cout << S.query(S.root[ver], 1, n, x) << endl;
            S.root[i] = S.root[ver];
        }
    }
    return 0;
}
