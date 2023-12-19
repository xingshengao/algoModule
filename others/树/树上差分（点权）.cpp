// https://www.luogu.com.cn/problem/P3128
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

// 点权公式: dis(x)+dis(y)-2*dis(LCA)+w[LCA]
// 边权公式: dis(x)+dis(y)-2*dis(LCA)
// 点权差分公式： dis(x)++, dis(y)++, dis(LCA(x, y))--, dis(fa[LCA(x, y)])--

struct TreePre {
    vector<int> depth, dis;
    vector<vector<int>> fa, g;

    TreePre() {}
    TreePre(int n) {    // 构造函数,传入点数
        depth = vector<int> (n + 5, 1e9);
        dis = vector<int> (n + 5);
        g = vector<vector<int>> (n + 5);
        fa = vector<vector<int>> (n + 5);
    }

    void add(int u, int v) {    // 添加一条无向边
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void init1(int x, int f, vector<int>& path, int deep) {    // 传入root, -1, {}, 1
        depth[x] = deep;
        for (int i = 1; i <= path.size(); i *= 2) {
            fa[x].push_back(path[path.size() - i]);
        }
        path.push_back(x);
        for (int i = 0; i < g[x].size(); i++) {
            int y = g[x][i];
            if (y == f) continue;
            init1(y, x, path, deep + 1);
        }
        path.pop_back();
    }

    int init2(int x, int f) {    // 传入root, -1
        for (int i = 0; i < g[x].size(); i++) {
            int y = g[x][i];
            if (y == f) continue;
            dis[x] += init2(y, x);
        }
        return dis[x];
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

};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    TreePre S(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        S.add(u, v);
    }
    vector<int> t;
    S.init1(1, -1, t, 1);
    while (q--) {
        int a, b;
        cin >> a >> b;
        int lca = S.lca(a, b);
        // 差分
        S.dis[a]++, S.dis[b]++, S.dis[lca]--;    
        if (S.fa[lca].size()) {
            S.dis[S.fa[lca][0]]--;
        }
    }
    S.init2(1, -1);
    int res = 0;
    for (int i = 1; i <= n; i++) {
        res = max(res, S.dis[i]);
    }
    cout << res << endl;
    return 0;
}