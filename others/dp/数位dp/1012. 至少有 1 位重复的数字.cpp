// https://leetcode.cn/problems/numbers-with-repeated-digits/comments/
class Solution {
public:

    int dp[10][1 << 10][2][2];

    int dfs(int pos, int mask, bool limit, bool full, string& s) {
        if (dp[pos][mask][limit][full] != -1) return dp[pos][mask][limit][full];
        if (pos == s.size()) return full;
        int res = 0;
        if (!full) res += dfs(pos + 1, mask, false, false, s);
        int now = s[pos] - '0';
        int down = full ? 0 : 1;
        int up = limit ? now : 9;
        for (int i = down; i <= up; i++) {
            if ((mask & (1 << i)) == 0) {
                res += dfs(pos + 1, mask | (1 << i), limit && (i == now), true, s);
            }
        }
        return dp[pos][mask][limit][full] = res;
    }

    int numDupDigitsAtMostN(int n) {
        string s = to_string(n);
        memset(dp, -1, sizeof dp);
        return n - dfs(0, 0, true, false, s);
    }
};