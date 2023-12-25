#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using LL = long long;
// 字典树
struct Node {
    Node* son[26]{};
    int sid = -1;  // 字符串的编号
};
class Solution {
   public:
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        Node* root = new Node();
        int sid = 0;  // 编号
        // 把每一个字符串转化成一个编号
        // 这一步兼具了去重的作用
        auto put = [&](string& s) -> int {
            Node* o = root;
            for (char b : s) {
                int i = b - 'a';
                if (o->son[i] == nullptr) {
                    o->son[i] = new Node();
                }
                o = o->son[i];
            }
            if (o->sid < 0) {
                o->sid = sid++;
            }
            return o->sid;
        };

        // 初始化距离矩阵
        int m = original.size();
        vector dis(m * 2, vector<LL>(m * 2, 1e18));
        for (int i = 0; i < m * 2; ++i) dis[i][i] = 0;
        for (int i = 0; i < m; ++i) {
            // 给字符串编号
            int x = put(original[i]);
            int y = put(changed[i]);
            dis[x][y] = min(dis[x][y], cost[i] * 1LL);
        }

        // Floyd求两点最短路
        for (int k = 0; k < sid; ++k) {
            for (int x = 0; x < sid; ++x) {
                if (dis[x][k] == 1e18) continue; // 加上这句话, 巨大优化
                for (int y = 0; y < sid; ++y) {
                    dis[x][y] = min(dis[x][y], dis[x][k] + dis[k][y]);
                }
            }
        }

        // 动态规划, dp[i]代表source从i开始向后修改的最小代价
        int n = source.size();
        vector<LL> dp(n + 1, -1);
        function<LL(int)> dfs = [&](int i) -> LL {
            if (i >= n) return 0;
            LL& res = dp[i];
            if (res != -1) return res;
            res = 1e18;
            if (source[i] == target[i]) {
                res = dfs(i + 1);  // 不修改source[i]
            }
            Node *p = root, *q = root;
            for (int j = i; j < n; ++j) {
                p = p->son[source[j] - 'a'];
                q = q->son[target[j] - 'a'];
                if (p == nullptr || q == nullptr) {
                    break;
                }
                if (p->sid < 0 || q->sid < 0) {
                    continue;
                }
                // 修改i到j的这一段
                LL d = dis[p->sid][q->sid];
                if (d < 1e18) {
                    res = min(res, dis[p->sid][q->sid] + dfs(j + 1));
                }
            }
            return res;
        };
        LL ans = dfs(0);
        return ans >= 1e18 ? -1 : ans;
    }
};