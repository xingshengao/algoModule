// https://www.acwing.com/problem/content/description/11/
#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    int mod = 1e9 + 7;
    vector<int> dp(m + 1), cnt(m + 1, 1);
    for (int i = 1; i <= n; i++) {
        int v, w;
        cin >> v >> w;
        for (int j = m; j >= v; j--) {
            int t = dp[j - v] + w;
            if (t > dp[j]) {
                dp[j] = t;
                cnt[j] = cnt[j - v];
            } else if (t == dp[j]) {
                cnt[j] = (cnt[j] + cnt[j - v]) % mod;
            }
        }
    }
    cout << cnt[m] << endl;
}