#include <bits/stdc++.h>
using namespace std;
// 通过tarjan算法找到无向图中的强连通分量, 1211
struct Tarjan {
   public:
    int time;                 // 时间戳
    vector<vector<int>> adj;  // 邻接表
    vector<int> dfn;          // 节点的时间戳
    vector<int> low;          // 节点的追溯值
    vector<bool> vis;         // 是否遍历过节点
    int cnt;                  // 强连通分量的数量
    vector<vector<int>> ans;  // 存强连通分量
    void tarjan(int u, int fa) {
        time++;
        dfn[u] = time;
        low[u] = time;
        vis[u] = 1;

        for (int v : adj[u]) {
            if (v == fa) continue;
            if (!vis[v]) {
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                // 说明找到了一条强连通分量
                if (low[v] > dfn[u]) {
                    ans.push_back({u, v});
                    cnt += 1;
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
    // 初始化变量们并建图
    void init(int n, vector<vector<int>>& connections) {
        time = 0;
        adj = vector<vector<int>>(n);
        dfn = vector<int>(n, 0);
        low = vector<int>(n, 0);
        vis = vector<bool>(n, false);
        cnt = 0;
        // 建图
        for (auto& e : connections) {
            int x = e[0], y = e[1];
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
    }
    // 使用举例, 求出所有强连通分量
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        init(n, connections);
        tarjan(0, -1);
        return ans;
    }
};