// 例题: https://www.luogu.com.cn/problem/P3384
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct BIT {

    int n;
    vector<int> d, t1, t2;

    void init(int _n) {
        n = _n;
        d.resize(n + 5);
        t1.resize(n + 5);
        t2.resize(n + 5);
    }

    void add(int x, int v) {
        for (int i = x; i <= n; i += i & -i) {
            t1[i] += v;
            t2[i] += v * (x - 1);
        }
    }

    int ask(int x) {
        int res = 0;
        for (int i = x; i > 0; i -= i & -i) {
            res += x * t1[i] - t2[i];
        }
        return res;
    }

    void add_range(int l, int r, int v) {   // 单点修改和区间修改都用此函数
        add(l, v);
        add(r + 1, -v);
    }

    int ask_range(int l, int r) {   // 单点查询和区间查询都用此函数
        return ask(r) - ask(l - 1);
    }
};

struct TreeCut {
    
    int root, cnt;                       // 树以root为根
    unordered_map<int, int> dep;    // dep[i]表示编号为i的节点的深度
    unordered_map<int, vector<int>> edges;   // 存储边
    unordered_map<int, int> fa;     // fa[i]表示编号为i的节点的父亲
    unordered_map<int, int> sz;     // sz[i]表示编号为i为根的子树的节点数
    unordered_map<int, int> hson;   // hson[i]表示编号为i的节点的重儿子
    unordered_map<int, int> top;    // top[i]表示编号为i的节点重链中深度最小的节点
    unordered_map<int, int> dfsn;   // dfsn[i]表示编号为i的节点的进入时间
    unordered_map<int, int> rdfsn;  // rdfsn[i]表示编号为i的节点的离开时间
    BIT B;
    
    TreeCut() {}
    TreeCut(int root) {     // 构造函数，传入根节点
        this->root = root;
        cnt = 1;
        B.init(1000000);
    }

    void addEdge(int u, int v) {        // 添加一条u与v相通的边
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    void init() {   // 加边，加权值后初始化
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
                B.add_range(dfsn[top[x]], dfsn[x], val);
                x = fa[top[x]];
            } else {
                B.add_range(dfsn[top[y]], dfsn[y], val);
                y = fa[top[y]];
            }
        }
        if (dep[x] > dep[y]) {
            B.add_range(dfsn[y], dfsn[x], val);
        } else {
            B.add_range(dfsn[x], dfsn[y], val);
        }
    }

    int query_path(int x, int y) {   // 链x->y上所有点的和
        int res = 0;
        while (top[x] != top[y]) {
            if (dep[top[x]] > dep[top[y]]) {
                res += B.ask_range(dfsn[top[x]], dfsn[x]);
                x = fa[top[x]];
            } else {
                res += B.ask_range(dfsn[top[y]], dfsn[y]);
                y = fa[top[y]];
            }
        }
        if (dep[x] > dep[y]) {
            res += B.ask_range(dfsn[y], dfsn[x]);
        } else {
            res += B.ask_range(dfsn[x], dfsn[y]);
        }
        return res;
    }

    void update_subtree(int x, int val) {   // 以x为根的子树上所有点加上val
        B.add_range(dfsn[x], rdfsn[x], val);
    }

    int query_subtree(int x) {             // 以x为根的子树上所有点的和
        return B.ask_range(dfsn[x], rdfsn[x]);
    }

};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, root, p;
    cin >> n >> m >> root >> p;
    TreeCut T(root);
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