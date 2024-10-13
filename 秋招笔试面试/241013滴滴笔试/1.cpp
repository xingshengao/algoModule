#include <bits/stdc++.h>
#define int long long
using namespace std;

struct DSU {
    vector<int> f, siz;
    int cnt;
    DSU() {}
    DSU(int n) { init(n); }
    void init(int n) {
        cnt = n;
        f.resize(n);
        iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        cnt--;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[find(x)]; }
};

void solve() {
    int n, m;
    cin >> n >> m;
    // 倒序来
    vector<int> ans(n);
    vector<vector<int>> g(n);
    DSU dsu(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = n - 1; i >= 0; --i) {
        ans[i] = dsu.cnt - (i + 1);
        for (int j : g[i]) {
            if (j >= i) dsu.merge(i, j);
        }
    }
    for (int i = 0; i < n - 1; ++i) {
        cout << ans[i] << " ";
    }
    cout << ans.back() << endl;
}

signed main() {
    std::ios::sync_with_stdio(0), std::cout.tie(0), std::cin.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}