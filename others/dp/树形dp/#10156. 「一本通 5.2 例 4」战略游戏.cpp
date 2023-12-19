// https://loj.ac/p/10156
#include <bits/stdc++.h>

using namespace std;

unordered_map<int, vector<int>> g;

unordered_map<int, int> dp1, dp2;

void dfs(int root, int fa) {
    if (g[root].size() == 1) {
        dp1[root] = 1;
        dp2[root] = 0;
    }
    dp1[root] = 1;
    int v1 = 1e9;
    for (int nxt : g[root]) {
        if (nxt == fa) continue;
        dfs(nxt, root);
        dp1[root] += min(dp1[nxt], dp2[nxt]);
        dp2[root] += dp1[nxt];
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int node, k;
        cin >> node >> k;
        for (int j = 0; j < k; j++) {
            int nxt;
            cin >> nxt;
            g[node].push_back(nxt);
            g[nxt].push_back(node);
        }
    }
    dfs(0, -1);
    cout << min(dp1[0], dp2[0]) << endl;
}