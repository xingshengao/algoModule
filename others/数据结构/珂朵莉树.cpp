#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct node {
    int l, r;
    mutable int v;
    
    bool operator < (const node& a) const {
        return l < a.l;
    }
};

struct ODT {

    int n;
    set<node> odt;
    ODT() {}
    ODT(int n) {    // 构造函数
        this->n = n;
    }

    auto split(int x) {     // 分裂区间
        if (x > n) return odt.end();
        auto it = --odt.upper_bound({x, 0, 0});
        if (it->l == x) return it;
        int l = it->l, r = it->r, v = it->v;
        odt.erase(it);
        odt.insert({l, x - 1, v});
        return odt.insert({x, r, v}).first;
    }

    void assign(int l, int r, int v) {  // 区间赋值
        auto itr = split(r + 1), itl = split(l);
        odt.erase(itl, itr);
        odt.insert({l, r, v});
    }

    void add(int l, int r, int v) {     // 区间加法
        auto itr = split(r + 1), itl = split(l);
        for (; itl != itr; ++itl) {
            itl->v += v;
        }
    }

    int query_sum(int l, int r) {       // 区间求和
        int res = 0;
        auto itr = split(r + 1), itl = split(l);
        for (; itl != itr; ++itl) {
            res += (itl->r - itl->l + 1) * itl->v;
        }
        return res;
    }

    int kth(int l, int r, int k) {      // 区间求第k小
        auto end = split(r + 1);
        vector<tuple<int, int>> v;  // 存节点的值和区间长度
        for (auto it = split(l); it != end; it++) {
            v.push_back({it->v, it->r - it->l + 1});
        }
        sort(v.begin(), v.end());
        for (int i = 0; i < v.size(); i++) {
            k -= get<1> (v[i]);
            if (k <= 0) {
                return get<0> (v[i]);
            }
        }
        return -1;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    ODT O(n);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        O.odt.insert({i, i, a});
    }
    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << O.kth(l, r, k) << endl;
    }
    return 0;
}
