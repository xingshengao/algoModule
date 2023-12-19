// https://www.luogu.com.cn/problem/P3224
#include <bits/stdc++.h>
// #define int long long
#define endl '\n'

using namespace std;

struct SegTree {
    
    int cnt;
    vector<int> root, lson, rson, v;

    SegTree() {}
    SegTree(int root_cnt, int node_cnt) {    // 传入根节点个数和总节点个数
        cnt = 1;
        root = vector<int> (root_cnt + 5);
        for (int i = 1; i <= root_cnt; i++) { // 初始化根
            root[i] = cnt++;
        }
        lson = vector<int> (node_cnt + 5);
        rson = vector<int> (node_cnt + 5);
        v = vector<int> (node_cnt + 5);
    }

    void pushup(int p) {
        v[p] = v[lson[p]] + v[rson[p]];
    }

    void change(int p, int l, int r, int pos, int val) {
        if (l == r) {
            v[p] += val;
            return;
        }
        int m = l + r >> 1;
        if (pos <= m) {
            if (lson[p] == 0) lson[p] = cnt++;
            change(lson[p], l, m, pos, val);
        } else {
            if (rson[p] == 0) rson[p] = cnt++;
            change(rson[p], m + 1, r, pos, val);
        }
        pushup(p);
    }

    int merge(int r1, int r2, int l, int r) {   // 把r2合并到r1上
        if (!r1) return r2;
        if (!r2) return r1;
        if (l == r) {
            v[r1] += v[r2];
            return r1;
        }
        int m = l + r >> 1;
        lson[r1] = merge(lson[r1], lson[r2], l, m);
        rson[r1] = merge(rson[r1], rson[r2], m + 1, r);
        pushup(r1);
        return r1;
    }

    int kth(int p, int l, int r, int k) {
        if (l == r) {
            return v[p] >= k ? l : 0;
        }
        int m = l + r >> 1;
        if (v[lson[p]] >= k) {
            return kth(lson[p], l, m, k);
        } else {
            return kth(rson[p], m + 1, r, k - v[lson[p]]);
        }
    }
};

struct dsu {
    
    vector<int> fa, siz;

    dsu() {}
    dsu(int n) {
        fa.resize(n + 5);
        siz.resize(n + 5, 1);
        for (int i = 0; i < n + 5; i++) {
            fa[i] = i;
        }
    }

    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }

    bool merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        siz[a] += siz[b];
        fa[b] = a;
        return true;
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    int size(int x) {
        return siz[find(x)];
    }

};


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n, m;
    cin >> n >> m;
    vector<int> v2i(n + 1);
    v2i[0] = -1;
    SegTree S(n, 5000005);
    dsu D(n);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        v2i[a] = i;
        S.change(S.root[i], 1, n, a, 1);
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        int fx = D.find(x), fy = D.find(y);
        D.merge(fx, fy);
        S.merge(S.root[fx], S.root[fy], 1, n);
    }
    int q;
    cin >> q;
    while (q--) {
        string op;
        int x, y;
        cin >> op >> x >> y;
        if (op == "Q") {
            int fx = D.find(x);
            int val = S.kth(S.root[fx], 1, n, y);
            cout << v2i[val] << endl;
        } else {
            int fx = D.find(x), fy = D.find(y);
            D.merge(fx, fy);
            S.merge(S.root[fx], S.root[fy], 1, n);
        }
    }
    return 0;
}
