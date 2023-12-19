#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n;
    cin >> n;
    int m = sqrt(n);
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> dp(n + 1, vector<int> (m + 1));
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= m; j++) {
            if (i + a[i] + j > n) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = dp[i + a[i] + j][j] + 1;
            }
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int p, k;
        cin >> p >> k;
        if (k <= m) {
            cout << dp[p][k] << endl;
        } else {
            int res = 0;
            while (p <= n) {
                p += a[p] + k;
                res++;
            }
            cout << res << endl;
        }
    }
    return 0;
}
