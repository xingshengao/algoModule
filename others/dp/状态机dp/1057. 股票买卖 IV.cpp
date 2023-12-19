// https://www.acwing.com/problem/content/1059/
#include <bits/stdc++.h>

using namespace std;

int dp[100005][105][2];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    memset(dp, -0x3f, sizeof dp);
    vector<int> w(n + 1);
    for (int i = 0; i <= n; i++) {
        dp[i][0][0] = 0;
    }
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + w[i]);
            dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - w[i]);
        }
    }
    int res = 0;
    for (int i = 0; i <= k; i++) {
        res = max(res, dp[n][i][0]);
    }
    cout << res << endl;
}