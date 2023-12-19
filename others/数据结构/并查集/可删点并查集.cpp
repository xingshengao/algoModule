// https://www.luogu.com.cn/problem/U130175
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

// 维护一个并查集，支持以下操作：
// 1 u v : 将 u 和 v 合并
// 2 u v : 将 u 从原有的集合删除，加入到 v 所在的集合
// 3 u v : 询问 u 和 v 是否处于同一个集合

struct dsu {
    
    int cnt;
    vector<int> fa, siz;
    vector<int> id; // id[i]表示i这个点的最新编号

    dsu() {}
    dsu(int n, int m) { // n为点数, m为操作次数, 下标从0开始
        cnt = n;
        fa.resize(n + m + 5);
        siz.resize(n + m + 5);
        id.resize(n + m + 5);
        for (int i = 0; i < n; i++) {
            fa[i] = i;
            id[i] = i;
            siz[i] = 1;
        }
    }

    int _find(int x) {  // 其他地方访问find都要用find(id[x])
        return x == fa[x] ? x : fa[x] = _find(fa[x]);
    }

    int find(int x) {   // 查询x的祖先结点
        return _find(id[x]);
    }

    bool merge(int a, int b) {  // 合并集合a和集合b
        a = find(a);
        b = find(b);
        if (a == b) return false;
        siz[a] += siz[b];
        fa[b] = a;
        return true;
    }

    bool same(int a, int b) {   // 判断a和b两个点是否在同一集合
        return find(a) == find(b);
    }

    void move(int x) {      // 把x从所在的集合删除, 并独立成为一个新的集合
        siz[find(x)]--;
        id[x] = cnt++;
        siz[id[x]] = 1;
        fa[id[x]] = id[x];
    }

    int size(int x) {       // 返回x所在集合的大小
        return siz[find(x)];
    }

};


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n, m;
    cin >> n >> m;
    dsu D(n + 1, m);
    while (m--) {
        int op, u, v;
        cin >> op >> u >> v;
        if (op == 1) {
            D.merge(u, v);
        } else if (op == 2) {
            D.move(u);
            D.merge(u, v);
        } else {
            cout << (D.same(u, v) ? "YES" : "NO") << endl;
        }
    }
    set<int> cnt;
    for (int i = 1; i <= n; i++) {
        cnt.insert(D.find(i));
    }
    cout << cnt.size() << endl;
    return 0;
}
