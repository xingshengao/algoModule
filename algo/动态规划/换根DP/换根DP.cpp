#include <bits/stdc++.h>

using namespace std;
using LL = long long;
// 力扣834 树中距离之和https://leetcode.cn/problems/sum-of-distances-in-tree/description/
// 给定一个无向、连通的树。树中有 n 个标记为 0...n-1 的节点以及 n-1 条边 。

// 给定整数 n 和数组 edges ， edges[i] = [ai, bi]表示树中的节点 ai 和 bi 之间有一条边。

// 返回长度为 n 的数组 answer ，其中 answer[i] 是树中第 i 个节点与所有其他节点之间的距离之和
class Solution1 {
   public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        vector<int> ans(n, 0);
        // 先计算ans[0]
        function<void(int, int, int)> dfs = [&](int x, int fa, int depth) -> void {
            ans[0] += depth;
            for (int y : g[x]) {
                if (y != fa) {
                    dfs(y, x, depth + 1);
                }
            }
        };
        dfs(0, -1, 0);

        // 计算每个点的子树大小
        vector<int> size(n, 1);
        function<void(int, int)> dfs1 = [&](int x, int fa) -> void {
            for (int y : g[x]) {
                if (y != fa) {
                    dfs1(y, x);
                    size[x] += size[y];
                }
            }
        };
        dfs1(0, -1);

        // 换根DP, 考虑换根时的距离变化
        // 从x换根到y, y的子树的距离全部减一, 不在y的子树的点的距离全部加一
        // ans[y] = ans[x] - size[y] + (n - size[y]) = ans[x] + n - 2 * size[y]
        function<void(int, int)> re_root = [&](int x, int fa) {
            for (int y : g[x]) {
                if (y != fa) {
                    ans[y] = ans[x] + n - 2 * size[y];
                    re_root(y, x);
                }
            }
        };
        re_root(0, -1);
        return ans;
    }
};

// 力扣2825可以到达每一个节点的最少边反转次数https://leetcode.cn/problems/minimum-edge-reversals-so-every-node-is-reachable/description/?envType=list&envId=82brfHyb
// s给你一个 n 个点的 简单有向图 （没有重复边的有向图），节点编号为 0 到 n - 1 。如果这些边是双向边，那么这个图形成一棵 树 。
// 给你一个整数 n 和一个 二维 整数数组 edges ，其中 edges[i] = [ui, vi] 表示从节点 ui 到节点 vi 有一条 有向边 。
// 边反转 指的是将一条边的方向反转，也就是说一条从节点 ui 到节点 vi 的边会变为一条从节点 vi 到节点 ui 的边。
// 对于范围 [0, n - 1] 中的每一个节点 i ，你的任务是分别 独立 计算 最少 需要多少次 边反转 ，从节点 i 出发经过 一系列有向边 ，可以到达所有的节点。
// 请你返回一个长度为 n 的整数数组 answer ，其中 answer[i]表示从节点 i 出发，可以到达所有节点的 最少边反转 次数

class Solution2 {
   public:
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {
        typedef pair<int, int> PII;
        vector<vector<PII>> g(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(PII(v, 1));
            g[v].push_back(PII(u, -1));
        }
        vector<int> ans(n, 0);  // 每个点的答案
        // 计算节点0的答案
        function<void(int, int)> dfs = [&](int x, int fa) {
            for (auto [y, dir] : g[x]) {
                if (y == fa) continue;
                if (dir == -1) ans[0] += 1;
                dfs(y, x);
            }
        };
        dfs(0, -1);
        // 换根DP
        function<void(int, int)> re_root = [&](int x, int fa) {
            for (auto [y, dir] : g[x]) {
                if (y == fa) continue;
                ans[y] = ans[x] + dir;
                re_root(y, x);
            }
        };
        re_root(0, -1);
        return ans;
    }
};