// 例题:https://loj.ac/p/132
#include <bits/stdc++.h>
#define int long long

using namespace std;

struct BIT {

    int n;
    vector<int> d, t1, t2;

    BIT() {}
    BIT(int _n) {
        n = _n;
        d.resize(n + 5);
        t1.resize(n + 5);
        t2.resize(n + 5);
    }

    void add(int x, int v) {
        for (int i = x; i <= n; i += i & -i) {
            t1[i] += v;
            t2[i] += v * (x - 1);
        }
    }

    int ask(int x) {
        int res = 0;
        for (int i = x; i > 0; i -= i & -i) {
            res += x * t1[i] - t2[i];
        }
        return res;
    }

    void add_range(int l, int r, int v) {   // 单点修改和区间修改都用此函数
        add(l, v);
        add(r + 1, -v);
    }

    int ask_range(int l, int r) {   // 单点查询和区间查询都用此函数
        return ask(r) - ask(l - 1);
    }
};

signed main() {
    int n, m;
    cin >> n >> m;
    BIT B(n);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        B.add_range(i, i, a);
    }
    while (m--) {
        int op, l, r, x;
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> x;
            B.add_range(l, r, x);
        } else {
            cin >> l >> r;
            cout << B.ask_range(l, r) << endl;
        }
    }
    return 0;
} 
