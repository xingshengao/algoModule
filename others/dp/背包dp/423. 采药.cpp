// https://www.acwing.com/problem/content/425/
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t, m;
    cin >> t >> m;
    vector<int> dp(t + 1);
    vector<int> v(m + 1), w(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> v[i] >> w[i];
    }
    for (int i = 1; i <= m; i++) {
        for (int j = t; j >= 0; j--) {
            if (j - v[i] >= 0) {
                dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
            }
        }
    }
    cout << dp[t] << endl;
}