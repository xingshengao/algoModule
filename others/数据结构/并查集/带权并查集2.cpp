// https://www.luogu.com.cn/problem/P1196
#include <bits/stdc++.h>

using namespace std;

struct dsu {
    
    vector<int> fa, d, siz;  // d[i] 表示i到其根节点的距离, siz[i] 表示以i为根的集合大小

    dsu() {}
    dsu(int n) {
        d.resize(n + 5);
        fa.resize(n + 5);
        siz.resize(n + 5, 1);
        for (int i = 0; i < n + 5; i++) {
            fa[i] = i;
        }
    }

    int find(int x) {
        if (x == fa[x]) {
            return x;
        } else {
            int f = find(fa[x]);
            d[x] += d[fa[x]];
            fa[x] = f;
            return f;
        }
    }

    void merge(int a, int b) {
        int pa = find(a), pb = find(b);
        if (pa == pb) return;
        d[pb] += siz[pa];
        siz[pa] += siz[pb];
        fa[pb] = pa;
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

};

signed main() {
    dsu D(30000);
    int t;
    cin >> t;
    while (t--) {
        char a;
        int b, c;
        cin >> a >> b >> c;
        if (a == 'M') {
            D.merge(c, b);
        } else {
            if (D.same(b, c)) {
                cout << abs(D.d[b] - D.d[c]) - 1 << endl;
            } else {
                cout << -1 << endl;
            }
        }
    }
}