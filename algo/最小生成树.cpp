#include <bits/stdc++.h>
using namespace std;
/**
 * 最小生成树, Kruskal算法, 加边法
 * 把所有边按照代价排序, 然后按照并查集连通性加边, 直至并查集的连通块只有1个
 */
class Solution {
   public:
    vector<int> fa;
    int part;
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        part -= 1;
        fa[y] = x;
        return true;
    }
    int find(int x) {
        while (x != fa[x]) {
            x = fa[x] = fa[fa[x]];
        }
        return x;
    }
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        if (n <= 1) return 0;
        fa = vector<int>(n);
        iota(fa.begin(), fa.end(), 0);
        part = n;
        typedef tuple<int, int, int> TIII;  // 元组存储边的代价, 边的顶点编号
        vector<TIII> vec;                   // 存边
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];
                int cost = abs(x1 - x2) + abs(y1 - y2);
                vec.push_back(TIII(cost, i, j));
            }
        }
        sort(vec.begin(), vec.end());  // 按照代价升序排序
        int ans = 0;
        for (auto& [cost, u, v] : vec) {
            int fau = find(u);
            int fav = find(v);
            if (fav != fau) {
                merge(u, v);
                ans += cost;
            }
            if (part == 1) {
                return ans;
            }
        }
        return -1;
    }
};

/**
 * 最小生成树, Prim算法, 加点法
 * 每次迭代选择代价最小的边对应的点，加入到最小生成树中。
 * 算法从某一个顶点s开始，逐渐长大覆盖整个连通网的所有顶点。
 * 图的所有顶点为V, 初始时令集合u = s, v = V - s
 * 在两个集合能组成的边中, 选择一条代价最小的边(u0, v0)加入到最小生成树中, 并把v0加入到集合u
 * 直到最小生成树有n - 1条边或者n个顶点为止
 */
class _Solution {
   public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        if (n <= 1) return 0;
        typedef pair<int, int> PII;
        vector<vector<PII>> g(n);  // 建图, 存的是代价和下一个节点
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];
                int cost = abs(x1 - x2) + abs(y1 - y2);
                g[i].push_back(PII(cost, j));
                g[j].push_back(PII(cost, i));
            }
        }
        vector<bool> vis(n, false);
        typedef pair<int, int> PII;
        priority_queue<PII, vector<PII>, greater<PII>> q;
        // 选一个起点, 把从他的出边选最小的边
        vis[0] = 1;
        for (auto& e : g[0]) {
            q.push(e);
        }
        int ans = 0, edge_cnt = 0;
        while (q.size()) {
            // 选出当前代价最小的边
            auto [cost, u] = q.top();
            q.pop();
            if (vis[u]) {
                continue;
            }
            vis[u] = 1;
            ans += cost;
            edge_cnt += 1;
            if (edge_cnt == n - 1) {
                return ans;
            }
            for (auto v : g[u]) {
                q.push(v);
            }
        }
        return -1;
    };
};