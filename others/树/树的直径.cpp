// 例题: https://www.51nod.com/Challenge/Problem.html#problemId=2602
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct treeDiameter {
    
    vector<vector<vector<int>>> g;
    int n;

    treeDiameter() {}
    treeDiameter(int n) {   // 构造函数,输入点的数量
        this->n = n;
        g.resize(n + 5);
    }

    void add(int u, int v, int w) {    // 添加带权一条无向边
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    int get_diameter() {    // 求树的直径

        // 1.第一次bfs,获取离随机选择的点最大距离的点
        int point, max_value = -1e9;
        queue<vector<int>> q;
        q.push({1, 0});
        vector<bool> used(n + 5);
        while (q.size()) {
            auto t = q.front();
            q.pop();
            int now = t[0], value = t[1];
            if (used[now]) continue;
            if (value > max_value) {
                point = now;
                max_value = value;
            }
            used[now] = 1;
            for (int i = 0; i < g[now].size(); i++) {
                int nxt = g[now][i][0], w = g[now][i][1];
                q.push({nxt, value + w});
            }
        }
        
        // 2.第二次bfs,获取直径
        while (q.size()) q.pop();
        q.push({point, 0});
        fill(used.begin(), used.end(), 0);
        int res = 0;
        while (q.size()) {
            auto t = q.front();
            q.pop();
            int now = t[0], value = t[1];
            if (used[now]) continue;
            res = max(res, value);
            used[now] = 1;
            for (int i = 0; i < g[now].size(); i++) {
                int nxt = g[now][i][0], w = g[now][i][1];
                q.push({nxt, value + w});
            }
        }
        return res;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    treeDiameter T(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        T.add(u, v, 1);
    }
    cout << T.get_diameter() << endl;
    return 0;
}
