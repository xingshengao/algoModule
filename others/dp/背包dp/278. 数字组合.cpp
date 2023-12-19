// https://www.acwing.com/problem/content/280/
#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> dp(m + 1);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        for (int j = m; j >= 0; j--) {
            if (j - a >= 0) {
                dp[j] += dp[j - a];
            }
        }
    }
    cout << dp[m] << endl;
}