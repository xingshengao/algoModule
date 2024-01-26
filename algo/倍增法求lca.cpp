#include <bits/stdc++.h>
using namespace std;

// 2846. 边权重均等查询

// 现有一棵由 n 个节点组成的无向树，节点按从 0 到 n - 1 编号。给你一个整数 n 和一个长度为 n - 1 的二维整数数组 edges ，其中 edges[i] = [ui, vi,
// wi] 表示树中存在一条位于节点 ui 和节点 vi 之间、权重为 wi 的边。

// 另给你一个长度为 m 的二维整数数组 queries ，其中 queries[i] = [ai, bi] 。对于每条查询，请你找出使从 ai 到 bi 路径上每条边的权重相等所需的
// 最小操作次数 。在一次操作中，你可以选择树上的任意一条边，并将其权重更改为任意值。

// 注意：

// 查询之间 相互独立 的，这意味着每条新的查询时，树都会回到 初始状态 。
// 从 ai 到 bi的路径是一个由 不同 节点组成的序列，从节点 ai 开始，到节点 bi 结束，且序列中相邻的两个节点在树中共享一条边。
// 返回一个长度为 m 的数组 answer ，其中 answer[i] 是第 i 条查询的答案
class Solution {
   public:
    vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        // 建图
        vector<vector<pair<int, int>>> g(n);
        for (auto& e : edges) {
            int x = e[0], y = e[1], w = e[2] - 1;
            g[x].emplace_back(y, w);
            g[y].emplace_back(x, w);
        }
        int m = 32 - __builtin_clz(n);                  // n 的二进制长度
        vector<vector<int>> pa(n, vector<int>(m, -1));  // pa[x][i]代表x的第2^i个父节点
        // 因为权值很有限, 可以在倍增的同时, 维护从x到x的2^i个祖先节点上每一种边权的个数
        vector cnt(n, vector<vector<int>>(m, vector<int>(26, 0)));

        // 路径长度可以用深度数组depth计算出
        vector<int> depth(n, 0);
        function<void(int, int)> dfs = [&](int x, int fa) {
            pa[x][0] = fa;
            for (auto& [y, w] : g[x]) {
                if (y == fa) continue;
                cnt[y][0][w] = 1;
                depth[y] = depth[x] + 1;
                dfs(y, x);
            }
        };
        dfs(0, -1);

        // 倍增模板
        for (int i = 0; i < m - 1; ++i) {
            for (int x = 0; x < n; ++x) {
                int p = pa[x][i];
                if (p != -1) {
                    pa[x][i + 1] = pa[p][i];
                    for (int k = 0; k < 26; ++k) {
                        cnt[x][i + 1][k] = cnt[x][i][k] + cnt[p][i][k];
                    }
                }
            }
        }

        // 计算lca并求答案
        vector<int> ans;
        for (auto& q : queries) {
            int x = q[0], y = q[1];
            int path_len = depth[x] + depth[y];  // 两个点的深度, 最后减去2*depth[lca]
            vector<int> cw(26, 0);
            if (depth[x] > depth[y]) swap(x, y);

            // 让x和y在同一深度
            for (int k = depth[y] - depth[x]; k; k &= k - 1) {
                int i = __builtin_ctz(k);
                int p = pa[y][i];
                for (int j = 0; j < 26; ++j) {
                    cw[j] += cnt[y][i][j];
                }
                y = p;
            }

            // 使用倍增法求lca
            if (y != x) {
                for (int i = m - 1; i >= 0; i--) {
                    int px = pa[x][i], py = pa[y][i];
                    if (px != py) {
                        for (int j = 0; j < 26; j++) {
                            cw[j] += cnt[x][i][j] + cnt[y][i][j];
                        }
                        x = px;
                        y = py;  // x 和 y 同时上跳 2^i 步
                    }
                }
                for (int j = 0; j < 26; j++) {
                    cw[j] += cnt[x][0][j] + cnt[y][0][j];
                }
                x = pa[x][0];
            }

            int lca = x;
            path_len -= 2 * depth[lca];
            ans.push_back(path_len - *max_element(cw.begin(), cw.end()));
        }
        return ans;
    }
};