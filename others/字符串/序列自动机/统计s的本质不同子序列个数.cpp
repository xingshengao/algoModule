class Solution {
    int n, mod = 1e9 + 7;
    vector<vector<int>> nxt;    // nxt[i][j]表示第i个位置往后第一个j元素出现的位置
    vector<int> dp; // dp[i]表示以i为开头的不同子序列个数
public:

    int dfs(int x) {
        if (dp[x]) return dp[x];
        dp[x] = 1;
        for (int i = 0; i < 26; i++) {
            if (nxt[x + 1][i] != -1) {
                dp[x] += dfs(nxt[x + 1][i]);
                dp[x] %= mod;
            }
        }
        return dp[x];
    }

    int distinctSubseqII(string s) {
        n = s.size();
        dp = vector<int> (n + 1);
        nxt = vector<vector<int>> (n + 1, vector<int> (26, -1));
        // 求序列自动机
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < 26; j++) {
                nxt[i][j] = nxt[i + 1][j];
            }
            nxt[i][s[i] - 'a'] = i;
        }
        int res = 0;
        for (int i = 0; i < 26; i++) {
            if (nxt[0][i] != -1) {
                res += dfs(nxt[0][i]);
                res %= mod;
            }
        }
        return res;
    }
};