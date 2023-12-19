// https://loj.ac/p/10134
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

// 点权公式: dis(x)+dis(y)-2*dis(LCA)+w[LCA]
// 边权公式: dis(x)+dis(y)-2*dis(LCA)
// 点权差分公式： dis(x)++, dis(y)++, dis(LCA(x, y))--, dis(fa[LCA(x, y)])--

struct TreePre {
    vector<int> depth, dis;
    vector<vector<int>> fa;
    vector<vector<vector<int>>> g;

    TreePre() {}
    TreePre(int n) {    // 构造函数,传入点数
        depth = vector<int> (n + 5, 1e9);
        dis = vector<int> (n + 5);
        g = vector<vector<vector<int>>> (n + 5);
        fa = vector<vector<int>> (n + 5);
    }

    void add(int u, int v, int w) {    // 添加一条无向边
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    void init(int x, int f, vector<int>& path, int deep, int dist) {    // 传入root, -1, {}, 1, 0
        depth[x] = deep;
        dis[x] = dist;
        for (int i = 1; i <= path.size(); i *= 2) {
            fa[x].push_back(path[path.size() - i]);
        }
        path.push_back(x);
        for (int i = 0; i < g[x].size(); i++) {
            int y = g[x][i][0], w = g[x][i][1];
            if (y == f) continue;
            init(y, x, path, deep + 1, dist + w);
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

    int get(int a, int b) { // 询问点 x 到点 y 的最短距离
        return dis[a] + dis[b] - 2 * dis[lca(a, b)];
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    TreePre S(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        S.add(u, v, w);
    }
    vector<int> t;
    S.init(1, -1, t, 1, 0);
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << S.get(a, b) << endl;
    }
    return 0;
}