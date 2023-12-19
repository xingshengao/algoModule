#include <bits/stdc++.h>

using namespace std;

struct treeCentroid {

    int n;          // 结点个数
    int minBalance; // 重心为根的最大子树大小
    int res;        // 重心的结点编号
    vector<int> siz;
    vector<vector<int>> g;

    treeCentroid() {}
    treeCentroid(int n) {
        this->n = n;
        minBalance = INT_MAX;
        siz.resize(n + 5);
        g.resize(n + 5);
    }

    void add(int a, int b) {    // 添加一条a到b的无向边
        g[a].push_back(b);
        g[b].push_back(a);
    }

    void dfs(int node, int parent) {
        siz[node] = 1;
        int maxSubTree = 0;
        for (int i = 0; i < g[node].size(); i++) {
            int son = g[node][i];
            if (son != parent) {
                dfs(son, node);
                siz[node] += siz[son];
                maxSubTree = max(maxSubTree, siz[son]);
            }
        }
        maxSubTree = max(maxSubTree, n - siz[node]);
        if (maxSubTree < minBalance) {
            minBalance = maxSubTree;
            res = node;
        }
    }

};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        treeCentroid D(n);
        for (int i = 0; i < n - 1; i++) {
            int a, b;
            cin >> a >> b;
            D.add(a, b);
        }
        D.dfs(1, -1);
        cout << D.res << ' ' << D.minBalance << endl;
    }
    return 0;
}
