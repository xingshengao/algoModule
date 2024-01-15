#include <bits/stdc++.h>
using namespace std;

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
    int Min_sum, Max_sum;
    LL calc(string s) {
        LL m = s.size();
        vector memo(25, vector<LL>(450, -1));
        function<LL(LL, LL, bool, bool)> dfs = [&](LL i, LL cnt, bool is_limit, bool is_num) -> LL {
            if (i == m) return cnt >= Min_sum and cnt <= Max_sum;
            if (!is_limit and is_num and memo[i][cnt] != -1) return memo[i][cnt];
            LL res = 0;
            if (!is_num) {
                res += dfs(i + 1, cnt, false, false);
                res %= mod;
            }
            int up = is_limit ? s[i] - '0' : 9;
            int low = is_num ? 0 : 1;
            for (int d = low; d <= up; ++d) {
                res += dfs(i + 1, cnt + d, is_limit and d == up, true);
                res %= mod;
            }
            if (!is_limit and is_num) memo[i][cnt] = res;
            return res;
        };
        return dfs(0, 0, true, false);
    }
    bool check(string s) {
        int cnt = 0;
        for (char c : s) cnt += c - '0';
        return cnt >= Min_sum and cnt <= Max_sum;
    }
    int count(string num1, string num2, int min_sum, int max_sum) {
        Max_sum = max_sum;
        Min_sum = min_sum;
        LL ans = calc(num2) - calc(num1) + check(num1);
        return (ans % mod + mod) % mod;
    }
};