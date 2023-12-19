// https://loj.ac/p/10102
#include <bits/stdc++.h>

using namespace std;

struct Bridge {

    int cnt, n;
    vector<pair<int, int>> bridges;
    vector<vector<int>> edges;
    vector<int> dfsn, low, fa;

    Bridge() {}
    Bridge(int n) {
        cnt = 0;
        this->n = n;
        edges.resize(n + 5);
        dfsn.resize(n + 5);
        low.resize(n + 5);
        fa.resize(n + 5);
    }

    void add(int a, int b) {    // 添加一条无向边
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    void tarjan(int p) {
        low[p] = dfsn[p] = ++cnt;
        for (auto to : edges[p]) {
            if (!dfsn[to]) {
                fa[to] = p;     // 记录父节点
                tarjan(to);
                low[p] = min(low[p], low[to]);
                if (low[to] > dfsn[p])
                    bridges.emplace_back(p, to);
            } else if (fa[p] != to) {// 排除父节点
                low[p] = min(low[p], dfsn[to]);
            }
        }
    }

    vector<pair<int, int>> GetBridge() {    // 返回所有桥
        for (int i = 0; i <= n; i++) {
            if (dfsn[i] == 0) {
                tarjan(i);
            }
        }
        return bridges;
    }
};  

signed main() {
    int n, m;
    while (cin >> n >> m && n != 0 && m != 0) {
        Bridge B(n);
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            B.add(a, b);
        }
        cout << B.GetBridge().size() << endl;
    }

}