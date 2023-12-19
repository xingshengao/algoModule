#include <bits/stdc++.h>

using namespace std;

struct dsu {
    
    vector<int> fa, siz;
    vector<pair<int, int>> st;

    dsu() {}
    dsu(int n) {        // 构造函数
        fa.resize(n + 5);
        siz.resize(n + 5, 1);
        for (int i = 0; i < n + 5; i++) {
            fa[i] = i;
        }
    }

    int find(int x) {   // 找出集合x的根节点
        return x == fa[x] ? x : find(fa[x]);
    }

    bool merge(int a, int b) {  // 合并集合a和集合b
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (siz[a] < siz[b]) swap(a, b);
        st.push_back({a, b});
        siz[a] += siz[b];
        fa[b] = a;
        return true;
    }

    void roll() {   // 回滚到上一次操作前
        int a = st.back().first, b = st.back().second;
        st.pop_back();
        fa[b] = b;
        siz[a] -= siz[b];
    }

    bool same(int a, int b) {   // 判断元素a和元素b是否在同一集合
        return find(a) == find(b);
    }

};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    dsu D(100);
    D.merge(1, 2);
    D.merge(1, 3);
    cout << D.same(1, 2) << endl;
    cout << D.same(2, 3) << endl;
    D.roll();
    cout << D.same(1, 2) << endl;
    cout << D.same(2, 3) << endl;
    D.roll();
    cout << D.same(1, 2) << endl;
    cout << D.same(2, 3) << endl;
}