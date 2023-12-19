// https://www.luogu.com.cn/problem/SP10707
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

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
    vector<int> euler;          // 欧拉序列
    
    TreeCut() {}
    TreeCut(int root, int n) {     // 构造函数，传入根节点, 结点数
        this->root = root;
        this->n = n;
        cnt = 1;
        dep.resize(n + 5);
        edges.resize(n + 5);
        fa.resize(n + 5);
        sz.resize(n + 5);
        hson.resize(n + 5);
        top.resize(n + 5);
        dfsn.resize(n + 5);
        rdfsn.resize(n + 5);
        euler.resize(2 * n + 5);
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
        euler[cnt] = root;
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
        euler[cnt] = root;
        rdfsn[root] = cnt++;
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

};

int n, m;

struct query {
    int l, r, id, lca;

    bool operator < (const query& x) const {
        int m = sqrt(2 * n);    // 因为dfsn, rdfsn的大小都是n, 所以取块的大小时要用2n, 而不是n
        if (l / m != x.l / m) return l < x.l;
        return (l / m) & 1 ? (r < x.r) : (r > x.r);
    }
};

int nowRes = 0;
vector<int> v, cnt, res, used;
vector<query> querys;

void add(int pos) {
    if (cnt[v[pos]] == 0) nowRes++;
    cnt[v[pos]]++;
}

void del(int pos) {
    cnt[v[pos]]--;
    if (cnt[v[pos]] == 0) nowRes--;
}

void calc(int x) {    // 对点进行加入或删除
    if (used[x]) del(x);
    else add(x);
    used[x] ^= 1;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    v = vector<int> (n + 1);
    res = vector<int> (m + 1);
    querys = vector<query> (m + 1);
    cnt = vector<int> (1000005);
    used = vector<int> (n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    // 离散化
    vector<int> t = v;
    sort(t.begin() + 1, t.end());
    for (int i = 1; i <= n; i++) {
        v[i] = lower_bound(t.begin() + 1, t.end(), v[i]) - t.begin();
    }
    TreeCut T(1, n);
    for (int i = 1; i <= n - 1; i++) {
        int a, b;
        cin >> a >> b;
        T.addEdge(a, b);
    }
    T.init();
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        if (T.euler[a] > T.euler[b]) swap(a, b);    // 保证a的欧拉序更小
        querys[i].id = i;
        querys[i].lca = T.lca(a, b);
        if (querys[i].lca == a) {
            querys[i].l = T.dfsn[a];
            querys[i].r = T.dfsn[b];
            querys[i].lca = -1;
        } else {
            querys[i].l = T.rdfsn[a];
            querys[i].r = T.dfsn[b];
        }
    }
    sort(querys.begin() + 1, querys.begin() + m + 1);
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        int ql = querys[i].l, qr = querys[i].r, id = querys[i].id, lca = querys[i].lca;
        while (l > ql) calc(T.euler[--l]);
        while (r < qr) calc(T.euler[++r]);
        while (l < ql) calc(T.euler[l++]);
        while (r > qr) calc(T.euler[r--]);
        if (lca != -1) calc(lca);
        res[id] = nowRes;
        if (lca != -1) calc(lca);
    }
    for (int i = 1; i <= m; i++) {
        cout << res[i] << endl;
    }
}