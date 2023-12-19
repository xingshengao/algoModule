// https://www.acwing.com/problem/content/description/9/
#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<vector<int>>> vw(n + 1);
    for (int i = 1; i <= n; i++) {
        int v, w, k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            cin >> v >> w;
            vw[i].push_back({v, w});
        }
    }
    vector<vector<int>> dp(n + 1, vector<int> (m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = dp[i - 1][j];
            for (int k = 0; k < vw[i].size(); k++) {
                int v = vw[i][k][0], w = vw[i][k][1];
                if (j - v >= 0) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - v] + w);
                }
            }
        }
    }
    cout << dp[n][m] << endl;
}