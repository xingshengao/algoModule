#include <bits/stdc++.h>
using namespace std;

// 100160. 价值和小于等于 K 的最大数字

// 给你一个整数 k 和一个整数 x 。

// 令 s 为整数 num 的下标从 1 开始的二进制表示。我们说一个整数 num 的 价值 是满足 i % x == 0 且 s[i] 是 设置位 的 i 的数目。

// 请你返回 最大 整数 num ，满足从 1 到 num 的所有整数的 价值 和小于等于 k 。

// 一个整数二进制表示下 设置位 是值为 1 的数位。

// 一个整数的二进制表示下标从右到左编号，比方说如果 s == 11100 ，那么 s[4] == 1 且 s[2] == 0 。
using LL = long long;
class Solution {  // 二分 + 数位DP
   public:
    LL X;
    LL calc(LL n) {
        string s;
        while (n) {
            s.push_back(n % 2 + '0');
            n /= 2;
        }
        reverse(s.begin(), s.end());
        // 使用数位DP计算[1: n]中价值和
        int m = s.size();
        vector memo(m + 1, vector<LL>(m + 1, -1));
        function<LL(LL, LL, bool, bool)> dfs = [&](LL i, LL cnt1, bool is_limit, bool is_num) -> LL {
            if (i == m) {
                if (is_num) return cnt1;
                return 0;
            }
            if (!is_limit and is_num and memo[i][cnt1] != -1) return memo[i][cnt1];
            LL res = 0;
            if (!is_num) {
                res += dfs(i + 1, cnt1, false, false);
            }
            int up = is_limit ? s[i] - '0' : 1;
            int low = is_num ? 0 : 1;
            for (int d = low; d <= up; ++d) {
                res += dfs(i + 1, cnt1 + (d == 1 && (m - i) % X == 0), is_limit and d == up, true);
            }
            if (!is_limit and is_num) memo[i][cnt1] = res;
            return res;
        };
        return dfs(0, 0, true, false);
    }
    long long findMaximumNumber(long long k, int x) {
        X = x;
        LL lo = 1, hi = 1e15 + 1;
        // 二分求上界
        while (lo < hi) {
            LL mid = lo + (hi - lo + 1 >> 1);
            if (calc(mid) <= k)
                lo = mid;
            else
                hi = mid - 1;
        }
        return lo;
    }
};