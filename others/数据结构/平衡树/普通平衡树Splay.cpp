// https://loj.ac/p/104
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
        void init(int p1, int v1) {
            p = p1, v = v1;
            cnt = size = 1;
        }
    };

    int root;   // 根节点编号
    int idx;    // 结点个数
    int inf;    // 无穷大
    vector<node> tr;

    Splay() {}
    Splay(int n) {  // 构造函数, 传入结点个数最多为多少
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

    void find(int v) {  // 查找find, 找到v所在结点, 并把该结点转到根
        int x = root;
        while (tr[x].s[v > tr[x].v] && v != tr[x].v) {
            x = tr[x].s[v > tr[x].v];
        }
        splay(x, 0);
    }

    int get_pre(int v) {    // 前驱get_pre, 求v的前驱, 返回其节点编号
        find(v);
        int x = root;
        if (tr[x].v < v) return x;
        x = tr[x].s[0];
        while (tr[x].s[1]) {
            x = tr[x].s[1];
        }
        splay(x, 0);
        return x;
    }

    int get_suc(int v) {    // 后继get_suc, 求v的后继, 返回其节点编号
        find(v);
        int x = root;
        if (tr[x].v > v) return x;
        x = tr[x].s[1];
        while (tr[x].s[0]) {
            x = tr[x].s[0];
        }
        splay(x, 0);
        return x;
    }

    void del(int v) {   // 删除del, 删除v(若有多个相同的数, 只删除一个)
        int pre = get_pre(v);
        int suc = get_suc(v);
        splay(pre, 0), splay(suc, pre);
        int del = tr[suc].s[0];
        if (tr[del].cnt > 1) {
            tr[del].cnt--, splay(del, 0);
        } else {
            tr[suc].s[0] = 0, splay(suc, 0);
        }
    }

    int get_rank(int v) {   // 排名get_rank, 查询v数的排名
        int p = get_pre(v);
        return tr[p].cnt + tr[tr[p].s[0]].size + 1;
    }

    int get_val(int k) {    // 数值, 查询排名为k的数值
        int x = root;
        while (1) {
            int y = tr[x].s[0];
            if (tr[y].size + tr[x].cnt < k) {
                k -= tr[y].size + tr[x].cnt;
                x = tr[x].s[1];
            } else {
                if (tr[y].size >= k) {
                    x = tr[x].s[0];
                } else {
                    break;
                }
            }
        }
        splay(x, 0);
        return tr[x].v;
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
    int n;
    cin >> n;
    Splay S(n);
    while (n--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) S.insert(x);
        if (op == 2) S.del(x);
        if (op == 3) cout << S.get_rank(x) - 1 << endl; // 答案排名减1是因为加入了哨兵
        if (op == 4) cout << S.get_val(x + 1) << endl;  // 查排名为x+1是因为加入了哨兵
        if (op == 5) cout << S.tr[S.get_pre(x)].v << endl;
        if (op == 6) cout << S.tr[S.get_suc(x)].v << endl;
    }
}