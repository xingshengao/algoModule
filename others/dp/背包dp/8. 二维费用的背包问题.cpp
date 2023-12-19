// https://www.acwing.com/problem/content/8/
#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, V, M;
    cin >> n >> V >> M;
    vector<vector<int>> dp(V + 1, vector<int> (M + 1));
    for (int i = 0; i < n; i++) {
        int v, m, w;
        cin >> v >> m >> w;
        for (int j = V; j >= 0; j--) {
            for (int k = M; k >= 0; k--) {
                if (j - v >= 0 && k - m >= 0) {
                    dp[j][k] = max(dp[j][k], dp[j - v][k - m] + w);
                }
            }
        }
    }
    cout << dp[V][M] << endl;
}