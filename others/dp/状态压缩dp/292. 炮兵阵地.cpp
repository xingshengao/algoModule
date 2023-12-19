// https://www.acwing.com/problem/content/294/
#include <bits/stdc++.h>

using namespace std;

int dp[101][1 << 10][1 << 10];

vector<int> ok, used;

int count(int x) {
    int res = 0;
    while (x) res += x % 2, x /= 2;
    return res;
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int t = 0;
        for (int j = 0; j < m; j++) {
            if (s[j] == 'H') t |= (1 << j);
        }
        used.push_back(t);
    }
    for (int i = 0; i < (1 << m); i++) {
        if ((i & (i << 1)) == 0 && (i & (i << 2)) == 0 && (i & (i >> 1)) == 0 && (i & (i >> 2)) == 0) {
            ok.push_back(i);
        }
    }
    if (n == 1) {
        int res = 0;
        for (int x : ok) {
            if ((x & used[0]) == 0) res = max(res, count(x));
        }
        cout << res << endl;
        return 0;
    }
    for (int x : ok) {
        for (int y : ok) {
            if ((x & y) | (x & (used[1])) | (y & used[0])) continue;
            dp[2][x][y] = count(x) + count(y);
        }
    }
    for (int i = 3; i <= n; i++) {
        for (int j : ok) {
            for (int k : ok) {
                for (int u : ok) {
                    if ((j & k) | (j & u) | (k & u)) continue;
                    if ((j & used[i - 1]) | (k & used[i - 2]) | (u & used[i - 3])) continue;
                    dp[i][j][k] = max(dp[i - 1][k][u] + count(j), dp[i][j][k]);
                }
            }
        }
    }
    int res = 0;
    for (int i = 2; i <= n; i++) {
        for (int j : ok) {
            for (int k : ok) {
                res = max(res, dp[i][j][k]);
            }
        }
    }
    cout << res << endl;
}