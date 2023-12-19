// https://www.acwing.com/problem/content/4293/
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

// 如何判断无向图是否为树
// 1、判断是否有环 -> 并查集
// 2、不能是森林 -> 所有节点只有一个祖先
// 3、0个节点也算一棵树

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
    dsu D(100000);
    bool f = 0;
    while (cin >> a >> b) {
        if (a == -1 && b == -1) break;
        if (a == 0 && b == 0) {
            set<int> s;
            for (int i = 0; i <= 100000; i++) {
                if (i != D.find(i)) s.insert(D.find(i));
            }
            cout << (f || (s.size() != 1 && s.size() != 0) ? "No" : "Yes") << endl;
            f = 0;
            for (int i = 0; i <= 100000; i++) {
                D.fa[i] = i;
            }
            continue;
        }
        if (f) continue;
        if (D.same(a, b)) {
            f = 1;
        }
        D.merge(a, b);
    }
}