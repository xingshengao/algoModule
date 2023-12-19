// https://www.acwing.com/problem/content/329/
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

int dp[14][1 << 14], mod = 1e8; // dp[i][j]表示前面已经种植了i层，第i层种植状态为j的方案数

vector<int> ok, used;   // ok表示合法状态, used[i]表示第i层不能用的土地状态

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int t = 0;
        for (int j = 0; j < m; j++) {
            int a;
            cin >> a;
            if (!a) t |= (1 << j);
        }
        used.push_back(t);
    }
    for (int i = 0; i < (1 << m); i++) {
        if ((i & (i << 1)) == 0 && (i & (i >> 1)) == 0) ok.push_back(i);
    }
    for (int x : ok) {
        if ((x & used[0]) == 0) dp[1][x] = 1;
    }
    for (int i = 2; i <= n; i++) {
        for (int j : ok) {
            if (used[i - 1] & j) continue;
            for (int k : ok) {
                if (j & k) continue; 
                dp[i][j] += dp[i - 1][k];
                dp[i][j] %= mod;
            }
        }
    }
    int res = 0;
    for (int x : ok) {
        res += dp[n][x];
        res %= mod;
    }
    cout << res << endl;
}