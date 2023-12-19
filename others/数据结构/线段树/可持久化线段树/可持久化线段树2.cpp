// 例题: https://www.acwing.com/problem/content/257/
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

struct SegTree {

    int cnt = 1, n, len;
    vector<int> sum, root, rson, lson, ind;

    SegTree() {}
    SegTree(vector<int>& a) {
        n = a.size();
        ind = a;
        sort(ind.begin(), ind.end());
        root.resize(n + 10);
        sum.resize((n << 5) + 10);
        rson.resize((n << 5) + 10);
        lson.resize((n << 5) + 10);
        len = unique(ind.begin(), ind.end()) - ind.begin();
        root[0] = build(0, len - 1);
        for (int i = 0; i < n; i++) {
            root[i + 1] = change(root[i], 0, len - 1, getid(a[i]));
        }
    }

    int build(int l, int r) {
        int root = cnt++;
        if (l == r) return root;
        int mid = l + r >> 1;
        lson[root] = build(l, mid);
        rson[root] = build(mid + 1, r);
        return root;
    }

    int change(int root, int l, int r, int k) {
        int dir = cnt++;
        lson[dir] = lson[root], rson[dir] = rson[root], sum[dir] = sum[root] + 1;
        if (l == r) return dir;
        int mid = l + r >> 1;
        if (k <= mid) lson[dir] = change(lson[dir], l, mid, k);
        else rson[dir] = change(rson[dir], mid + 1, r, k);
        return dir;
    }

    int query(int u, int v, int l, int r, int k) {
        int mid = l + r >> 1, x = sum[lson[v]] - sum[lson[u]];
        if (l == r) return l;
        if (k <= x) return query(lson[u], lson[v], l, mid, k);
        else return query(rson[u], rson[v], mid + 1, r, k - x);
    }

    int getid(int val) {  // 离散化
        return lower_bound(ind.begin(), ind.begin() + len, val) - ind.begin();
    }

    int query_rank(int l, int r, int k) {   // 查询区间[l, r]内的第k小的数
        return ind[query(root[l], root[r + 1], 0, len - 1, k)];
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    SegTree S(a);
    while (m--) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << S.query_rank(l, r, k) << endl;
    }
    return 0;
}