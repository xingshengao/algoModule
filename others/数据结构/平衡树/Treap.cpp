// 例题: https://loj.ac/p/104
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct Node {
    int l, r;
    int key, val;
    int cnt, size;
};

struct Treap {
    
    vector<Node> tr;
    int root, idx, inf = 1e9;

    Treap() {}
    Treap(int n) {
        idx = 0;
        tr.resize(n);
        get_node(-inf), get_node(inf);
        root = 1, tr[1].r = 2;
        pushup(root);
    }

    int get_node(int key) {
        tr[++idx].key = key;
        tr[idx].val = rand();
        tr[idx].cnt = tr[idx].size = 1;
        return idx;
    }

    void pushup(int p) {
        tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + tr[p].cnt;
    }

    void zig(int &p) { // 右旋
        int q = tr[p].l;
        tr[p].l = tr[q].r, tr[q].r = p, p = q;
        pushup(tr[p].r), pushup(p);
    }

    void zag(int &p) { // 左旋
        int q = tr[p].r;
        tr[p].r = tr[q].l, tr[q].l = p, p = q;
        pushup(tr[p].l), pushup(p);
    }

    void insert(int &p, int key) {
        if (!p) {
            p = get_node(key);
        } else if (tr[p].key == key) {
            tr[p].cnt++;
        } else if (tr[p].key > key) {
            insert(tr[p].l, key);
            if (tr[tr[p].l].val > tr[p].val) zig(p);
        } else {
            insert(tr[p].r, key);
            if (tr[tr[p].r].val > tr[p].val) zag(p);
        }
        pushup(p);
    }

    void remove(int &p, int key) {
        if (!p) return;
        if (tr[p].key == key) {
            if (tr[p].cnt > 1) {
                tr[p].cnt--;
            } else if (tr[p].l || tr[p].r) {
                if (!tr[p].r || tr[tr[p].l].val > tr[tr[p].r].val) {
                    zig(p);
                    remove(tr[p].r, key);
                } else {
                    zag(p);
                    remove(tr[p].l, key);
                }
            } else {
                p = 0;
            }
        } else if (tr[p].key > key) {
            remove(tr[p].l, key);
        } else {
            remove(tr[p].r, key);
        }
        pushup(p);
    }

    int get_rank_by_key(int p, int key) {
        if (!p) return 0;
        if (tr[p].key == key) return tr[tr[p].l].size + 1;
        if (tr[p].key > key) return get_rank_by_key(tr[p].l, key);
        return tr[tr[p].l].size + tr[p].cnt + get_rank_by_key(tr[p].r, key);
    }

    int get_key_by_rank(int p, int rank) {
        if (!p) return inf;
        if (tr[tr[p].l].size >= rank) return get_key_by_rank(tr[p].l, rank);
        if (tr[tr[p].l].size + tr[p].cnt >= rank) return tr[p].key;
        return get_key_by_rank(tr[p].r, rank - tr[tr[p].l].size - tr[p].cnt);
    }

    int get_prev(int p, int key) {
        if (!p) return -inf;
        if (tr[p].key >= key) return get_prev(tr[p].l, key);
        return max(tr[p].key, get_prev(tr[p].r, key));
    }

    int get_next(int p, int key) {
        if (!p) return inf;
        if (tr[p].key <= key) return get_next(tr[p].r, key);
        return min(tr[p].key, get_next(tr[p].l, key));
    }
};


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    Treap T(100005);
    while (n--) {
        int opt, x;
        cin >> opt >> x;
        if (opt == 1) T.insert(T.root, x);  // 插入x数
        else if (opt == 2) T.remove(T.root, x); // 删除x数（若有多个相同的数，只删除一个）
        else if (opt == 3) cout << T.get_rank_by_key(T.root, x) - 1 << endl;    // 查询x数的排名（若有多个相同的数，输出最小的排名）
        else if (opt == 4) cout << T.get_key_by_rank(T.root, x + 1) << endl;    // 查询排名为x的数
        else if (opt == 5) cout << T.get_prev(T.root, x) << endl;   // 求x的前驱（前驱定义为小于x，且最大的数）
        else cout << T.get_next(T.root, x) << endl; // 求x的后继（后继定义为大于x，且最小的数）
    }
    return 0;
}
