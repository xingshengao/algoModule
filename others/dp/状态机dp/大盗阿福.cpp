// https://vjudge.net/problem/%E8%AE%A1%E8%92%9C%E5%AE%A2-T1227
#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    vector<vector<int>> dp(n + 1, vector<int> (2));
    dp[1][1] = v[1];
    for (int i = 2; i <= n; i++) {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
        dp[i][1] = dp[i - 1][0] + v[i];
    }
    cout << max(dp[n][0], dp[n][1]) << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}