// https://loj.ac/p/10148
#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> v(2 * n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    for (int i = 1; i <= n; i++) {
        v[i + n] = v[i];
    }
    vector<vector<int>> dp(2 * n + 1, vector<int> (2 * n + 1, 0));
    for (int len = 3; len <= n + 1; len++) {
        for (int l = 1; l + len - 1 <= 2 * n; l++) {
            int r = l + len - 1;
            for (int m = l + 1; m < r; m++) {
                dp[l][r] = max(dp[l][m] + dp[m][r] + v[l] * v[m] * v[r], dp[l][r]);
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= n; i++) {
        res = max(res, dp[i][i + n]);
    }
    cout << res << endl;
}