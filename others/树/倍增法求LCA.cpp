// 例题: https://www.luogu.com.cn/problem/P3379
// https://loj.ac/p/10130
// https://leetcode.cn/problems/kth-ancestor-of-a-tree-node/
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct LCA {

    vector<int> depth;
    vector<vector<int>> g, fa;

    LCA() {}
    LCA(int n) {    // 构造函数,传入点数
        depth = vector<int> (n + 5, 1e9);
        g = vector<vector<int>> (n + 5);
        fa = vector<vector<int>> (n + 5);
    }

    void add(int u, int v) {    // 添加一条无向边
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void init(int x, int f, vector<int>& path, int deep) {    // 传入root, -1, {}, 1
        depth[x] = deep;
        for (int i = 1; i <= path.size(); i *= 2) {
            fa[x].push_back(path[path.size() - i]);
        }
        path.push_back(x);
        for (int y : g[x]) {
            if (y == f) continue;
            init(y, x, path, deep + 1);
        }
        path.pop_back();
    }

    int lca(int a, int b) { // 获取a和b的最近公共祖先
        if (depth[a] < depth[b]) swap(a, b);
        for (int i = 20; i >= 0; i--) {
            if (i < fa[a].size() && depth[fa[a][i]] >= depth[b]) {
                a = fa[a][i];
            }
        }
        if (a == b) return a;
        for (int i = 20; i >= 0; i--) {
            if (i < fa[a].size() && i < fa[b].size() && fa[a][i] != fa[b][i]) {
                a = fa[a][i];
                b = fa[b][i];
            }
        }
        return fa[a][0];
    }

    int getDist(int a, int b) { // 获取a和b之间的距离
        int lca_ab = lca(a, b);
        return depth[a] + depth[b] - 2 * depth[lca_ab];
    }

    int getKthAncestor(int x, int k) {  // 返回结点x的第k个祖先
        for (int i = 0; i < 20; i++) {
            if (k & (1 << i) && i < fa[x].size()) {
                x = fa[x][i];
                k -= 1 << i;
            }
        }
        if (k != 0) return -1;
        return x;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q, root;
    cin >> n >> q >> root;
    LCA S(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        S.add(u, v);
    }
    vector<int> t;
    S.init(root, -1, t, 1);
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << S.lca(a, b) << endl;
    }
    return 0;
}
