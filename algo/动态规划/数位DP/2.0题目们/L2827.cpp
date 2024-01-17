#include <bits/stdc++.h>
using namespace std;
// 2827. 范围中美丽整数的数目

// 给你正整数 low ，high 和 k 。

// 如果一个数满足以下两个条件，那么它是 美丽的 ：

// 偶数数位的数目与奇数数位的数目相同。
// 这个整数可以被 k 整除。
// 请你返回范围 [low, high] 中美丽整数的数目。

using LL = long long;
static constexpr long long mod = 1e9 + 7;
class Solution {  // 数位DP2.0模板
   public:
    int numberOfBeautifulIntegers(int Low, int High, int K) {
        string high = to_string(High);
        string low = to_string(Low);
        // 添加前导0
        if (low.size() < high.size()) {
            low = string(high.size() - low.size(), '0') + low;
        }
        int m = high.size();
        LL memo[12][12][12][21];
        memset(memo, -1, sizeof(memo));
        function<LL(LL, LL, LL, LL, bool, bool, bool)> dfs = [&](LL i, LL a, LL b, LL v, bool limit_low, bool limit_high, bool is_num) -> LL {
            if (i == m) {
                return int(is_num and a == b and v == 0);
            }
            if (!limit_high and !limit_low and is_num and memo[i][a][b][v] != -1) return memo[i][a][b][v];
            LL res = 0;
            if (!is_num and low[i] == '0') {
                res += dfs(i + 1, a, b, v, true, false, false);
                res %= mod;
            }

            //  i 个数位可以从哪枚举到哪
            // 如果对数位有其它约束，应当只在下面的 for 循环做限制
            int hi = limit_high ? high[i] - '0' : 9;
            int lo = limit_low ? low[i] - '0' : 0;

            // 若有对其它数位的限制, 写在枚举d这边
            int d0 = is_num ? 0 : 1;
            for (int d = max(lo, d0); d <= hi; ++d) {
                res += dfs(i + 1, a + (d % 2 == 1), b + (d % 2 == 0), (v * 10 + d) % K, limit_low and d == lo, limit_high and d == hi, true);
                res %= mod;
            }
            if (!limit_high and !limit_low and is_num) return memo[i][a][b][v] = res;
            return res;
        };
        return dfs(0, 0, 0, 0, true, true, false);
    }
};