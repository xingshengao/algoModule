// https://www.luogu.com.cn/problem/AT_abc183_f
// 维护每个集合所含元素的哈希表, 考虑每个元素从一个哈希表移到另一个哈希表最多移动多少次
// 元素从小集合合并到大集合里, 每次合并哈希表大小乘2, 最多合log次
#include <bits/stdc++.h>

using namespace std;

struct dsu {
    
    vector<int> fa;
    vector<map<int, int>> cnt;

    dsu() {}
    dsu(int n) {
        fa.resize(n + 5);
        cnt.resize(n + 5);
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
        if (cnt[a].size() < cnt[b].size()) {
            swap(a, b);
        }
        for (auto x : cnt[b]) {
            cnt[a][x.first] += x.second;
        }
        fa[b] = a;
        return true;
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    dsu D(n);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        D.cnt[i][a]++;
    }
    while (q--) {
        int op, a, b;
        cin >> op >> a >> b;
        if (op == 1) {
            D.merge(a, b);
        } else {
            cout << D.cnt[D.find(a)][b] << endl;
        }
    }
}