// https://www.acwing.com/problem/content/3/
#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, v;
    cin >> n >> v;
    vector<int> dp(v + 1);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        for (int j = 0; j <= v; j++) {
            if (j - a >= 0) {
                dp[j] = max(dp[j], dp[j - a] + b);
            }
        }
    }
    cout << dp[v] << endl;
}