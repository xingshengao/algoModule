// https://loj.ac/p/10153
#include <bits/stdc++.h>

using namespace std;

int v[105][105], dp[105][105];
unordered_map<int, vector<int>> g;

int dfs(int root, int q, int fa) {
    if (dp[root][q] != -1) return dp[root][q];
    if (q == 0 || g[root].size() == 1) return 0;
    vector<int> son;
    for (int nxt : g[root]) {
        if (nxt != fa) son.push_back(nxt);
    }
    int lson = son[0], rson = son[1];
    int lv = v[root][lson], rv = v[root][rson];
    int res = max(dfs(lson, q - 1, root) + lv, dfs(rson, q - 1, root) + rv);
    if (q >= 2) {
        int nowq = q - 2;
        for (int i = 0; i <= nowq; i++) {
            res = max(res, dfs(lson, i, root) + dfs(rson, nowq - i, root) + lv + rv);
        }
    }
    return dp[root][q] = res;
}

int main() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        v[a][b] = c;
        v[b][a] = c;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    memset(dp, -1, sizeof dp);
    cout << dfs(1, q, -1) << endl;
}
