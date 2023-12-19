// https://atcoder.jp/contests/abc331/tasks/abc331_f
// 给你一个长度为 N 的字符串 S ，由小写英文字母组成。  
// 请按照给出的顺序处理下面描述的 Q 个查询。  
// 查询有两种类型：
// 1 x c : 将S的x个字符改为小写英文字母c。
// 2 L R : 如果由S的L到R字符组成的子串是一个回文字符串，则打印 "是"，否则打印 "否"。
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct SegTree {
    
    int n, inf = 2e9;
    int base = 131, mod = 1e9 + 7;
    vector<int> lsum, rsum, pw;
    
    SegTree() {}
    SegTree(int n) {
        this->n = n;
        lsum = vector<int> (n * 4 + 5);
        rsum = vector<int> (n * 4 + 5);
        pw = vector<int> (n + 5);
        pw[0] = 1;
        for (int i = 1; i <= n; i++) {
            pw[i] = pw[i - 1] * base % mod;
        }
    }

    void pushup(int p, int l, int r, int m) {
        lsum[p] = (lsum[p * 2] * pw[r - m] % mod + lsum[p * 2 + 1]) % mod;
        rsum[p] = (rsum[p * 2 + 1] * pw[m - l + 1] % mod + rsum[p * 2]) % mod;
    }

    void change(int p, int l, int r, int pos, int val) {    // 单点修改
        if (l == r) {
            lsum[p] = val % mod;
            rsum[p] = val % mod;
            return;
        }
        int m = l + r >> 1;
        if (pos <= m) {
            change(p * 2, l, m, pos, val);
        }
        if (m < pos) {
            change(p * 2 + 1, m + 1, r, pos, val);
        }
        pushup(p, l, r, m);
    }

    int query_left(int p, int l, int r, int ql, int qr) {    // 查询区间正向哈希值
        if (ql <= l && r <= qr) {
            return lsum[p];
        }
        int m = l + r >> 1;
        int res = 0;
        if (ql <= m) {
            res = query_left(p * 2, l, m, ql, qr);
        }
        if (qr > m) {
            res = (res * pw[min(r, qr) - m] % mod + query_left(p * 2 + 1, m + 1, r, ql, qr)) % mod;
        }
        return res;
    }

    int query_right(int p, int l, int r, int ql, int qr) {    // 查询区间反向哈希值
        if (ql <= l && r <= qr) {
            return rsum[p];
        }
        int m = l + r >> 1;
        int res = 0;
        if (qr > m) {
            res = query_right(p * 2 + 1, m + 1, r, ql, qr);
        }
        if (ql <= m) {
            res = (res * pw[m - max(l, ql) + 1] % mod + query_right(p * 2, l, m, ql, qr)) % mod;
        }
        return res;
    }

    void change(int pos, int val) {
        change(1, 0, n, pos, val);
    }

    int query_left(int ql, int qr) {
        return query_left(1, 0, n, ql, qr);
    }

    int query_right(int ql, int qr) {
        return query_right(1, 0, n, ql, qr);
    }

};


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    SegTree S(n);
    for (int i = 0; i < n; i++) {
        S.change(i, s[i] - 'a');
    }
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            char c;
            cin >> x >> c;
            x--;
            S.change(x, c - 'a');
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << (S.query_left(l, r) == S.query_right(l, r) ? "Yes" : "No") << endl;
        }
    }
    return 0;
}
