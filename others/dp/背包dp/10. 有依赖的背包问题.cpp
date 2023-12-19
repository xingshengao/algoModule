// https://www.acwing.com/problem/content/10/
#include <bits/stdc++.h>

using namespace std;

int n, m, root;
unordered_map<int, vector<int>> g;
vector<int> v, w;
vector<vector<int>> dp;

void dfs(int root) {
    for (int i = v[root]; i <= m; i++) {
        dp[root][i] = w[root];
    }
    for (int son : g[root]) {
        dfs(son);
        for (int i = m; i >= v[root]; i--) {
            for (int k = 0; k <= i - v[root]; k++) {
                dp[root][i] = max(dp[root][i], dp[root][i - k] + dp[son][k]);
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    v.resize(n + 1);
    w.resize(n + 1);
    dp.resize(n + 1, vector<int> (m + 1));
    for (int i = 1; i <= n; i++) {
        int fa;
        cin >> v[i] >> w[i] >> fa;
        if (fa != -1) {
            g[fa].push_back(i);
        } else {
            root = i;
        }
    }
    dfs(root);
    cout << dp[root][m] << endl;
}