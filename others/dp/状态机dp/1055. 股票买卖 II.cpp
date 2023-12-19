// https://www.acwing.com/problem/content/1057/
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<vector<int>> dp(n + 1, vector<int> (2, -1e9));
    vector<int> w(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + w[i]);
        dp[i][1] = max(dp[i - 1][1], dp[i][0] - w[i]);
    }
    cout << dp[n][0] << endl;
}