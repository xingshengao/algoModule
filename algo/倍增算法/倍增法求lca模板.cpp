#include <bits/stdc++.h>
using namespace std;

// 如何计算最近公共祖先
// DFS预处理出depth深度数组
// 假设depth[x] <= depth[y] 否则交换两点
// 先把考下的y更新为y的第depth[y] - depth[x]个祖先节点, 使得x和y在同一深度
// 如果x==y, 说明x就是lca, 否则说明lca在更上面, 就把x和y一起往上跳
// 不知道lca的具体位置, 只能不断尝试, 先尝试大步跳, 再尝试小步跳。设 i=[log2(n)]循环直到 i<0。每次循环：
    // 如果x的第2^i个祖先节点不存在, 即 pa[x][i]=−1说明步子迈大了, i--, 继续循环。
    // 如果x的第2^i个祖先节点存在, 且 pa[x][i]≠pa[y][i]说明 lca在pa[x][i]的上面,
    // 那么更新x为 pa[x][i], 更新y为 pa[y][i]将i--继续循环。否则, 若 pa[x][i]=pa[y][i],
    // lca可能在 pa[x][i] 下面, 由于无法向下跳, 只能将i--继续循环
// 上述做法能跳就尽量跳, 不会错过任何可以上跳的机会。所以循环结束时, x与lca只有一步之遥, 即 lca=pa[x][0]

class TreeAncestor {
    vector<int> depth;
    vector<vector<int>> pa;

   public:
    TreeAncestor(vector<pair<int, int>>& edges) {
        int n = edges.size() + 1;
        int m = 32 - __builtin_clz(n);  // n 的二进制长度
        vector<vector<int>> g(n);
        for (auto [x, y] : edges) {  // 节点编号从 0 开始
            g[x].push_back(y);
            g[y].push_back(x);
        }

        // 预处理求depth数组
        depth.resize(n, 0);
        pa.resize(n, vector<int>(m, -1));
        function<void(int, int)> dfs = [&](int x, int fa) {
            pa[x][0] = fa;
            for (int y : g[x]) {
                if (y != fa) {
                    depth[y] = depth[x] + 1;
                    dfs(y, x);
                }
            }
        };
        dfs(0, -1);

        // 倍增模板
        for (int i = 0; i < m - 1; i++) {
            for (int x = 0; x < n; x++) {
                if (int p = pa[x][i]; p != -1) pa[x][i + 1] = pa[p][i];
            }
        }
    }

    // 得到node的第k个祖先节点
    int get_kth_ancestor(int node, int k) {
        for (; k; k &= k - 1) node = pa[node][__builtin_ctz(k)];
        return node;
    }

    // 返回 x 和 y 的最近公共祖先（节点编号从 0 开始）
    int get_lca(int x, int y) {
        if (depth[x] > depth[y]) swap(x, y);
        // 使 y 和 x 在同一深度
        y = get_kth_ancestor(y, depth[y] - depth[x]);
        if (y == x) return x;
        for (int i = pa[x].size() - 1; i >= 0; i--) {
            int px = pa[x][i], py = pa[y][i];
            if (px != py) {
                x = px;
                y = py;
            }
        }
        return pa[x][0];
    }
};
