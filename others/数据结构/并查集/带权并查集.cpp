// https://www.acwing.com/problem/content/4289/
#include <bits/stdc++.h>

using namespace std;

struct dsu {
    
    vector<int> fa, d;  // d[i] 表示i到其根节点的距离

    dsu() {}
    dsu(int n) {
        d.resize(n + 5);
        fa.resize(n + 5);
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
//             d[pb]
//         pa <------ pb
//         ↑          ↑
//    d[a] ↑          ↑ d[b]
//         ↑          ↑
//         a  <------ b
//               v
    void merge(int a, int b, int v) {
        int pa = find(a), pb = find(b);
        if (pa == pb) return;
        fa[pb] = pa;
        d[pb] = (d[a] + v - d[b]);
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

};

signed main() {
    int n, m;
    cin >> n >> m;
    dsu D(n);
    int res = 0;
    while (m--) {
        int l, r, s;
        cin >> l >> r >> s;
        l--;
        if (D.same(l, r)) {
            if (D.d[r] - D.d[l] != s) res++;
        } else {
            D.merge(l, r, s);
        }
    }
    cout << res << endl;
}