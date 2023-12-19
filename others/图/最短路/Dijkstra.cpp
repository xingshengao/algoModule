// https://www.luogu.com.cn/problem/P4779
#include <bits/stdc++.h>

using namespace std;

struct Dijkstra {

    vector<int> dist;
    vector<vector<pair<int, int>>> g;

    Dijkstra(int n) {   // 构造函数
        dist.resize(n + 5, INT_MAX);
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
            if (u > dist[t]) continue;
            for (int i = 0; i < g[t].size(); i++) {
                int v = g[t][i].first, w = g[t][i].second;
                if (u + w < dist[v]) {
                    dist[v] = u + w;
                    q.push({u + w, v});
                }
            }
        }
    }
};

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    Dijkstra D(n);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        D.addEdge(u, v, w);
    }
    D.get_dist(s);
    for (int i = 1; i <= n; i++) {
        cout << D.dist[i] << ' ';
    }
    cout << endl;
    return 0;
}
