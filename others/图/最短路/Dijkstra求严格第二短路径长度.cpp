// https://www.luogu.com.cn/problem/P2865
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct Dijkstra {

    vector<int> dist, dist2;
    vector<vector<pair<int, int>>> g;

    Dijkstra(int n) {   // 构造函数
        dist.resize(n + 5, INT_MAX);
        dist2.resize(n + 5, INT_MAX);
        g.resize(n + 5);
    }

    void addEdge(int from, int to, int value) { // 添加有向边
        g[from].push_back({to, value});
    }

    void get_dist(int start) {  // 获取从start到其他点的最短路径长度
        dist[start] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
        q.push({0, start});
        while (!q.empty()) {
            int u = q.top().first, t = q.top().second;
            q.pop();
            if (u > dist2[t]) continue;
            for (int i = 0; i < g[t].size(); i++) {
                int v = g[t][i].first, w = g[t][i].second;
                if (u + w < dist[v]) {
                    dist2[v] = dist[v];
                    dist[v] = u + w;
                    q.push({u + w, v});
                }
                if (dist[v] < u + w && u + w < dist2[v]) {
                    dist2[v] = u + w;
                    q.push({u + w, v});
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
    Dijkstra D(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        D.addEdge(a, b, c);
        D.addEdge(b, a, c);
    }
    D.get_dist(1);
    cout << D.dist2[n] << endl;
    return 0;
}
