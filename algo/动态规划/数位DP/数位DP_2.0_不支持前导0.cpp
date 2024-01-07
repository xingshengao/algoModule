#include <bits/stdc++.h>

using namespace std;
using LL = long long;
// 数位DP_2.0_不支持前导0


// 给你三个整数 start ，finish 和 limit 。同时给你一个下标从 0 开始的字符串 s ，表示一个 正整数。
// 如果一个 正 整数 x 末尾部分是 s （换句话说，s 是 x 的 后缀），且 x 中的每个数位至多是 limit ，那么我们称 x 是 强大的 。
// 请你返回区间 [start..finish] 内强大整数的 总数目 。

// 如果一个字符串 x 是 y 中某个下标开始（包括 0 ），到下标为 y.length - 1 结束的子字符串，那么我们称 x 是 y 的一个后缀。
// 比方说，25 是 5125 的一个后缀，但不是 512 的后缀
using LL = long long;
class Solution {
   public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        string low = to_string(start);
        string high = to_string(finish);
        int n = high.size();
        if ((int)low.size() < n) {
            low = string(n - (int)low.size(), '0') + low;
        }

        int diff = n - s.size();

        LL memo[20][2][2];
        memset(memo, -1, sizeof(memo));
        function<LL(LL, bool, bool)> dfs = [&](LL i, bool limit_low, bool limit_high) -> LL {
            if (i == n) {
                return 1;
            }
            LL& res = memo[i][limit_low][limit_high];
            if (res != -1) return res;
            res = 0;

            //  i 个数位可以从哪枚举到哪
            // 如果对数位有其它约束，应当只在下面的 for 循环做限制
            int hi = limit_high ? high[i] - '0' : 9;
            int lo = limit_low ? low[i] - '0' : 0;

            // 对其它数位的限制, 写在枚举d这边
            if (i < diff) {
                for (int d = lo; d <= min(hi, limit); ++d) {
                    res += dfs(i + 1, limit_low and d == lo, limit_high and d == hi);
                }
            } else {
                // 必须填s[i-diff] - '0'
                int x = s[i - diff] - '0';
                if (lo <= x and x <= min(hi, limit)) {
                    res = dfs(i + 1, limit_low and x == lo, limit_high and x == hi);
                }
            }
            return res;
        };

        return dfs(0, true, true);
    }
};