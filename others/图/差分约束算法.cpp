// https://www.luogu.com.cn/problem/P5960
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct SPFA {
    int n;
    queue<int> q;
    vector<int> dist, cnt;
    vector<bool> used;
    vector<vector<tuple<int, int>>> edges;
    
    SPFA() {}
    SPFA(int n) {
        this->n = n;
        used.resize(n + 1);
        dist.resize(n + 1, INT_MAX);    // 求最短路初始化为正无穷；求最长路初始化为-1
        edges.resize(n + 1);
        cnt.resize(n + 1);
    }

    void add(int u, int v, int w) {
        edges[u].push_back({v, w});
    }

    bool get_dist(int start) {
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
                if (dist[v] > dist[now] + w) {  // 如果求的是各变量的最小值，则求最长路；如果求的是各点的最大值，则求最短路；变一下大于小于号即可
                    dist[v] = dist[now] + w;
                    cnt[v] = cnt[now] + 1;
                    if (cnt[v] == n + 1) {   // 因为加了一个超级原点，所以有n + 1个点
                        return false;
                    }
                    if (used[v] == 0) {
                        q.push(v);
                        used[v] = 1;
                    }
                }
            }
        }
        return true;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    SPFA S(n);
    for (int i = 0; i < m; i++) {
        int x1, x2, y;
        cin >> x1 >> x2 >> y;
        S.add(x2, x1, y);
    }
    int start = 0;  // 以0为起点，建立从0到其他所有点的边，以保证图联通，然后从0开始求最短路
    for (int i = 1; i <= n; i++) {
        S.add(start, i, 0);
    }
    if (S.get_dist(start)) {
        for (int i = 1; i <= n; i++) {
            cout << S.dist[i] << ' ';
        }
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
