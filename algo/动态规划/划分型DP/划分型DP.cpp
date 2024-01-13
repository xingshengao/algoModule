#include <bits/stdc++.h>

using namespace std;
using LL = long long;

// 813. 最大平均值和的分组

// 相关企业
// 给定数组 nums 和一个整数 k 。我们将给定的数组 nums 分成 最多 k 个非空子数组，且数组内部是连续的 。 分数 由每个子数组内的平均值的总和构成。

// 注意我们必须使用 nums 数组中的每一个数进行分组，并且分数不一定需要是整数。

// 返回我们所能得到的最大 分数 是多少。答案误差在 10-6 内被视为是正确的

// 记忆化搜索写法
class Solution_1 {
   public:
    double largestSumOfAverages(vector<int>& nums, int k) {
        int n = nums.size();
        vector<double> ps(n + 1, 0);
        for (int i = 0; i < n; ++i) ps[i + 1] = ps[i] + nums[i];
        vector<vector<double>> memo(n + 1, vector<double>(k + 1, -1));
        // dfs(i, j)代表把前i个数字分为j个组的结果
        function<double(int, int)> dfs = [&](int i, int j) -> double {
            if (j == 1) {  // [1:i], 即[0: i - 1]的区间和
                return (ps[i] - ps[0]) / i;
            }
            if (memo[i][j] != -1) return memo[i][j];
            // 枚举最后一段的左端点L, 最后一段为[L: i]
            double res = 0;
            // 最后一段是第j段,L至少是j
            for (int L = j; L <= i; ++L) {
                res = max(res, dfs(L - 1, j - 1) + (ps[i] - ps[L - 1]) / (i - L + 1));
            }
            return memo[i][j] = res;
        };
        return dfs(n, k);
    }
};
// 动态规划写法
class Solution_2 {  // 划分DP
   public:
    double largestSumOfAverages(vector<int>& nums, int k) {
        // 贪心的分成k个子数组
        // dp[i][j]代表把数组的前i个元素元素分成j组的最大平均值和
        int n = nums.size();
        vector<double> ps(n + 1);  // 前缀和数组
        for (int i = 0; i < n; ++i) {
            ps[i + 1] = ps[i] + nums[i];
        }
        vector<vector<double>> dp(n + 1, vector<double>(k + 1, 0));
        for (int i = 1; i <= n; ++i) {
            dp[i][1] = (ps[i] - ps[0]) / i;
        }
        // 划分型DP
        for (int j = 2; j <= k; ++j) {
            for (int i = j; i <= n; ++i) {  // 分成j组, i至少是第j个元素
                // 枚举最后一组的起点, 即枚举第j段的起点, 最后一段是[L : i]
                // 枚举范围是[j: i]
                for (int L = j; L <= i; L++) {
                    dp[i][j] = max(dp[i][j], dp[L - 1][j - 1] + (ps[i] - ps[L - 1]) / (i - L + 1));
                }
            }
        }
        return dp[n][k];
    }
};
