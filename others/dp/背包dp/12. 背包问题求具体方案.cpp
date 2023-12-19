// https://www.acwing.com/problem/content/12/
#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> v(n + 1), w(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i] >> w[i];
    }
    vector<vector<int>> dp(n + 2, vector<int> (m + 1));
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = dp[i + 1][j];
            if (j - v[i] >= 0) {
                dp[i][j] = max(dp[i][j], dp[i + 1][j - v[i]] + w[i]);
            }
        }
    }
    int j = m;
    for (int i = 1; i <= n; i++) {
        if (j - v[i] >= 0 && dp[i][j] == dp[i + 1][j - v[i]] + w[i]) {
            cout << i << ' ';
            j -= v[i];
        }
    }
}