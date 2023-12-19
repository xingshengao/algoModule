// 例题: https://www.luogu.com.cn/problem/P2850
#include <bits/stdc++.h>
#define int long long

using namespace std;

struct Spfa {

    int n, inf = 1e9;
    vector<vector<vector<int>>> g;

    Spfa() {}
    Spfa(int n) {
        this->n = n;
        g.resize(n + 1);
    }

    void add(int a, int b, int w) { // 添加一条有向边
        g[a].push_back({b, w});
    }

    bool get() {    // 询问图中是否存在负环
        queue<int> q;
        vector<bool> used(n);
        vector<int> cnt(n + 1), dist(n + 1, inf);
        for (int i = 1; i <= n; i++) {
            q.push(i);
        }
        while (q.size()) {
            auto now = q.front();
            used[now] = 0;
            q.pop();
            for (int i = 0; i < g[now].size(); i++) {
                auto t = g[now][i];
                int nxt = t[0], w = t[1];
                if (dist[nxt] > dist[now] + w) {
                    dist[nxt] = dist[now] + w;
                    cnt[nxt] = cnt[now] + 1;
                    if (cnt[nxt] == n) {    // 当一条路径经过了至少n条边时,必定存在负环
                        return true;
                    }
                    if (!used[nxt]) {
                        used[nxt] = 1;
                        q.push(nxt);
                    }
                }
            }
        }
        return false;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, m, w;
        cin >> n >> m >> w;
        Spfa S(n);
        for (int i = 0; i < m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            S.add(a, b, c);
            S.add(b, a, c);
        }
        for (int i = 0; i < w; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            S.add(a, b, -c);
        }
        cout << (S.get() ? "YES" : "NO") << endl;
    }
    return 0;
}
