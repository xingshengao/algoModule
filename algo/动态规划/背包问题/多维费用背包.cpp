#include <bits/stdc++.h>
using namespace std;
static constexpr long long mod = 1e9 + 7;
using LL = long long;
// 879. 盈利计划
// 集团里有 n 名员工，他们可以完成各种各样的工作创造利润。

// 第 i 种工作会产生 profit[i] 的利润，它要求 group[i] 名成员共同参与。如果成员参与了其中一项工作，就不能参与另一项工作。

// 工作的任何至少产生 minProfit 利润的子集称为 盈利计划 。并且工作的成员总数最多为 n 。

// 有多少种计划可以选择？因为答案很大，所以 返回结果模 10^9 + 7 的值

class Solution1 {
   public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        int m = profit.size();  // 工作数量
        // 特殊的多维背包问题, 人数看作成本, 利润看作价值
        LL dp[110][110][110];  // dp[i][j][k]代表前i个物品, 使用容量不超过j, 利润至少为k的方案数
        memset(dp, 0, sizeof(dp));

        for (int i = 0; i < 110; ++i) dp[0][i][0] = 1;

        for (int i = 1; i <= m; ++i) {                // 遍历物品
            int w = group[i - 1], v = profit[i - 1];  // 体积, 价值
            for (int j = 0; j <= n; ++j) {            // 遍历容量
                for (int k = 0; k <= minProfit; ++k) {
                    dp[i][j][k] = dp[i - 1][j][k];  // 不选第i个物品
                    if (j >= w) {                   // 背包容积大于物品体积
                        dp[i][j][k] += dp[i - 1][j - w][max(0, k - v)];
                        dp[i][j][k] %= mod;
                    }
                }
            }
        }
        return dp[m][n][minProfit];
    }
};