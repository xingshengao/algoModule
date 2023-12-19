
// https://leetcode.cn/problems/is-subsequence/

bool isSubsequence(string s, string t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> nxt(m + 1, vector<int> (26, -1));
    // 求序列自动机
    for (int i = m - 1; i >= 0; i--) {
        for (int j = 0; j < 26; j++) {
            nxt[i][j] = nxt[i + 1][j];
        }
        nxt[i][t[i] - 'a'] = i;
    }
    int l = 0;
    for (int i = 0; i < n; i++) {
        if (nxt[l][s[i] - 'a'] == -1) {
            return false;
        }
        l = nxt[l][s[i] - 'a'] + 1;
    }
    return true;
}
