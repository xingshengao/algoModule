// https://www.acwing.com/problem/content/7/
#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> dp(m + 1);
    for (int i = 1; i <= n; i++) {
        int v, w, s;
        cin >> v >> w >> s;
        if (s == -1) {  // 01背包
            for (int j = m; j >= v; j--) {
                dp[j] = max(dp[j], dp[j - v] + w);
            }
        } else if (s == 0) {    // 完全背包
            for (int j = v; j <= m; j++) {
                dp[j] = max(dp[j], dp[j - v] + w);
            }
        } else {    // 多重背包, 二进制优化
            for (int k = 1; k <= s; k *= 2) {
                s -= k;
                int vk = v * k, wk = w * k;
                for (int j = m; j >= vk; j--) {
                    dp[j] = max(dp[j], dp[j - vk] + wk);
                }
            }
            if (s) {
                int vs = v * s, ws = w * s;
                for (int j = m; j >= vs; j--) {
                    dp[j] = max(dp[j], dp[j - vs] + ws);
                }
            }
        }
    }
    cout << dp[m] << endl;
}