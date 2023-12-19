// https://www.acwing.com/problem/content/description/93/
#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<vector<int>> d(n, vector<int> (n, 2e9));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> d[i][j];
        }
    }
    vector<vector<int>> dp(1 << n, vector<int> (n, 2e9));
    dp[0][0] = 0;
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                for (int k = 0; k < n; k++) {
                    if (i & (1 << k)) {
                        dp[i][k] = min(dp[i ^ (1 << k)][j] + d[j][k], dp[i][k]);
                    }
                }
            }
        }
    }
    cout << dp[(1 << n) - 1][n - 1] << endl;
}