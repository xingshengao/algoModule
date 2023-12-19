// https://loj.ac/p/105
#include <bits/stdc++.h>

using namespace std;

// Splay是一种平衡二叉树, 它通过不断将某个节点旋转到根节点, 使整棵树仍然满足BST的性质
struct Splay {

    struct node {
        int s[2];   // 左右儿子
        int p;  // 父亲
        int v;  // 结点权值
        int cnt;    // 权值出现次数
        int size;   // 子树大小
        int tag;    // 懒标记
        void init(int p1, int v1) {
            p = p1, v = v1;
            cnt = size = 1;
        }
    };

    int root;   // 根节点编号
    int idx;    // 结点个数
    int inf;    // 无穷大
    int n;
    vector<node> tr;

    Splay() {}
    Splay(int n) {  // 构造函数, 传入结点个数最多为多少
        this->n = n;
        root = 0;
        idx = 0;
        inf = 2e9;
        tr.resize(n + 5);
        insert(-inf);   // 插入两个哨兵
        insert(inf);
    }

    void pushup(int x) {    // 由儿子计算父亲的信息
        tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + tr[x].cnt;
    }

    void pushdown(int x) {  // 由父亲计算儿子的信息
        if (tr[x].tag) {
            swap(tr[x].s[0], tr[x].s[1]);
            tr[tr[x].s[0]].tag ^= 1;
            tr[tr[x].s[1]].tag ^= 1;
            tr[x].tag = 0;
        }
    }

    void rotate(int x) {    // 旋转rotate, 保序且信息正确
        int y = tr[x].p, z = tr[y].p;
        int k = tr[y].s[1] == x;
        tr[y].s[k] = tr[x].s[k ^ 1];
        tr[tr[x].s[k ^ 1]].p = y;
        tr[x].s[k ^ 1] = y;
        tr[y].p = x;
        tr[z].s[tr[z].s[1] == y] = x;
        tr[x].p = z;
        pushup(y), pushup(x);
    }

    void splay(int x, int k) { // 伸展splay, 访问一个节点x, 并且把x旋转到节点k下面
        while (tr[x].p != k) {
            int y = tr[x].p, z = tr[y].p;
            if (z != k) {
                if ((tr[y].s[0] == x) ^ (tr[z].s[0] == y)) {
                    rotate(x);
                } else {
                    rotate(y);
                }
            }
            rotate(x);
        }
        if (k == 0) root = x;
    }

    int get_k(int k) {  // 返回第k个结点编号
        int x = root;
        while (1) {
            pushdown(x);
            int y = tr[x].s[0];
            if (tr[y].size + 1 < k) {
                k -= tr[y].size + 1;
                x = tr[x].s[1];
            } else if (tr[y].size >= k) {
                x = y;
            } else {
                return x;
            }
        }
    }

    void output(int x) {    // 中序遍历输出
        pushdown(x);
        if (tr[x].s[0]) output(tr[x].s[0]);
        if (1 <= tr[x].v && tr[x].v <= n) {
            cout << tr[x].v << ' ';
        }
        if (tr[x].s[1]) output(tr[x].s[1]);
    }

    void insert(int v) {    // 插入一个数v
        int x = root, p = 0;
        while (x && tr[x].v != v) {
            p = x, x = tr[x].s[v > tr[x].v];
        }
        if (x) {
            tr[x].cnt++;
        } else {
            x = ++idx;
            tr[p].s[v > tr[p].v] = x;
            tr[x].init(p, v);
        }
        splay(x, 0);
    }

};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    Splay S(n);
    for (int i = 1; i <= n; i++) {
        S.insert(i);
    }
    while (m--) {
        int l, r;
        cin >> l >> r;
        l = S.get_k(l);
        r = S.get_k(r + 2);
        S.splay(l, 0);
        S.splay(r, l);
        S.tr[S.tr[r].s[0]].tag ^= 1;
    }
    S.output(S.root);
}