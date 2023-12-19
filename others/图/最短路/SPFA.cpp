// 例题 : https://loj.ac/p/119
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct SPFA {
    queue<int> q;
    vector<int> dist;
    vector<bool> used;
    vector<vector<tuple<int, int>>> edges;
    
    SPFA(int n) {
        used.resize(n + 1);
        dist.resize(n + 1, 1e9);
        edges.resize(n + 1);
    }

    void add(int u, int v, int w) {
        edges[u].push_back({v, w});
    }

    void get_dist(int start) {
        dist[start] = 0;
        q.push(start);
        used[start] = 1;
        while (q.size()) {
            int now = q.front();
            q.pop();
            used[now] = 0;
            for (int i = 0; i < edges[now].size(); i++) {
                auto& nxt = edges[now][i];
                int v = get<0> (nxt), w = get<1> (nxt);
                if (dist[v] > dist[now] + w) {
                    dist[v] = dist[now] + w;
                    if (used[v] == 0) {
                        q.push(v);
                        used[v] = 1;
                    }
                }
            }
        }
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    SPFA S(n);
    while (m--) {
        int si, ti, w;
        cin >> si >> ti >> w;
        S.add(si, ti, w);
        S.add(ti, si, w);
    }
    S.get_dist(s);
    cout << S.dist[t] << endl;
    return 0;
}
