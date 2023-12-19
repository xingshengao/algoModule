// https://www.acwing.com/problem/content/4/
#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, v;
    cin >> n >> v;
    vector<int> dp(v + 1);
    for (int i = 0; i < n; i++) {
        int a, b, s;
        cin >> a >> b >> s;
        for (int j = v; j >= 0; j--) {
            for (int k = 0; k <= s; k++) {
                if (j - k * a >= 0) {
                    dp[j] = max(dp[j], dp[j - k * a] + k * b);
                }
            }
        }
    }
    cout << dp[v] << endl;
}