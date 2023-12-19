// https://leetcode.cn/problems/minimum-score-triangulation-of-polygon/
class Solution {
    int dp[55][55];
    vector<int> v;
public:

    int dfs(int l, int r) {
        if (dp[l][r] != -1) return dp[l][r];
        if (r - l < 2) return 0;
        int res = 2e9;
        for (int i = l + 1; i < r; i++) {
            res = min(res, dfs(l, i) + dfs(i, r) + v[l] * v[i] * v[r]);
        }
        return dp[l][r] = res;
    }

    int minScoreTriangulation(vector<int>& values) {
        this->v = values;
        memset(dp, -1, sizeof dp);
        return dfs(0, values.size() - 1);
    }
};