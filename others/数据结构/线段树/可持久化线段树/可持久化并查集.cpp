// https://www.luogu.com.cn/problem/P3402
// from : https://blog.csdn.net/qq_45832461/article/details/120580951
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

struct SegTree {

    struct node {
        int l, r;
        int v;
    };

    int idx;
    vector<node> tr;
    vector<int> root;   // 存每个版本根节点位置
    vector<int> a;      // 初始版本

    SegTree(int n = 1000005) {
        idx = 0;
        tr.resize(n * 25 + 5);  // 能开多大就开多大
        root.resize(n + 5);
    }

    void build(int& x, int l, int r) {  // 必须有build
        x = ++idx;
        if (l == r) {
            tr[x].v = a[l];
            return;
        }
        int m = l + r >> 1;
        build(tr[x].l, l, m);
        build(tr[x].r, m + 1, r);
    }

    void change(int& x, int y, int l, int r, int pos, int v) {  // 在y版本的基础上, 新增x版本
        x = ++idx;
        tr[x] = tr[y];
        if (l == r) {
            tr[x].v = v;
            return;
        }
        int m = l + r >> 1;
        if (pos <= m) {
            change(tr[x].l, tr[y].l, l, m, pos, v);
        } else {
            change(tr[x].r, tr[y].r, m + 1, r, pos, v);
        }
    }

    int query(int x, int l, int r, int pos) {   // 询问x版本pos位置的值
        if (l == r) {
            return tr[x].v;
        }
        int m = l + r >> 1;
        if (pos <= m) {
            return query(tr[x].l, l, m, pos);
        } else {
            return query(tr[x].r, m + 1, r, pos);
        }
    }

};

// 定义两个可持久化数组, fa记录第i个版本中并查集的祖宗节点, dep记录第i个版本中并查集的树深度
SegTree fa(200000), dep(200000);
int n, m;

int find(int ver, int x) {  // 找到第ver个版本中x的父亲
    int fx = fa.query(fa.root[ver], 1, n, x);
    if (x != fx) {
        x = find(ver, fx);
    } 
    return x;
}

void merge(int ver, int x, int y) { // 将第ver个版本中的集合x和集合y合并
    x = find(ver - 1, x);
    y = find(ver - 1, y);
    if (x == y) {
        fa.root[ver] = fa.root[ver - 1];
        dep.root[ver] = dep.root[ver - 1];
    } else {
        int depx = dep.query(dep.root[ver - 1], 1, n, x);
        int depy = dep.query(dep.root[ver - 1], 1, n, y);
        if (depx < depy) {
            fa.change(fa.root[ver], fa.root[ver - 1], 1, n, x, y);
            dep.root[ver] = dep.root[ver - 1];
        } else if (depx > depy) {
            fa.change(fa.root[ver], fa.root[ver - 1], 1, n, y, x);
            dep.root[ver] = dep.root[ver - 1];
        } else {
            fa.change(fa.root[ver], fa.root[ver - 1], 1, n, x, y);
            dep.change(dep.root[ver], dep.root[ver - 1], 1, n, y, depy + 1);
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    cin >> n >> m;
    vector<int> a(n + 5);
    for (int i = 0; i <= n; i++) {
        a[i] = i;
    }
    fa.a = a;
    fa.build(fa.root[0], 1, n);
    for (int i = 1; i <= m; i++) {
        int op;
        cin >> op;
        if (op == 1) {  // 合并a, b
            int a, b;
            cin >> a >> b;
            merge(i, a, b);
        } else if (op == 2) {   // 回退到第k次操作
            int k;
            cin >> k;
            fa.root[i] = fa.root[k];
            dep.root[i] = dep.root[k];
        } else {
            int a, b;
            cin >> a >> b;
            fa.root[i] = fa.root[i - 1];
            dep.root[i] = dep.root[i - 1];
            a = find(i, a);
            b = find(i, b);
            cout << (a == b ? 1 : 0) << endl;
        }
    }
    return 0;
}