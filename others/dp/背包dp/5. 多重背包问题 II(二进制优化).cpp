// https://www.acwing.com/problem/content/5/
#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> dp(m + 1);
    vector<vector<int>> goods;
    for (int i = 0; i < n; i++) {
        int v, w, s;
        cin >> v >> w >> s;
        for (int k = 1; k <= s; k *= 2) {
            s -= k;
            goods.push_back({v * k, w * k});
        }
        if (s > 0) goods.push_back({v * s, w * s});
    }
    for (int i = 0; i < goods.size(); i++) {
        int v = goods[i][0], w = goods[i][1];
        for (int j = m; j >= 0; j--) {
            if (j - v >= 0) {
                dp[j] = max(dp[j], dp[j - v] + w);
            }
        }
    }
    cout << dp[m] << endl;
}