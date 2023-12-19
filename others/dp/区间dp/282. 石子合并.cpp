// https://www.acwing.com/problem/content/284/
#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> v(n + 1), pre(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        pre[i] = pre[i - 1] + v[i];
    }
    vector<vector<int>> dp(n + 1, vector<int> (n + 1, 2e9));
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 0;
    }
    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            for (int m = l; m < r; m++) {
                dp[l][r] = min(dp[l][m] + dp[m + 1][r] + pre[r] - pre[l - 1], dp[l][r]);
            }
        }
    }
    cout << dp[1][n] << endl;
}