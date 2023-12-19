// https://www.luogu.com.cn/problem/P5905
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct Johnson {
    
    int n;
    queue<int> q;
    vector<int> h, cnt;
    vector<bool> used;
    vector<vector<vector<int>>> g;
    vector<vector<int>> dist;
    
    Johnson() {}
    Johnson(int n) {
        this->n = n;
        used = vector<bool> (n + 6);
        h = vector<int> (n + 6, 1e9);
        g = vector<vector<vector<int>>> (n + 6);
        cnt = vector<int> (n + 6);
        dist = vector<vector<int>> (n + 6, vector<int> (n + 6, 1e9));
    }

    void add(int a, int b, int c) { // 添加一条a->b权值为c的边
        g[a].push_back({b, c});
    }

    void spfa(int start) {
        h[start] = 0;
        q.push(start);
        used[start] = 1;
        while (q.size()) {
            int now = q.front();
            q.pop();
            used[now] = 0;
            for (int i = 0; i < g[now].size(); i++) {
                int v = g[now][i][0], w = g[now][i][1];
                if (h[v] > h[now] + w) {
                    h[v] = h[now] + w;
                    cnt[v] = cnt[now] + 1;
                    if (cnt[v] > n) {
                        cout << -1 << endl;
                        exit(0);
                    }
                    if (used[v] == 0) {
                        q.push(v);
                        used[v] = 1;
                    }
                }
            }
        }
    }

    void dijkstra(int start) {
        dist[start][start] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
        q.push({0, start});
        while (!q.empty()) {
            int u = q.top().first, t = q.top().second;
            q.pop();
            if (u > dist[start][t]) continue;
            for (int i = 0; i < g[t].size(); i++) {
                int v = g[t][i][0], w = g[t][i][1];
                if (u + w < dist[start][v]) {
                    dist[start][v] = u + w;
                    q.push({u + w, v});
                }
            }
        }
    }

    void get_dist() {   // 求全源最短路
        // 这里建立n + 5为虚拟节点
        for (int i = 1; i <= n; i++) {
            g[n + 5].push_back({i, 0});
        }
        spfa(n + 5);
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < g[i].size(); j++) {
                g[i][j][1] += h[i] - h[g[i][j][0]];
            }
        }
        for (int i = 0; i <= n; i++) {
            dijkstra(i);
            for (int j = 0; j <= n; j++) {
                if (dist[i][j] != 1e9) {
                    dist[i][j] += h[j] - h[i];
                }
            }
        }
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n, m;
    cin >> n >> m;
    Johnson J(n);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        J.add(a, b, c);
    }
    J.get_dist();
    for (int i = 1; i <= n; i++) {
        int res = 0;
        for (int j = 1; j <= n; j++) {
            res += j * J.dist[i][j];
        }
        cout << res << endl;
    }
    return 0;
}