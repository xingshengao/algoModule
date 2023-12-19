// https://www.luogu.com.cn/problem/P2657
#include <bits/stdc++.h>

using namespace std;

int dp[44][44][2][2];

int dfs(int pos, int pre, bool limit, bool full, string& s) {
    if (dp[pos][pre][limit][full] != -1) return dp[pos][pre][limit][full];
    if (pos == s.size()) return full;
    int res = 0;
    if (!full) res += dfs(pos + 1, pre, false, false, s);
    int now = s[pos] - '0';
    int down = full ? 0 : 1;
    int up = limit ? now : 9;
    for (int i = down; i <= up; i++) {
        if (abs(i - pre) >= 2) res += dfs(pos + 1, i, limit && (i == now), true, s);
    }
    return dp[pos][pre][limit][full] = res;
}

signed main() {
    int a, b;
    cin >> a >> b;
    string sa = to_string(a - 1), sb = to_string(b);
    memset(dp, -1, sizeof dp);
    int resa = dfs(0, 40, true, false, sa);
    memset(dp, -1, sizeof dp);
    int resb = dfs(0, 40, true, false, sb);
    cout << resb - resa << endl;
}