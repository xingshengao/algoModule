// https://www.luogu.com.cn/problem/P6348
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct Dijkstra {

    vector<int> dist;
    vector<vector<pair<int, int>>> g;

    Dijkstra() {}
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

Dijkstra D;

struct SegTree {
    
    #define ls(p) (p << 1)
    #define rs(p) (p << 1 | 1)

    int n, m, inf = 2e9;
    int idx;    // 虚拟点下标
    vector<int> id; // i在出树上的编号
    
    SegTree() {}
    SegTree(int n, int m) { // n为点数, m为边数
        this->n = n;
        this->m = m;
        this->idx = 8 * n;
        id = vector<int> (n * 4 + 5);
    }

    void build_in(int p, int l, int r) {    // 建立入树
        if (l == r) return;
        int m = l + r >> 1;
        build_in(ls(p), l, m);
        build_in(rs(p), m + 1, r);
        D.addEdge(p, ls(p), 0);
        D.addEdge(p, rs(p), 0);
    }

    void build_out(int p, int l, int r) {    // 建立出树
        D.addEdge(p, p + n * 4, 0);
        if (l == r) {
            id[l] = p + n * 4;
            return;
        }
        int m = l + r >> 1;
        build_out(ls(p), l, m);
        build_out(rs(p), m + 1, r);
        D.addEdge(ls(p) + n * 4, p + n * 4, 0);
        D.addEdge(rs(p) + n * 4, p + n * 4, 0);
    }

    void add1(int p, int l, int r, int ql, int qr, int k, int v) { // 添加一条从出树线段[ql,qr]指向虚拟点k, 权值为v的边
        if (ql <= l && r <= qr) {
            D.addEdge(p + n * 4, k, v);
            return;
        }
        int m = l + r >> 1;
        if (ql <= m) {
            add1(ls(p), l, m, ql, qr, k, v);
        }
        if (m < qr) {
            add1(rs(p), m + 1, r, ql, qr, k, v);
        }
    }

    void add2(int p, int l, int r, int ql, int qr, int k, int v) { // 添加一条从虚拟点k指向入树线段[ql,qr], 权值为v的边
        if (ql <= l && r <= qr) {
            D.addEdge(k, p, 0);
            return;
        }
        int m = l + r >> 1;
        if (ql <= m) {
            add2(ls(p), l, m, ql, qr, k, v);
        }
        if (m < qr) {
            add2(rs(p), m + 1, r, ql, qr, k, v);
        }
    }

    void add(int a, int b, int c, int d, int v) {  // [a,b]的每个数向[c,d]的每个数连一条长度为v的有向边
        ++idx;
        add1(1, 1, n, a, b, idx, v);
        add2(1, 1, n, c, d, idx, 0);
    }

};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n, m, p;
    cin >> n >> m >> p;
    D = Dijkstra(8 * n + 2 * m);    // 8n+2m是两棵线段树和虚拟点加起来的总点数
    SegTree S(n, m);
    S.build_in(1, 1, n);
    S.build_out(1, 1, n);
    // 入树1~4n
    // 出树4n+1~8n
    // 虚拟点8n+1~8n+2m
    for (int i = 1; i <= m; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        // 注意题目说是无向边
        S.add(a, b, c, d, 1);
        S.add(c, d, a, b, 1);
    }
    D.get_dist(S.id[p]);
    for (int i = 1; i <= n; i++) {
        cout << D.dist[S.id[i]] << endl;
    }
    return 0;
}
