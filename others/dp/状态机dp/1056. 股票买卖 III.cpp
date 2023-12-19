// https://www.acwing.com/problem/content/description/1058/
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<vector<int>> dp(n + 1, vector<int> (5, -1e9));
    vector<int> w(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i][0] = dp[i - 1][0];
        dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - w[i]);
        dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + w[i]);
        dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] - w[i]);
        dp[i][4] = max(dp[i - 1][4], dp[i - 1][3] + w[i]);
    }
    cout << max({dp[n][0], dp[n][2], dp[n][4]}) << endl;
}