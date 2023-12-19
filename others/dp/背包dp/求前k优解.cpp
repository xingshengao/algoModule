// https://www.luogu.com.cn/problem/P1858
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
	cout.tie(0);
	cout << fixed << setprecision(15);
    int k, v, n;
    cin >> k >> v >> n;
    vector<vector<int>> goods(n, vector<int> (2));
    for (int i = 0; i < n; i++) {
        cin >> goods[i][0] >> goods[i][1];
    }
    // dp[i][j]表示体积为i的第j优解
    vector<vector<int>> dp(v + 1, vector<int> (k + 1, -1e9));
    dp[0][1] = 0;
    for (int i = 0; i < n; i++) {
        int a = goods[i][0], b = goods[i][1];
        for (int j = v; j >= a; j--) {
            vector<int> tdp;
            int l1 = 1, l2 = 1;
            while (tdp.size() < k) {
                if (dp[j][l1] >= dp[j - a][l2] + b) {
                    tdp.push_back(dp[j][l1++]);
                } else {
                    tdp.push_back(dp[j - a][l2++] + b);
                }
            }
            for (int u = 1; u <= k; u++) {
                dp[j][u] = tdp[u - 1];
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= k; i++) {
        res += dp[v][i];
    }
    cout << res << endl;
    return 0;
}
