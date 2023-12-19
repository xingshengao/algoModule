// 例题: https://loj.ac/p/123
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct MST {

    vector<vector<int>> edges;
    vector<int> p;
    int n;

    MST() {}
    MST(int _n) {    // 构造函数,传入结点数
        n = _n;
        for (int i = 0; i <= n + 5; i++) {
            p.push_back(i);
        }
    }
    
    int find(int x) {
        return x == p[x] ? p[x] : p[x] = find(p[x]);
    }

    void add(int u, int v, int w) { // 添加一条带权值的无向边
        edges.push_back({u, v, w});
    }

    int Get_MST() { // 求最小生成树的权值之和
        int cnt = 0, res = 0;
        sort(edges.begin(), edges.end(), [](vector<int>& a, vector<int>& b) {
            return a[2] < b[2];
        }); 
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0], v = edges[i][1], w = edges[i][2];
            if (find(u) != find(v)) {
                p[find(u)] = find(v);
                cnt++;
                res += w;
                if (cnt == n - 1) return res;
            }
        }
        return 0;  // 无最小生成树, 返回0
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    MST S(n);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        S.add(u, v, w);
    }
    cout << S.Get_MST() << endl;
    return 0;
}
