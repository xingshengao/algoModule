#include <bits/stdc++.h>

using namespace std;
using LL = long long;
// 力扣2827. 范围中美丽整数的数目
// 给你正整数 low ，high 和 k 。
// 如果一个数满足以下两个条件，那么它是 美丽的
// 偶数数位的数目与奇数数位的数目相同。
// 这个整数可以被 k 整除。
// 请你返回范围 [low, high] 中美丽整数的数目。
class Solution1 {
   public:
    LL K;
    // 计算<=n的美丽整数
    LL calc(LL n) {
        string s = to_string(n);
        LL m = s.size();
        LL memo[11][11][11][23];
        memset(memo, -1, sizeof(memo));
        // ab代表奇数数位和偶数数位, m代表模k的余数
        function<LL(LL, LL, LL, LL, bool, bool)> dfs = [&](LL i, LL a, LL b, LL v, bool is_limit, bool is_num) -> LL {
            if (i == m) {
                return is_num and a == b and v == 0;
            }
            if (not is_limit and is_num and memo[i][a][b][v] != -1) return memo[i][a][b][v];
            LL res = 0;
            // 可以跳过当前数位
            if (not is_num) {
                res += dfs(i + 1, a, b, v, false, false);
            }
            int high = is_limit ? s[i] - '0' : 9;
            int low = is_num ? 0 : 1;
            // 枚举这一位选什么
            for (int d = low; d <= high; ++d) {
                res += dfs(i + 1, a + (d % 2 == 1), b + (d % 2 == 0), (v * 10 + d) % K, is_limit and d == high, true);
            }
            if (not is_limit and is_num) memo[i][a][b][v] = res;
            return res;
        };
        return dfs(0, 0, 0, 0, true, false);
    }
    LL check(LL n) {
        if (n % K != 0) return false;
        int a = 0, b = 0;
        string s = to_string(n);
        for (int i = 0; i < s.size(); ++i) {
            int d = s[i] - '0';
            if (d & 1)
                a += 1;
            else
                b++;
        }
        return a == b;
    }
    int numberOfBeautifulIntegers(int low, int high, int k) {
        K = k;
        return calc(high) - calc(low) + check(low);
    }
};

// 力扣2801. 统计范围内的步进数字数目

// 给你两个正整数 low 和 high ，都用字符串表示，请你统计闭区间 [low, high] 内的 步进数字 数目。

// 如果一个整数相邻数位之间差的绝对值都 恰好 是 1 ，那么这个数字被称为 步进数字 。

// 请你返回一个整数，表示闭区间 [low, high] 之间步进数字的数目。

// 由于答案可能很大，请你将它对 109 + 7 取余 后返回。

// 注意：步进数字不能有前导 0
class Solution2 {
   public:
    const int MOD = 1e9 + 7;
    // 计算[0, s]有多少步进数字
    int calc(string& s) {
        // 数位DP的记忆化搜索
        int m = s.size();
        int memo[m][10];
        memset(memo, -1, sizeof(memo));
        function<int(int, int, bool, bool)> f = [&](int i, int pre, bool is_limit, bool is_num) -> int {
            if (i == m) return is_num;
            if (!is_limit && is_num && memo[i][pre] != -1) return memo[i][pre];
            int res = 0;
            if (!is_num) {  // 前面没有填数字, 可以跳过当前这一位
                res = (res + f(i + 1, pre, false, false)) % MOD;
            }
            int up = is_limit ? s[i] - '0' : 9;
            int low = is_num ? 0 : 1;
            for (int d = low; d <= up; ++d) {
                if (!is_num || abs(d - pre) == 1) {
                    // 第一位可以随便填, 其余位绝对值之差必须是1
                    res = (res + f(i + 1, d, is_limit && d == up, true)) % MOD;
                }
            }
            if (!is_limit && is_num) {  // 不受n限制并且前面填了数字的情况下, 记录结果
                memo[i][pre] = res;
            }
            return res;
        };
        return f(0, 0, true, false);
    }
    bool valid(string& s) {
        for (int i = 0; i < s.size() - 1; ++i) {
            if (abs(s[i + 1] - '0' - s[i] + '0') != 1) return false;
        }
        return true;
    }
    int countSteppingNumbers(string low, string high) {
        return (calc(high) - calc(low) + valid(low) + MOD) % MOD;  // 加上MOD防止算出负数
    }
};

// 力扣2376. 统计特殊整数

// 如果一个正整数每一个数位都是 互不相同 的，我们称它是 特殊整数 。

// 给你一个 正 整数 n ，请你返回区间 [1, n] 之间特殊整数的数目

class Solution3 {
   public:
    int countSpecialNumbers(int n) {
        string s = to_string(n);
        int m = s.size();
        LL memo[11][1 << 10];
        memset(memo, -1, sizeof memo);
        // mask代表选了哪些数字, 状压
        function<LL(LL, LL, bool, bool)> dfs = [&](int i, int mask, bool is_limit, bool is_num) -> LL {
            if (i == m) return is_num;
            if (not is_limit and is_num and memo[i][mask] != -1) return memo[i][mask];
            LL res = 0;
            // 可以跳过当前数位
            if (not is_num) res += dfs(i + 1, mask, false, false);
            LL hi = is_limit ? s[i] - '0' : 9;
            int lo = is_num ? 0 : 1;
            for (LL d = lo; d <= hi; ++d) {
                // 之前没选过d
                if (((mask >> d) & 1) == 0) {
                    res += dfs(i + 1, mask | (1 << d), is_limit and d == hi, true);
                }
            }
            if (not is_limit and is_num) memo[i][mask] = res;
            return res;
        };
        return dfs(0, 0, true, false);
    }
};