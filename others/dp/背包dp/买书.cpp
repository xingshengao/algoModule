// https://vjudge.net/problem/%E8%AE%A1%E8%92%9C%E5%AE%A2-T1225
#include <bits/stdc++.h>

using namespace std;

int d[] = {10, 20, 50, 100};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> dp(n + 1);
    dp[0] = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j <= n; j++) {
            if (j - d[i] >= 0) {
                dp[j] += dp[j - d[i]];
            }
        }
    }
    cout << dp[n] << endl;
}