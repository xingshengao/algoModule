#include <bits/stdc++.h>
using namespace std;

static constexpr long long mod = 1e9 + 7;
using LL = long long;

// 2719. 统计整数数目
// 给你两个数字字符串 num1 和 num2 ，以及两个整数 max_sum 和 min_sum 。如果一个整数 x 满足以下条件，我们称它是一个好整数：

// num1 <= x <= num2
// min_sum <= digit_sum(x) <= max_sum.
// 请你返回好整数的数目。答案可能很大，请返回答案对 109 + 7 取余后的结果。

// 注意，digit_sum(x) 表示 x 各位数字之和。
static constexpr long long mod = 1e9 + 7;
using LL = long long;
class Solution {
   public:
    int count(string num1, string num2, int min_sum, int max_sum) {
        string low = num1;
        string high = num2;
        if (high.size() > low.size()) {
            low = string(high.size() - low.size(), '0') + low;
        }
        int m = high.size();
        LL memo[25][450];
        memset(memo, -1, sizeof(memo));
        function<LL(LL, LL, bool, bool, bool)> dfs = [&](LL i, LL cnt, bool limit_low, bool limit_high, bool is_num) -> LL {
            if (i == m) {
                if (is_num) {
                    return cnt >= min_sum and cnt <= max_sum;
                } else {
                    return 0;
                }
            }
            if (!limit_high and !limit_low and is_num and memo[i][cnt] != -1) {
                return memo[i][cnt];
            }
            LL res = 0;

            // 前面的都填0, 这一位也可以填0, 且limit_low
            if (!is_num and low[i] == '0') {
                res += dfs(i + 1, cnt, true, false, false);
                res %= mod;
            }

            //  i 个数位可以从哪枚举到哪
            // 如果对数位有其它约束，应当只在下面的 for 循环做限制
            int hi = limit_high ? high[i] - '0' : 9;
            int lo = limit_low ? low[i] - '0' : 0;

            // 若有对其它数位的限制, 写在枚举d这边
            int d0 = is_num ? 0 : 1;
            for (int d = max(lo, d0); d <= hi; ++d) {
                res += dfs(i + 1, cnt + d, limit_low and d == lo, limit_high and d == hi, true);
                res %= mod;
            }
            if (!limit_high and !limit_low and is_num) {
                memo[i][cnt] = res;
            }
            return res;
        };

        LL ans = dfs(0, 0, true, true, false);
        return (ans % mod + mod) % mod;
    }
};