#include <bits/stdc++.h>
using namespace std;
/**
 * 树上倍增算法: 预处理每个节点的第2^i个祖先节点, 任意k可分解为不同的二进制次幂, 快速到达第k个祖先节点
 * 在构造函数中, 初始化每个节点x的第2^i个祖先节点, 记作pa[x][i], 若第2^i个祖先节点不存在则pa[x][i]=-1
 * pa[x][i] = pa[pa[x][i]][i], 表示x的第2^i个祖先节点的第2^i祖先节点, 就是x的第2^(i+1)个祖先节点
 */
class TreeAncestor {
   public:
    vector<vector<int>> pa;
    TreeAncestor(int n, vector<int>& parent) { init(n, parent); }
    // 初始化倍增数组, n个节点, (0~n-1), fa[i]是i的父节点
    void init(int n, vector<int>& fa) {
        int m = 32 - __builtin_clz(n);  // n的二进制长度
        pa = vector<vector<int>>(n, vector<int>(m, -1));
        for (int x = 0; x < n; ++x) pa[x][0] = fa[x];
        // 先枚举i再枚举x相当于先算出所有的爷爷节点, 再算出所有的爷爷的爷爷节点
        for (int i = 0; i < m - 1; ++i) {
            for (int x = 0; x < n; ++x) {
                if (pa[x][i] != -1) {
                    pa[x][i + 1] = pa[pa[x][i]][i];
                }
            }
        }
    }
    int getKthAncestor(int node, int k) {
        int m = 32 - __builtin_clz(k);  // k的二进制长度
        for (int i = 0; i < m; ++i) {
            if ((k >> i) & 1) {
                node = pa[node][i];
                if (node < 0) break;
            }
        }
        return node;
    }
    // 另一种写法，不断去掉 k 的最低位的 1
    int getKthAncestor2(int node, int k) {
        for (; k && node != -1; k &= k - 1) // 也可以写成 ~node
            node = pa[node][__builtin_ctz(k)];
        return node;
    }
};