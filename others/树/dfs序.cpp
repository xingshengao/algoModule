// https://loj.ac/p/144
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct dfsOrder {

    int root, Time = 0; // root为起点, Time为时间戳
    unordered_map<int, vector<int>> g;
    unordered_map<int, int> l, r;
    // l[i]表示dfs进入子树i的时间
    // r[i]表示dfs离开子树i的时间

    dfsOrder() {}
    dfsOrder(int root) {
        this->root = root;
    }

    void addEdge(int a, int b) {    // 添加一条无向边
        g[a].push_back(b);
        g[b].push_back(a);
    }

    void getDfsOrder(int root, int fa) { // 获取dfs序, 调用时fa填-1
        l[root] = ++Time;
        for (int i = 0; i < g[root].size(); i++) {
            int nxt = g[root][i];
            if (nxt != fa) {
                getDfsOrder(nxt, root);
            }
        }
        r[root] = Time;
    }

};

struct BIT {    // 下标从1开始

    int n;
    vector<int> t;

    BIT(int _n) {
        n = _n + 4;
        t.resize(_n + 5);
    }

    void add(int x, int v) {
        for (; x <= n; x += x & -x) t[x] += v;
    }

    int ask(int x) {
        int res = 0;
        for (; x > 0; x -= x & -x) res += t[x];
        return res;
    }

    int ask_range(int l, int r) {return ask(r) - ask(l - 1);}
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, r;
    cin >> n >> m >> r;
    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    dfsOrder D(r);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        D.addEdge(a, b);
    }
    D.getDfsOrder(D.root, -1);

    BIT B(1000000);
    for (int i = 1; i <= n; i++) {
        B.add(D.l[i], v[i]);
    }
    while (m--) {
        int op, a, x;
        cin >> op;
        if (op == 1) {
            cin >> a >> x;
            B.add(D.l[a], x);
        } else {
            cin >> a;
            cout << B.ask_range(D.l[a], D.r[a]) << endl;
        }
    }
}