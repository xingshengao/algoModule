// https://www.luogu.com.cn/problem/P3690
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

// 给定 n 个点 (编号为 1 ~ n) 以及每个点的权值，你需要在此基础上处理接下来给出的 m 个操作。
// 操作有以下四种：

// 0 x y 代表询问从 x 到 y 的路径上的点的权值的 xor 和。保证 x 到 y 是联通的。
// 1 x y 代表连接 x 到 y, 若 x 到 y 已经联通则无需连接。
// 2 x y 代表删除边 (x,y)，不保证边 (x,y) 存在。
// 3 x y 代表将点 x 上的权值变成 y。

struct LCT {
    
    #define fa(x) tr[x].p
    #define lc(x) tr[x].s[0]
    #define rc(x) tr[x].s[1]
    #define notroot(x) lc(fa(x)) == x || rc(fa(x)) == x

    int n, m;
    struct node {
        int s[2], p, v, sum;    // 分别为左右儿子、父亲、权值和子树权值和
        int tag;    // 翻转懒标记
    };

    vector<node> tr;

    LCT() {}
    LCT(int n) {    // 结点数量
        tr.resize(n + 5);
    }

    void pushup(int x) {    // 由子结点信息计算父结点信息
        tr[x].sum = tr[lc(x)].sum ^ tr[x].v ^ tr[rc(x)].sum;
    }

    void pushdown(int x) {  // 由父结点信息计子结点信息
        if (tr[x].tag) {
            swap(lc(x), rc(x));
            tr[lc(x)].tag ^= 1;
            tr[rc(x)].tag ^= 1;
            tr[x].tag = 0;
        }
    }

    void rotate(int x) {    // 旋转rotate, 保序且信息正确
        int y = fa(x), z = fa(y);
        int k = rc(y) == x;
        if (notroot(y)) {
            tr[z].s[rc(z) == y] = x;
        }
        fa(x) = z;
        tr[y].s[k] = tr[x].s[k ^ 1];
        fa(tr[x].s[k ^ 1]) = y;
        tr[x].s[k ^ 1] = y;
        fa(y) = x;
        pushup(y), pushup(x);
    }

    void pushall(int x) {   // 在 access 操作之后, 递归地从上到下 pushDown 更新信息
        if (notroot(x)) pushall(fa(x));
        pushdown(x);
    }

    void splay(int x) {     // 伸展splay, 访问一个节点x, 并且把x旋转到节点k下面
        pushall(x);
        while (notroot(x)) {
            int y = fa(x), z = fa(y);
            if (notroot(y)) {
                (rc(y) == x) ^ (rc(z) == y) ? rotate(x) : rotate(y);
            }
            rotate(x);
        }
    }

    void access(int x) {    // 打通从x到树根的路径, 把路径变成一条实链
        for (int y = 0; x; ) {
            splay(x);
            rc(x) = y;
            pushup(x);
            y = x, x = fa(x);
        }
    }

    void makeroot(int x) {  // 换根, 把指定点x变成树根
        access(x);
        splay(x);
        tr[x].tag ^= 1;
    }

    void split(int x, int y) {  // 提取出x, y间的路径，方便做区间操作
        makeroot(x);
        access(y);
        splay(y);
    }

    void output(int x, int y) { // 输出从x到y路径的权值和
        split(x, y);
        cout << tr[y].sum << endl;
    }

    int findroot(int x) {      // 找到x所在树的根节点编号
        access(x);
        splay(x);
        while (lc(x)) {
            pushdown(x), x = lc(x);
        }
        splay(x);
        return x;
    }

    void link(int x, int y) {   // 对x和y进行连边
        makeroot(x);
        if (findroot(y) != x) fa(x) = y;
    }

    void cut(int x, int y) {    // 切断x与y之间的边
        makeroot(x);
        if (findroot(y) == x && fa(y) == x && !lc(y)) {
            rc(x) = fa(y) = 0;
            pushup(x);
        }
    }

    void change(int x, int y) { // 更改结点x的权值为y
        splay(x);
        tr[x].v = y;
        pushup(x);
    }

};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n, m;
    cin >> n >> m;
    LCT lct(n);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        lct.change(i, a);
    }
    while (m--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 0) {
            lct.output(x, y);
        } else if (op == 1) {
            lct.link(x, y);
        } else if (op == 2) {
            lct.cut(x, y);
        } else {
            lct.change(x, y);
        }
    }
    return 0;
}
