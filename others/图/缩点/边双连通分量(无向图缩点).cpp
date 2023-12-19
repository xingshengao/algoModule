// https://www.luogu.com.cn/problem/P8436
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct eDcc {

    int n, m, stamp;
    vector<vector<pair<int, int>>> g;
    vector<int> dfn, low;
    vector<bool> bridge, vis;
    vector<vector<int>> dcc;    // 存储边双连通分量内的结点
    vector<int> id;     // id[i]表示结点i在编号为id[i]边双连通分量中
    vector<vector<int>> ng; // 缩点后的无向无环图

    eDcc(int n, int m) {    // 传入点数、边数
        this->n = n;
        this->m = m;
        stamp = 0;
        g = vector<vector<pair<int, int>>> (n + 5);
        ng = vector<vector<int>> (n + 5);
        id = vector<int> (n + 5);
        dfn = vector<int> (n + 5);
        low = vector<int> (n + 5);
        vis = vector<bool> (n + 5);
        bridge = vector<bool> (m + 5);
    }

    void add(int from, int to, int id) {    // 添加一条无向边
        g[from].push_back({to, id});
        g[to].push_back({from, id});
    }

    void tarjan(int from, int id) {
        dfn[from] = low[from] = ++stamp;
        for (int i = 0; i < g[from].size(); i++) {
            int to = g[from][i].first, eid = g[from][i].second;
            if (!dfn[to]) {
                tarjan(to, eid);
                low[from] = min(low[from], low[to]);
            } else if (id != eid) {
                low[from] = min(low[from], dfn[to]);
            }
        }
        if (dfn[from] == low[from] && id != -1) {
            bridge[id] = true;
        }
    }

    void dfs(int from) {
        vis[from] = true;
        dcc.back().push_back(from);
        for (int i = 0; i < g[from].size(); i++) {
            int to = g[from][i].first, id = g[from][i].second;
            if (!bridge[id] && !vis[to]) {
                dfs(to);
            }
        }
    }

    void geteDcc() {    // 获取所有边双连通分量
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                tarjan(i, -1);
            }
        }
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                dcc.push_back({});
                dfs(i);
            }
        }
        for (int i = 0; i < dcc.size(); i++) {
            for (int j = 0; j < dcc[i].size(); j++) {
                id[dcc[i][j]] = i;
            }
        }
        for (int i = 0; i < g.size(); i++) {
            for (int j = 0; j < g[i].size(); j++) {
                int k = g[i][j].first, eid = g[i][j].second;
                if (bridge[eid]) {
                    ng[id[i]].push_back(id[k]);
                }
            }
        }
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n, m;
    cin >> n >> m;
    eDcc D(n, m);
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        D.add(a, b, i);
    }
    D.geteDcc();
    cout << D.dcc.size() << endl;
    for (int i = 0; i < D.dcc.size(); i++) {
        cout << D.dcc[i].size() << ' ';
        for (int j : D.dcc[i]) {
            cout << j << ' ';
        }
        cout << endl;
    }
    return 0;
}
