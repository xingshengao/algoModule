#include <bits/stdc++.h>
using namespace std;
static constexpr long long mod = 1e9 + 7;
using LL = long long;

class Solution {
   public:
    int sumOfPower(vector<int>& nums, int k) {
        LL n = nums.size();
        // 二维01背包dp[i][j]代表恰好装满容量为i的背包且正好使用j个物品的方案数量
        vector<vector<LL>> dp(k + 1, vector<LL>(n + 1));
        dp[0][0] = 1;
        for (int i = 0; i < n; ++i) {              // 遍历物品
            for (int j = k; j >= nums[i]; --j) {   // 逆序遍历容量
                for (int c = i + 1; c > 0; --c) {  // 逆序遍历个数
                    dp[j][c] += dp[j - nums[i]][c - 1];
                    dp[j][c] %= mod;
                }
            }
        }
    }
};