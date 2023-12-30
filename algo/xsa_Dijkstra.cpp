#include <bits/stdc++.h>
using namespace std;
static constexpr long long mod = 1e9 + 7;
using LL = long long;
typedef pair<LL, LL> PLL;
class Solution {
   public:
    LL N;                   // N个点, 编号是0~N-1
    vector<LL> dis;         // 最短路径
    vector<LL> vis;         // visit数组
    vector<vector<PLL>> g;  // 建图, g[u]存(v, w)
    void dijkstra(LL start) {
        priority_queue<PLL, vector<PLL>, greater<PLL>> pq;  // 小顶堆
        pq.push(PLL(0, start));
        dis[start] = 0;
        while (pq.size()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            for (auto& [v, cost] : g[u]) {
                if (dis[v] > d + cost) {
                    dis[v] = d + cost;
                    pq.push(PLL(dis[v], v));
                }
            }
        }
    }
    void init(int n, vector<vector<int>>& roads) {  // Dijkstra
        // 初始化变量们, 并建图
        N = n;
        dis = vector<LL>(N, 1e18);
        vis = vector<LL>(N, 0);
        g = vector<vector<PLL>>(N);
        for (auto& r : roads) {
            int u = r[0], v = r[1], w = r[2];
            g[u].push_back(PLL(v, w));
            g[v].push_back(PLL(u, w));
        }
        // 计算所有点到start的距离
        dijkstra(0);
    }
};