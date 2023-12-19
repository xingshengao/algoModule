// https://loj.ac/p/10170
#include <bits/stdc++.h>
#define int long long

using namespace std;

int dp[12][102][1 << 12];   // dp[i][j][k]表示在前i行，摆了j个国王，且第i行的摆放状态为k的方案数

int count(int x) {
    int res = 0;
    while (x) res += x % 2, x /= 2;
    return res;
}

bool check(int a, int b) {
    return ((a << 1) & b) == 0 && ((a >> 1) & b) == 0 && (a & b) == 0;
}

vector<int> ok;
vector<int> nxt[1 << 12];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < (1 << n); i++) {
        if (((i << 1) & i) == 0 && ((i >> 1) & i) == 0) ok.push_back(i);
    }
    for (int now : ok) {
        for (int i = 0; i < (1 << n); i++) {
            if (check(now, i)) {
                nxt[now].push_back(i);
            }
        }
    }
    for (int x : ok) {
        dp[1][count(x)][x] = 1;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            for (int u : ok) {
                for (int v : nxt[u]) {
                    dp[i][j][u] += dp[i - 1][j - count(u)][v];
                }
            }
        }
    }
    int res = 0;
    for (int i = 0; i < (1 << n); i++) {
        res += dp[n][k][i];
    }
    cout << res << endl;
}