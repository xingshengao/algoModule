// https://www.luogu.com.cn/problem/P1144
#include <bits/stdc++.h>

using namespace std;

struct Dijkstra {

    int mod = 100003;
    vector<int> dist, cnt;
    vector<vector<pair<int, int>>> g;

    Dijkstra(int n) {   // 构造函数
        dist.resize(n + 5, INT_MAX);
        cnt.resize(n + 5, 0);
        g.resize(n + 5);
    }

    void addEdge(int from, int to, int value) { // 添加有向边
        g[from].push_back({to, value});
    }

    void get_dist(int start) {  // 获取从start到其他点的最短路径长度
        dist[start] = 0;
        cnt[start] = 1;
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
                    cnt[v] = cnt[t];
                    q.push({u + w, v});
                } else if (u + w == dist[v]) {
                    cnt[v] += cnt[t];
                    cnt[v] %= mod;
                }
            }
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    Dijkstra D(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        D.addEdge(u, v, 1);
        D.addEdge(v, u, 1);
    }
    D.get_dist(1);
    for (int i = 1; i <= n; i++) {
        cout << D.cnt[i] << endl;
    }
    return 0;
}
