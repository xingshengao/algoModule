// https://www.luogu.com.cn/problem/P3367
#include <bits/stdc++.h>

using namespace std;

struct dsu {
    
    vector<int> fa, siz;

    dsu() {}
    dsu(int n) {
        fa.resize(n + 5);
        siz.resize(n + 5, 1);
        for (int i = 0; i < n + 5; i++) {
            fa[i] = i;
        }
    }

    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }

    bool merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        siz[a] += siz[b];
        fa[b] = a;
        return true;
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    int size(int x) {
        return siz[find(x)];
    }

};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    dsu D(n);
    while (m--) {
        int z, x, y;
        cin >> z >> x >> y;
        if (z == 1) {
            D.merge(x, y);
        } else {
            cout << (D.same(x, y) ? 'Y' : 'N') << endl;
        }
    }
}