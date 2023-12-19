// https://www.acwing.com/problem/content/3412/
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

// 如何判断有向图是不是树？
// 1、没有环 -> 通过并查集进行判断
// 2、每个节点只有一个入度 -> 通过一个数组记录
// 3、边数 + 1 == 点数

struct dsu {
    
    vector<int> fa;

    dsu() {}
    dsu(int n) {
        fa.resize(n + 5);
        for (int i = 0; i < n + 5; i++) {
            fa[i] = i;
        }
    }

    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }

    void merge(int a, int b) {
        fa[find(a)] = find(b);
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int a, b;
    dsu D(10000);
    bool f = 0;
    for (int Case = 1; ; Case++) {
        for (int i = 0; i <= 10000; i++) {
            D.fa[i] = i;
        }
        int a, b, ok = 1, m = 0;
        vector<bool> vis(10001), ind(10001);
        while (cin >> a >> b && a != 0 && b != 0) {
            if (ok) {
                if (D.same(a, b)) {
                    ok = 0;
                } else {
                    D.merge(a, b);
                    vis[a] = 1;
                    vis[b] = 1;
                    if (ind[b]) {
                        ok = 0;
                    } else {
                        ind[b] = 1;
                    }
                    m++;
                }
            }
        }
        if (a == -1) break;
        int sum = 0;
        for (int x : vis) sum += x;
        if (m + 1 != sum && m) {
            ok = 0;
        }
        cout << "Case " << Case << " is " << (ok ? "" : "not ") << "a tree" << endl;
    }
}