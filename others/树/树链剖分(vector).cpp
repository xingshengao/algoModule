// 例题: https://www.luogu.com.cn/problem/P3384
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

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

struct TreeCut {
    
    int root, cnt, n;           // 树以root为根
    vector<int> dep;            // dep[i]表示编号为i的节点的深度
    vector<vector<int>> edges;  // 存储边
    vector<int> fa;             // fa[i]表示编号为i的节点的父亲
    vector<int> sz;             // sz[i]表示编号为i为根的子树的节点数
    vector<int> hson;           // hson[i]表示编号为i的节点的重儿子
    vector<int> top;            // top[i]表示编号为i的节点重链中深度最小的节点
    vector<int> dfsn;           // dfsn[i]表示编号为i的节点的进入时间
    vector<int> rdfsn;          // rdfsn[i]表示编号为i的节点的离开时间
    SegTree S;
    
    TreeCut() {}
    TreeCut(int root, int n) {     // 构造函数，传入根节点, 结点数
        this->root = root;
        this->n = n;
        cnt = 1;
        S = SegTree(n + 5);
        dep.resize(n + 5);
        edges.resize(n + 5);
        fa.resize(n + 5);
        sz.resize(n + 5);
        hson.resize(n + 5);
        top.resize(n + 5);
        dfsn.resize(n + 5);
        rdfsn.resize(n + 5);
    }

    void addEdge(int u, int v) {        // 添加一条u与v相通的边
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    void init() {   // 加边后初始化
        top[root] = root;
        dfs1(root, 1);
        dfs2(root);
    }

    void dfs1(int root, int deep) {
        int size = 1, maxv = 0;
        dep[root] = deep;
        for (int nxt : edges[root]) {
            if (!dep[nxt]) {
                dfs1(nxt, deep + 1);
                fa[nxt] = root;
                size += sz[nxt];
                if (sz[nxt] > maxv) {
                    hson[root] = nxt;
                    maxv = sz[nxt];
                }
            }
        }
        sz[root] = size;
    }

    void dfs2(int root) {
        dfsn[root] = cnt++;
        if (hson[root] != 0) {
            top[hson[root]] = top[root];
            dfs2(hson[root]);
        }
        for (int nxt : edges[root]) {
            if (!top[nxt]) {
                top[nxt] = nxt;
                dfs2(nxt);
            }
        }
        rdfsn[root] = cnt - 1;
    }

    int lca(int a, int b) {                     // 求编号为a和b的最近公共祖先
        while (top[a] != top[b]) {
            if (dep[top[a]] > dep[top[b]]) {
                a = fa[top[a]];
            } else {
                b = fa[top[b]];
            }
        }
        return (dep[a] > dep[b] ? b : a);
    }

    void update_path(int x, int y, int val) {   // 链x->y上所有点加上val
        while (top[x] != top[y]) {
            if (dep[top[x]] > dep[top[y]]) {
                S.change(dfsn[top[x]], dfsn[x], val);
                x = fa[top[x]];
            } else {
                S.change(dfsn[top[y]], dfsn[y], val);
                y = fa[top[y]];
            }
        }
        if (dep[x] > dep[y]) {
            S.change(dfsn[y], dfsn[x], val);
        } else {
            S.change(dfsn[x], dfsn[y], val);
        }
    }

    int query_path(int x, int y) {   // 链x->y上所有点的和
        int res = 0;
        while (top[x] != top[y]) {
            if (dep[top[x]] > dep[top[y]]) {
                res += S.query(dfsn[top[x]], dfsn[x]);
                x = fa[top[x]];
            } else {
                res += S.query(dfsn[top[y]], dfsn[y]);
                y = fa[top[y]];
            }
        }
        if (dep[x] > dep[y]) {
            res += S.query(dfsn[y], dfsn[x]);
        } else {
            res += S.query(dfsn[x], dfsn[y]);
        }
        return res;
    }

    void update_subtree(int x, int val) {   // 以x为根的子树上所有点加上val
        S.change(dfsn[x], rdfsn[x], val);
    }

    int query_subtree(int x) {             // 以x为根的子树上所有点的和
        return S.query(dfsn[x], rdfsn[x]);
    }

};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, root, p;
    cin >> n >> m >> root >> p;
    TreeCut T(root, n);
    vector<int> value(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> value[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        T.addEdge(x, y);
    }
    T.init();
    for (int i = 1; i <= n; i++) {
        T.update_path(i, i, value[i]);
    }
    while (m--) {
        int op, x, y, z;
        cin >> op;
        if (op == 1) {
            cin >> x >> y >> z;
            T.update_path(x, y, z);
        } else if (op == 2) {
            cin >> x >> y;
            cout << T.query_path(x, y) % p << endl;
        } else if (op == 3) {
            cin >> x >> z;
            T.update_subtree(x, z);
        } else {
            cin >> x;
            cout << T.query_subtree(x) % p << endl;
        }
    }
}